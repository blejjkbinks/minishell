#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

// Example built-in command functions (for simplicity)
int my_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd: expected argument to \"cd\"\n");
        return 1;
    }
    if (chdir(args[1]) != 0) {
        perror("cd");
    }
    return 1;
}

int my_echo(char **args) {
    for (int i = 1; args[i]; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
    return 1;
}

// Determine if the command is a built-in and execute it if so
int is_builtin(char **command) {
    if (strcmp(command[0], "cd") == 0) {
        return my_cd(command);
    } else if (strcmp(command[0], "echo") == 0) {
        return my_echo(command);
    }
    return 0; // Not a built-in command
}

// Function to handle here document (<< redirection)
void handle_here_document(char *content, int *here_fd) {
    if (pipe(here_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Write the here document content to the pipe
    write(here_fd[1], content, strlen(content));
    close(here_fd[1]); // Close the write end of the pipe
}

// Function to handle built-in commands (executed in the parent)
void execute_builtin(char ***commands, char **input_files, char **output_files, int *redirection_modes, char **here_document_content, int i) {
    // Handle fd manipulations (input/output redirection)
    if (input_files[i] != NULL) {
        int input_fd = open(input_files[i], O_RDONLY);
        if (input_fd == -1) {
            perror("open input file");
            exit(EXIT_FAILURE);
        }
        dup2(input_fd, STDIN_FILENO); // Redirect input to the file
        close(input_fd);
    } else if (here_document_content[i] != NULL) {
        // Handle here document
        int here_fd[2];
        handle_here_document(here_document_content[i], here_fd);
        dup2(here_fd[0], STDIN_FILENO); // Redirect input from the here document pipe
        close(here_fd[0]); // Close the read end of the here document pipe
    }

    if (output_files[i] != NULL) {
        int flags = (redirection_modes[i] == 2) ? O_WRONLY | O_APPEND | O_CREAT : O_WRONLY | O_TRUNC | O_CREAT;
        int output_fd = open(output_files[i], flags, 0644);
        if (output_fd == -1) {
            perror("open output file");
            exit(EXIT_FAILURE);
        }
        dup2(output_fd, STDOUT_FILENO); // Redirect output to the file
        close(output_fd);
    }

    // Execute the built-in command in the parent
    if (is_builtin(commands[i]) == 0) {
        fprintf(stderr, "Unknown built-in command: %s\n", commands[i][0]);
    }
}

// Function to execute external commands (fork + exec)
void execute_external(char ***commands, char **input_files, char **output_files, int *redirection_modes, char **here_document_content, int i, int in_fd, int out_fd) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // In child process: handle input/output redirection
        if (input_files[i] != NULL) {
            int input_fd = open(input_files[i], O_RDONLY);
            if (input_fd == -1) {
                perror("open input file");
                exit(EXIT_FAILURE);
            }
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        } else if (here_document_content[i] != NULL) {
            // Handle here document
            int here_fd[2];
            handle_here_document(here_document_content[i], here_fd);
            dup2(here_fd[0], STDIN_FILENO);
            close(here_fd[0]);
        } else if (in_fd != -1) {
            dup2(in_fd, STDIN_FILENO); // Read from previous pipe if applicable
        }

        if (output_files[i] != NULL) {
            int flags = (redirection_modes[i] == 2) ? O_WRONLY | O_APPEND | O_CREAT : O_WRONLY | O_TRUNC | O_CREAT;
            int output_fd = open(output_files[i], flags, 0644);
            if (output_fd == -1) {
                perror("open output file");
                exit(EXIT_FAILURE);
            }
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        } else if (out_fd != -1) {
            dup2(out_fd, STDOUT_FILENO); // Write to next pipe if applicable
        }

        // Execute the external command
        execvp(commands[i][0], commands[i]);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

void execute_pipeline(char ***commands, char **input_files, char **output_files, int *redirection_modes, char **here_document_content, int n) {
    int i, fd[2], in_fd = -1;
    
    for (i = 0; i < n; i++) {
        // Check if the command is a built-in
        if (is_builtin(commands[i])) {
            execute_builtin(commands, input_files, output_files, redirection_modes, here_document_content, i);
        } else {
            // For external commands, we need to fork
            if (i < n - 1) {
                if (pipe(fd) == -1) {
                    perror("pipe");
                    exit(EXIT_FAILURE);
                }
            }

            execute_external(commands, input_files, output_files, redirection_modes, here_document_content, i, in_fd, (i < n - 1) ? fd[1] : -1);

            // Close the pipe's write end and update the read end
            if (i < n - 1) close(fd[1]);
            if (in_fd != -1) close(in_fd);
            in_fd = (i < n - 1) ? fd[0] : -1;
        }
    }

    // Wait for all child processes
    while (wait(NULL) > 0);
}

int main() {
    // Example commands split into arrays of strings
    char *cmd1[] = { "echo", "Hello", "World", NULL };
    char *cmd2[] = { "wc", "-l", NULL };
    
    // Array of commands (each is an array of strings)
    char **commands[] = { cmd1, cmd2 };

    // Input and output files for each command (NULL means no redirection)
    char *input_files[] = { NULL, NULL };
    char *output_files[] = { NULL, "output.txt" };

    // Redirection modes (0 = none, 1 = truncating output, 2 = appending output)
    int redirection_modes[] = { 0, 1 };

    // Here document content (NULL means no here document)
    char *here_document_content[] = { NULL, NULL };

    // Number of stages (commands)
    int n = 2;

    // Execute the pipeline
    execute_pipeline(commands, input_files, output_files, redirection_modes, here_document_content, n);

    return 0;
}


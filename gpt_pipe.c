#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

// Function to check if a command is a builtin
int is_builtin(char *cmd) {
    return (strcmp(cmd, "echo") == 0 || strcmp(cmd, "cd") == 0);  // Example builtins
}

// Example builtin function (echo in this case)
void run_builtin(char *cmd[]) {
    if (strcmp(cmd[0], "echo") == 0) {
        for (int i = 1; cmd[i] != NULL; i++) {
            printf("%s ", cmd[i]);
        }
        printf("\n");
    }
}

// Function to restore original stdin and stdout
void restore_fds(int stdin_copy, int stdout_copy) {
    dup2(stdin_copy, STDIN_FILENO);
    dup2(stdout_copy, STDOUT_FILENO);
    close(stdin_copy);
    close(stdout_copy);
}

// Handle redirection for the current command
void handle_redirection(char *input_file, char *output_file, int output_type) {
    if (input_file) {
        int in_fd = open(input_file, O_RDONLY);
        if (in_fd < 0) {
            perror("Error opening input file");
            exit(EXIT_FAILURE);
        }
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }

    if (output_file) {
        int out_fd;
        if (output_type == 1) {  // ">"
            out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        } else if (output_type == 2) {  // ">>"
            out_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }

        if (out_fd < 0) {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }
}

int main() {
    // Array of commands with optional input/output redirection files
    char *commands[][4] = {
        {"echo", "hello", NULL},          // Builtin command
        {"grep", "h", NULL},              // External command
        {"wc", "-l", NULL}                // External command
    };

    // Simulated input/output files for redirection
    char *input_file = "input.txt";       // Example input redirection
    char *output_file = "output.txt";     // Example output redirection (could be NULL)
    int output_type = 1;                  // 1 = ">", 2 = ">>" (can be dynamically set)

    int num_cmds = 3;
    int pipe_fd[2];
    int input_fd = -1;  // Input from previous pipe
    pid_t pid;

    // Save original stdin and stdout
    int stdin_copy = dup(STDIN_FILENO);
    int stdout_copy = dup(STDOUT_FILENO);

    for (int i = 0; i < num_cmds; i++) {
        // Create a pipe for every command except the last one
        if (i < num_cmds - 1) {
            pipe(pipe_fd);
        }

        // Check if the command is a builtin
        if (is_builtin(commands[i][0])) {
            // If there's an input from the previous pipe, redirect stdin
            if (input_fd != -1) {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }

            // Handle input/output redirection for builtin
            handle_redirection(i == 0 ? input_file : NULL,  // Apply input redirection for first cmd
                               (i == num_cmds - 1) ? output_file : NULL,  // Apply output redirection for last cmd
                               output_type);

            // If there's an output pipe, redirect stdout
            if (i < num_cmds - 1) {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            // Run the builtin command
            run_builtin(commands[i]);

            // Restore original stdin and stdout after the builtin
            restore_fds(stdin_copy, stdout_copy);
        } else {
            // Fork a child for external commands
            if ((pid = fork()) == 0) {
                // In child process
                if (input_fd != -1) {
                    dup2(input_fd, STDIN_FILENO);
                    close(input_fd);
                }

                if (i < num_cmds - 1) {
                    dup2(pipe_fd[1], STDOUT_FILENO);
                    close(pipe_fd[0]);
                    close(pipe_fd[1]);
                }

                // Handle input/output redirection for external commands
                handle_redirection(i == 0 ? input_file : NULL,
                                   (i == num_cmds - 1) ? output_file : NULL,
                                   output_type);

                // Execute the external command
                execvp(commands[i][0], commands[i]);
                perror("execvp failed");
                exit(EXIT_FAILURE);
            }
        }

        // In the parent process

        if (input_fd != -1) {
            close(input_fd);  // Close previous pipe read end
        }

        if (i < num_cmds - 1) {
            close(pipe_fd[1]);  // Close current pipe write end
            input_fd = pipe_fd[0];  // Set up input for the next command
        }
    }

    // Wait for all child processes
    for (int i = 0; i < num_cmds; i++) {
        wait(NULL);
    }

    // Restore original stdin and stdout
    restore_fds(stdin_copy, stdout_copy);

    return 0;
}

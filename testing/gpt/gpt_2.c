#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

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

void execute_pipeline(char ***commands, char **input_files, char **output_files, int *redirection_modes, char **here_document_content, int n) {
    int i;
    int fd[2];
    int in_fd = 0; // Start with standard input
    int here_fd[2]; // Pipe for here document
    pid_t pid;

    for (i = 0; i < n; i++) {
        // Create a pipe for the next stage, if not the last stage
        if (i < n - 1 && pipe(fd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // In child process

            // Handle input redirection
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
                handle_here_document(here_document_content[i], here_fd);
                dup2(here_fd[0], STDIN_FILENO); // Redirect input from the here document pipe
                close(here_fd[0]); // Close the read end of the here document pipe
            } else if (i > 0) {
                dup2(in_fd, STDIN_FILENO); // Redirect input from the previous pipe
            }

            // Handle output redirection
            if (output_files[i] != NULL) {
                int flags = (redirection_modes[i] == 2) ? O_WRONLY | O_APPEND | O_CREAT : O_WRONLY | O_TRUNC | O_CREAT;
                int output_fd = open(output_files[i], flags, 0644);
                if (output_fd == -1) {
                    perror("open output file");
                    exit(EXIT_FAILURE);
                }
                dup2(output_fd, STDOUT_FILENO); // Redirect output to the file
                close(output_fd);
            } else if (i < n - 1) {
                dup2(fd[1], STDOUT_FILENO); // Redirect output to the next pipe
            }

            // Close pipe file descriptors
            if (i < n - 1) close(fd[0]);
            if (i > 0) close(in_fd);
            if (i < n - 1) close(fd[1]);

            // Execute the command
            execvp(commands[i][0], commands[i]);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            // In parent process

            // Close the write end of the current pipe
            if (i < n - 1) close(fd[1]);

            // Close the previous input pipe
            if (i > 0) close(in_fd);

            // Save the read end of the current pipe for the next iteration
            if (i < n - 1) in_fd = fd[0];
        }
    }

    // Wait for all children to finish
    for (i = 0; i < n; i++) {
        wait(NULL);
    }
}

int main() {
    // Example commands split into arrays of strings
    char *cmd1[] = { "grep", "pattern", NULL };
    char *cmd2[] = { "wc", "-l", NULL };
    
    // Array of commands (each is an array of strings)
    char **commands[] = { cmd1, cmd2 };

    // Input and output files for each command (NULL means no redirection)
    char *input_files[] = { NULL, NULL }; // No input redirection for either command
    char *output_files[] = { NULL, "output.txt" }; // Only cmd2 has output redirection

    // Redirection modes (0 = none, 1 = truncating output, 2 = appending output)
    int redirection_modes[] = { 0, 1 }; // Only cmd2 has truncating output redirection

    // Here document content (NULL means no here document)
    char *here_document_content[] = { "this is some pattern\nanother line\n", NULL }; // Only cmd1 uses a here document

    // Number of stages (commands)
    int n = 2;

    // Execute the pipeline
    execute_pipeline(commands, input_files, output_files, redirection_modes, here_document_content, n);

    return 0;
}


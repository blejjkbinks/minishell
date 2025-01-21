#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void execute_pipeline(char ***commands, char **input_files, char **output_files, int *redirection_modes, int n)
{
    int i;
    int fd[2];
    int in_fd = 0; // Start with standard input
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
    char *cmd1[] = { "cat", "file.txt", NULL };
    char *cmd2[] = { "grep", "pattern", NULL };
    char *cmd3[] = { "wc", "-l", NULL };
    
    // Array of commands (each is an array of strings)
    char **commands[] = { cmd1, cmd2, cmd3 };

    // Input and output files for each command (NULL means no redirection)
    char *input_files[] = { "input.txt", NULL, NULL }; // Only cmd1 has input redirection
    char *output_files[] = { NULL, NULL, "output.txt" }; // Only cmd3 has output redirection

    // Redirection modes (0 = none, 1 = truncating output, 2 = appending output)
    int redirection_modes[] = { 0, 0, 1 }; // Only cmd3 has truncating output redirection

    // Number of stages (commands)
    int n = 3;

    // Execute the pipeline
    execute_pipeline(commands, input_files, output_files, redirection_modes, n);

    return 0;
}


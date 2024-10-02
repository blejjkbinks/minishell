#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

// Function to execute a single command with input/output redirection
void execute_command(char *cmd[], int input_fd, int output_fd)
{
    if (input_fd != -1) {
        dup2(input_fd, STDIN_FILENO);  // Redirect input
        close(input_fd);
    }

    if (output_fd != -1) {
        dup2(output_fd, STDOUT_FILENO);  // Redirect output
        close(output_fd);
    }

    // Execute the command
    if (execvp(cmd[0], cmd) == -1) {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    // Example commands
    char *commands[][4] = {
        {"cat", "input.txt", NULL},   // cat < input.txt
        {"grep", "hello", NULL},      // grep hello
        {"wc", "-l", NULL}            // wc -l
    };

    int num_cmds = 3;  // Number of commands

    // Pipe file descriptors
    int pipe_fd[2];
    int input_fd = -1;  // Initially, there's no input redirection
    pid_t pid;

    // Loop over all commands
    for (int i = 0; i < num_cmds; i++) {
        if (i < num_cmds - 1) {
            // Create a pipe for every command except the last one
            pipe(pipe_fd);
        }

        // Fork a child process
        if ((pid = fork()) == 0) {
            // In the child process
            if (input_fd != -1) {
                // Redirect input from the previous command's output
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }

            if (i < num_cmds - 1) {
                // Redirect output to the next command's input (pipe write end)
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            // Execute the current command
            execute_command(commands[i], -1, -1);
        }

        // In the parent process
        if (input_fd != -1) {
            // Close the previous command's pipe read end
            close(input_fd);
        }

        if (i < num_cmds - 1) {
            // Close the write end of the current pipe (since it's now handled by the child)
            close(pipe_fd[1]);
            // The next command's input will be the read end of this pipe
            input_fd = pipe_fd[0];
        }
    }

    // Wait for all child processes
    for (int i = 0; i < num_cmds; i++) {
        wait(NULL);
    }

    return 0;
}

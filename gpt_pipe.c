
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

// Function to check if a command is a builtin (this is just an example)
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

int main() {
    char *commands[][4] = {
        {"echo", "hello", NULL},    // Builtin command
        {"grep", "h", NULL},        // External command
        {"wc", "-l", NULL}          // External command
    };

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



// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/wait.h>
// #include <string.h>

// // Function to execute a single command with input/output redirection
// void execute_command(char *cmd[], int input_fd, int output_fd, int append_fd, int input_redir_fd)
// {
//     if (input_fd != -1) {
//         dup2(input_fd, STDIN_FILENO);  // Redirect input (from previous pipe)
//         close(input_fd);
//     }

//     if (input_redir_fd != -1) {
//         dup2(input_redir_fd, STDIN_FILENO);  // Redirect input from a file
//         close(input_redir_fd);
//     }

//     if (append_fd != -1) {
//         dup2(append_fd, STDOUT_FILENO);  // Redirect output to a file (append mode)
//         close(append_fd);
//     } else if (output_fd != -1) {
//         dup2(output_fd, STDOUT_FILENO);  // Redirect output to a file (truncate mode)
//         close(output_fd);
//     }

//     // Execute the command
//     if (execvp(cmd[0], cmd) == -1) {
//         perror("execvp");
//         exit(EXIT_FAILURE);
//     }
// }

// int main()
// {
//     // Example commands (without redirection for now)
//     char *commands[][4] = {
//         {"cat", "input.txt", NULL},   // cat < input.txt
//         {"grep", "hello", NULL},      // grep hello
//         {"wc", "-l", NULL}            // wc -l > output.txt
//     };

//     int num_cmds = 3;  // Number of commands

//     // Redirection types and file names for each command
//     char *redirections[] = {NULL, NULL, ">"};     // Last command has output redirection
//     char *files[] = {NULL, NULL, "output.txt"};   // Redirection to "output.txt"

//     int pipe_fd[2];       // Pipe file descriptors
//     int input_fd = -1;    // Input from previous pipe
//     int input_redir_fd = -1;  // Input redirection file descriptor
//     int output_fd = -1;   // Output redirection file descriptor
//     int append_fd = -1;   // Append redirection file descriptor
//     pid_t pid;

//     // Loop over all commands
//     for (int i = 0; i < num_cmds; i++) {
//         // Check for input/output redirection
//         if (redirections[i]) {
//             if (strcmp(redirections[i], "<") == 0) {
//                 input_redir_fd = open(files[i], O_RDONLY);
//                 if (input_redir_fd == -1) {
//                     perror("open input file");
//                     exit(EXIT_FAILURE);
//                 }
//             } else if (strcmp(redirections[i], ">") == 0) {
//                 output_fd = open(files[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//                 if (output_fd == -1) {
//                     perror("open output file");
//                     exit(EXIT_FAILURE);
//                 }
//             } else if (strcmp(redirections[i], ">>") == 0) {
//                 append_fd = open(files[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
//                 if (append_fd == -1) {
//                     perror("open append file");
//                     exit(EXIT_FAILURE);
//                 }
//             }
//         }

//         // Create a pipe for every command except the last one
//         if (i < num_cmds - 1) {
//             pipe(pipe_fd);
//         }

//         // Fork a child process
//         if ((pid = fork()) == 0) {
//             // In the child process
//             if (input_fd != -1) {
//                 // Redirect input from the previous command's output
//                 dup2(input_fd, STDIN_FILENO);
//                 close(input_fd);
//             }

//             if (i < num_cmds - 1) {
//                 // Redirect output to the next command's input (pipe write end)
//                 dup2(pipe_fd[1], STDOUT_FILENO);
//                 close(pipe_fd[0]);
//                 close(pipe_fd[1]);
//             }

//             // Execute the current command with redirection (if any)
//             execute_command(commands[i], -1, output_fd, append_fd, input_redir_fd);
//         }

//         // In the parent process
//         if (input_fd != -1) {
//             // Close the previous command's pipe read end
//             close(input_fd);
//         }

//         if (i < num_cmds - 1) {
//             // Close the write end of the current pipe (since it's now handled by the child)
//             close(pipe_fd[1]);
//             // The next command's input will be the read end of this pipe
//             input_fd = pipe_fd[0];
//         }

//         // Close file descriptors if used for redirection
//         if (input_redir_fd != -1) {
//             close(input_redir_fd);
//             input_redir_fd = -1;
//         }
//         if (output_fd != -1) {
//             close(output_fd);
//             output_fd = -1;
//         }
//         if (append_fd != -1) {
//             close(append_fd);
//             append_fd = -1;
//         }
//     }

//     // Wait for all child processes
//     for (int i = 0; i < num_cmds; i++) {
//         wait(NULL);
//     }

//     return 0;
// }

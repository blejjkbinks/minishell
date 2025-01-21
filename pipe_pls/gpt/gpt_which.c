#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid;
    char buffer[BUF_SIZE];
    ssize_t num_bytes;


    (void)argc;
    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Close the read end of the pipe
        close(pipefd[0]);

        // Redirect stdout to the pipe's write end
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        // Close the write end of the pipe (after dup2, it's not needed)
        close(pipefd[1]);

        // Prepare arguments for execve
        char *which_args[] = {"/bin/which", argv[1], NULL};

        // Execute the "which" command
        if (execve("/bin/which", which_args, NULL) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else { // Parent process
        // Close the write end of the pipe
        close(pipefd[1]);

        // Wait for the child to finish
        wait(NULL);

        // Read from the pipe
        num_bytes = read(pipefd[0], buffer, BUF_SIZE - 1);
        if (num_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Null-terminate the string
        buffer[num_bytes] = '\0';

        // Print the result
        printf("Result: %s", buffer);

        // Close the read end of the pipe
        close(pipefd[0]);
    }

    return 0;
}


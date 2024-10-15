#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        printf("myshell> ");  // Print prompt
        fgets(input, MAX_INPUT_SIZE, stdin);  // Read input

        // Remove newline character from input
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            break;  // Exit shell
        }

        // Create a child process
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            char *args[] = {"/bin/sh", "-c", input, NULL};  // Use /bin/sh to execute the command
            execv(args[0], args);  // Execute the command
            perror("execv");  // If execv returns, there was an error
            exit(1);
        } else if (pid < 0) {
            perror("fork");  // Fork failed
        } else {
            // Parent process waits for child to finish
            wait(NULL);
        }
    }
    return 0;
}

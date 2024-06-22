#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 10  // Maximum number of arguments for each command
#define MAX_COMMANDS 10  // Maximum number of commands in the pipeline
#define READ 0
#define WRITE 1
void execute_pipeline(char *commands[MAX_COMMANDS][MAX_ARGS], int num_commands);

int main() {
    char *commands[MAX_COMMANDS][MAX_ARGS];
    char input[1024];
    int num_commands = 0;

    printf("Enter commands for pipeline (terminate with 'end'): \n");

    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        input[strcspn(input, "\n")] = '\0';  // Remove trailing newline

        if (strcmp(input, "end") == 0) {
            break;
        }

        // Split input into tokens
        int argc = 0;
        char *token = strtok(input, " ");
        while (token != NULL && argc < MAX_ARGS - 1) {
            commands[num_commands][argc++] = token;
            token = strtok(NULL, " ");
        }
        commands[num_commands][argc] = NULL;  // Last argument must be NULL

        num_commands++;
        if (num_commands >= MAX_COMMANDS) {
            fprintf(stderr, "Maximum number of commands exceeded.\n");
            break;
        }
    }

    execute_pipeline(commands, num_commands);

    return 0;
}

void execute_pipeline(char *commands[MAX_COMMANDS][MAX_ARGS], int num_commands) {
    int pipes[num_commands - 1][2];  // Array of pipes
    pid_t pids[num_commands];  // Array of process IDs

    // Create pipes
    for (int i = 0; i < num_commands - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe error");
            exit(EXIT_FAILURE);
        }
    }

    // Execute commands in pipeline
    for (int i = 0; i < num_commands; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0) {
            // Child process
            // Handle input redirection from previous command
            if (i > 0) {
                dup2(pipes[i - 1][READ], STDIN_FILENO);
            }

            // Handle output redirection to next command
            if (i < num_commands - 1) {
                dup2(pipes[i][WRITE], STDOUT_FILENO);
            }

            // Close all pipe ends
            for (int j = 0; j < num_commands - 1; j++) {
                close(pipes[j][READ]);
                close(pipes[j][WRITE]);
            }

            // Execute the command
            execvp(commands[i][0], commands[i]);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }

    // Close all pipe ends in parent process
    for (int i = 0; i < num_commands - 1; i++) {
        close(pipes[i][READ]);
        close(pipes[i][WRITE]);
    }

    // Wait for all children to complete
    for (int i = 0; i < num_commands; i++) {
        waitpid(pids[i], NULL, 0);
    }
}

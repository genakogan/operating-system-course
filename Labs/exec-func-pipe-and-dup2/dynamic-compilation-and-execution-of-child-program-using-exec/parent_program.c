#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        // Fork failed
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process executing...\n");

        // Compile child_program.c using gcc
        execl("/usr/bin/gcc", "gcc", "child_program.c", "-o", "child_program", (char *)NULL);

        // If execl() fails
        perror("execl error");
        exit(1);
    } else {
        // Parent process
        printf("Parent process\n");

        // Wait for the child process to finish compilation
        wait(NULL);

        // Now execute the compiled child_program
        execl("./child_program", "child_program", (char *)NULL);

        // If execl() fails
        perror("execl error");
        exit(1);
    }

    return 0;
}

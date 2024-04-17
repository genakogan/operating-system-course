#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler function
void sigintHandler(int signum) {
    printf("Caught SIGINT signal (Ctrl+C)\n");
    // You can add custom actions here, such as cleanup or graceful termination
    exit(signum);
}

int main() {
    // Registering the signal handler
    signal(SIGINT, sigintHandler);

    printf("Try pressing Ctrl+C to trigger the SIGINT signal\n");

    // Infinite loop to keep the program running until terminated
    while (1) {
        // Do some work
    }

    return 0;
}

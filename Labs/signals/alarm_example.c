#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGALRM
void alarmHandler(int signum) {
    printf("Alarm triggered by SIGALRM\n");
    // Add custom handling here
    exit(signum); // Exit the program after handling the alarm
}

int main() {
    // Registering signal handler for SIGALRM
    signal(SIGALRM, alarmHandler);

    printf("Setting up alarm for 5 seconds\n");
    alarm(5); // Set up an alarm to trigger after 5 seconds

    // Infinite loop to keep the program running until the alarm triggers
    while(1) {
        // Do some work while waiting for the alarm
        sleep(1);
        printf("Still waiting...\n");
    }

    return 0;
}

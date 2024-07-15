#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

// Define the structure for sembuf
struct sembuf {
    unsigned short sem_num;  // Semaphore index in the set
    short sem_op;            // Semaphore operation
    short sem_flg;           // Operation flags
};

// Constants for the semaphore
#define KEY 1234            // Key to identify the semaphore set
#define NUM_SEMAPHORES 3    // Number of semaphores in the set

int main() {
    int semid;
    struct sembuf sb;
    unsigned short sem_values[NUM_SEMAPHORES] = {1, 1, 1};  // Initial values for the semaphores

    // Create a semaphore set with NUM_SEMAPHORES semaphores
    semid = semget(KEY, NUM_SEMAPHORES, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize all semaphores in the set with a value of 1
    if (semctl(semid, 0, SETALL, sem_values) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    // Fork the first child process
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // First child process

        sb.sem_num = 0;   // Index of the semaphore
        sb.sem_op = -1;   // Decrement the semaphore (wait)
        sb.sem_flg = 0;

        printf("First Child: Waiting to acquire semaphore 0...\n");
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }

        // Critical section
        printf("First Child: Entered critical section with semaphore 0.\n");
        sleep(2);  // Simulate some work
        printf("First Child: Leaving critical section with semaphore 0.\n");

        sb.sem_op = 1;   // Increment the semaphore (signal)
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    } else {
        // Fork the second child process
        pid_t pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) {
            // Second child process

            sb.sem_num = 2;   // Index of the semaphore
            sb.sem_op = -1;   // Decrement the semaphore (wait)
            sb.sem_flg = 0;

            printf("Second Child: Waiting to acquire semaphore 2...\n");
            if (semop(semid, &sb, 1) == -1) {
                perror("semop");
                exit(EXIT_FAILURE);
            }

            // Critical section
            printf("Second Child: Entered critical section with semaphore 2.\n");
            sleep(2);  // Simulate some work
            printf("Second Child: Leaving critical section with semaphore 2.\n");

            sb.sem_op = 1;   // Increment the semaphore (signal)
            if (semop(semid, &sb, 1) == -1) {
                perror("semop");
                exit(EXIT_FAILURE);
            }

            exit(EXIT_SUCCESS);
        } else {
            // Parent process

            // Wait for children to finish
            wait(NULL);
            wait(NULL);

            // Remove the semaphore set
            if (semctl(semid, 0, IPC_RMID) == -1) {
                perror("semctl");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}


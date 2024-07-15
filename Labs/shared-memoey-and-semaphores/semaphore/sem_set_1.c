#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>



union semun {
    int val;                // Value for SETVAL
    struct semid_ds *buf;   // Buffer for IPC_STAT, IPC_SET
    unsigned short *array;  // Array for GETALL, SETALL
};

#define KEY 1234  // Key to identify the semaphore set
#define NUM_SEMAPHORES 3  // Number of semaphores in the set

int main() {
    int semid;
    struct sembuf sb;
    union semun arg;
    unsigned short sem_values[NUM_SEMAPHORES] = {1, 1, 1};  // Initial values for the semaphores

    // Create a semaphore set with NUM_SEMAPHORES semaphores
    semid = semget(KEY, NUM_SEMAPHORES, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initializes all semaphores in the set with a value of 1.
    // unsigned short sem_values[NUM_SEMAPHORES] = {1, 1, 1};
    arg.array = sem_values;
    if (semctl(semid, 0, SETALL, arg) == -1) {
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

        // Wait (decrement) operation on the first semaphore
        sb.sem_num = 0;  // Index of the semaphore
        sb.sem_op = -1;  // Decrement the semaphore
        sb.sem_flg = 0;
        printf("First Child: Waiting for the first semaphore...\n");
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }

        // Critical section
        printf("First Child: Entering critical section with the first semaphore...\n");
        sleep(2);  // Simulate some work
        printf("First Child: Leaving critical section with the first semaphore...\n");

        // Signal (increment) operation on the first semaphore
        sb.sem_op = 1;  // Increment the semaphore
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

            // Wait (decrement) operation on the third semaphore
            sb.sem_num = 2;  // Index of the semaphore
            sb.sem_op = -1;  // Decrement the semaphore
            sb.sem_flg = 0;
            printf("Second Child: Waiting for the third semaphore...\n");
            if (semop(semid, &sb, 1) == -1) {
                perror("semop");
                exit(EXIT_FAILURE);
            }

            // Critical section
            printf("Second Child: Entering critical section with the third semaphore...\n");
            sleep(2);  // Simulate some work
            printf("Second Child: Leaving critical section with the third semaphore...\n");

            // Signal (increment) operation on the third semaphore
            sb.sem_op = 1;  // Increment the semaphore
            if (semop(semid, &sb, 1) == -1) {
                perror("semop");
                exit(EXIT_FAILURE);
            }

            exit(EXIT_SUCCESS);
        } else {
            // Parent process

            // Wait for the first child to acquire the first semaphore
            sleep(1);

            // Wait (decrement) operation on the second semaphore
            sb.sem_num = 1;  // Index of the semaphore
            sb.sem_op = -1;  // Decrement the semaphore
            sb.sem_flg = 0;
            printf("Parent: Waiting for the second semaphore...\n");
            if (semop(semid, &sb, 1) == -1) {
                perror("semop");
                exit(EXIT_FAILURE);
            }

            // Critical section
            printf("Parent: Entering critical section with the second semaphore...\n");
            sleep(2);  // Simulate some work
            printf("Parent: Leaving critical section with the second semaphore...\n");

            // Signal (increment) operation on the second semaphore
            sb.sem_op = 1;  // Increment the semaphore
            if (semop(semid, &sb, 1) == -1) {
                perror("semop");
                exit(EXIT_FAILURE);
            }

            // Wait for both children to finish
            wait(NULL);
            wait(NULL);

            // Remove the semaphore set
            if (semctl(semid, 0, IPC_RMID, arg) == -1) {
                perror("semctl");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}



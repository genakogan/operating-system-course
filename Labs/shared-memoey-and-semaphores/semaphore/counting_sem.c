#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 5
#define NUM_RESOURCES 3

sem_t semaphore;

void* thread_func(void* arg) {
    int thread_num = *(int*)arg;
    printf("Thread %d waiting to acquire resource...\n", thread_num);

    // Wait (decrement) the semaphore
    sem_wait(&semaphore);

    // Critical section
    printf("Thread %d acquired resource.\n", thread_num);
    sleep(2); // Simulate work with the resource
    printf("Thread %d releasing resource.\n", thread_num);

    // Signal (increment) the semaphore
    sem_post(&semaphore);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int result;

    // Initialize the counting semaphore with the number of resources
    result = sem_init(&semaphore, 0, NUM_RESOURCES);
    if (result != 0) {
        perror("sem_init");
        exit(EXIT_FAILURE);
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i] = i + 1;
        result = pthread_create(&threads[i], NULL, thread_func, &thread_args[i]);
        if (result != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        result = pthread_join(threads[i], NULL);
        if (result != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    // Destroy the semaphore
    result = sem_destroy(&semaphore);
    if (result != 0) {
        perror("sem_destroy");
        exit(EXIT_FAILURE);
    }

    return 0;
}


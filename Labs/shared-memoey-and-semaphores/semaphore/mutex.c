#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;

void* thread_func1(void* arg) {
    printf("Thread 1 waiting for mutex...\n");
    pthread_mutex_lock(&mutex);
    printf("Thread 1 entered critical section\n");
    sleep(2); // Simulate some work
    printf("Thread 1 leaving critical section\n");
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void* thread_func2(void* arg) {
    printf("Thread 2 waiting for mutex...\n");
    pthread_mutex_lock(&mutex);
    printf("Thread 2 entered critical section\n");
    sleep(2); // Simulate some work
    printf("Thread 2 leaving critical section\n");
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create two threads
    pthread_create(&thread1, NULL, thread_func1, NULL);
    pthread_create(&thread2, NULL, thread_func2, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}


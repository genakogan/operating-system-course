#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t my_mutex;
pthread_cond_t my_cond;

int data = 0;

void* thread1_func(void* arg) {
    // Wait for data to become non-zero
    pthread_mutex_lock(&my_mutex);
    while (data == 0) {
        pthread_cond_wait(&my_cond, &my_mutex);
    }

    // Print the data and release the mutex
    printf("Thread 1 received data: %d\n", data);
    pthread_mutex_unlock(&my_mutex);

    return NULL;
}

void* thread2_func(void* arg) {
    // Set the data and signal the condition variable
    pthread_mutex_lock(&my_mutex);
    data = 42;
    pthread_cond_signal(&my_cond);
    pthread_mutex_unlock(&my_mutex);

    return NULL;
}

int main() {
    // Initialize the mutex and condition variable
    pthread_mutex_init(&my_mutex, NULL);
    pthread_cond_init(&my_cond, NULL);

    // Launch two threads
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex and condition variable
    pthread_mutex_destroy(&my_mutex);
    pthread_cond_destroy(&my_cond);

    return 0;
}

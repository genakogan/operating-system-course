#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t my_mutex;

void* thread_func(void* arg) {
    // Attempt to acquire the mutex
    int ret = pthread_mutex_trylock(&my_mutex);

    if (ret == 0) {
        // Mutex acquired successfully
        printf("Thread %ld acquired the mutex\n", (long)pthread_self());

        // Do some work while holding the mutex
        // ...

        // Release the mutex
        pthread_mutex_unlock(&my_mutex);
        printf("Thread %ld released the mutex\n", (long)pthread_self());
    }
    else {
        // Mutex already locked by another thread
        printf("Thread %ld could not acquire the mutex\n", (long)pthread_self());
    }

    return NULL;
}

int main() {
    // Initialize the mutex
    pthread_mutex_init(&my_mutex, NULL);

    // Launch two threads that will compete for the mutex
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread_func, NULL);
    pthread_create(&thread2, NULL, thread_func, NULL);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&my_mutex);

    return 0;
}

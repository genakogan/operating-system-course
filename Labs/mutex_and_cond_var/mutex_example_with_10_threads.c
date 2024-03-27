#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 10
#define MAX_INDEX 3

int sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* worker(void* arg) {
    int index = *(int*)arg;
    printf("Starting worker %d with PID %ld\n", index, (long)pthread_self());
    // Execute some task here
    pthread_mutex_lock(&mutex);
    sum += index;
    printf("Finishing worker %d with PID %ld\n", index, (long)pthread_self());
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int indexes[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        indexes[i] = i;
        pthread_create(&threads[i], NULL, worker, (void*)&indexes[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Sum of indexes: %d\n", sum);
    return 0;
}
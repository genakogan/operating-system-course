#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

#define MAX_THREADS 3
#define MAX_COUNT 10

int counter = 0;
int turn = 0; // Which thread's turn it is (0, 1, 2)

pthread_mutex_t mutex;
pthread_cond_t condition;

void *threads_func(void *arg) {
    int thread_id = *((int *)arg);

    while (1) {
        pthread_mutex_lock(&mutex);

        // Wait until it's this thread's turn or counter is done
        while (thread_id != turn && counter < MAX_COUNT) {
            pthread_cond_wait(&condition, &mutex);
        }

        if (counter >= MAX_COUNT) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        printf("thread_id %d: counter = %d\n", thread_id, counter);
        counter++;

        // Change turn to next thread
        turn = (turn + 1) % MAX_THREADS;

        pthread_cond_broadcast(&condition); // Wake up all threads
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main(void) {
    pthread_t threads[MAX_THREADS];
    int thread_ids[MAX_THREADS];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condition, NULL);

    for (int i = 0; i < MAX_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, threads_func, &thread_ids[i]);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);

    return 0;
}


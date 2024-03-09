#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*In this example, we set the thread attribute to PTHREAD_CREATE_DETACHED, making the threads detached. Detached threads do not need to be explicitly joined; they clean up resources automatically when they exit.*/

#define NUM_THREADS 3

void *thread_function(void *arg) {
    printf("Thread is running\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    int rc, t;

    // Initialize thread attribute
    pthread_attr_init(&attr);

    // Set thread as detached
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Create threads
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating detached thread %d\n", t);
        rc = pthread_create(&threads[t], &attr, thread_function, NULL);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Main thread does not need to join detached threads

    // Destroy thread attribute once it is no longer needed
    pthread_attr_destroy(&attr);

    printf("Main thread exiting\n");

    pthread_exit(NULL);
}


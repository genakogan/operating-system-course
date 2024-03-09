#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/prctl.h>  // Required for prctl

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

    // Create threads
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %d\n", t);

        // Create thread
        rc = pthread_create(&threads[t], &attr, thread_function, NULL);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }

        // Set thread name (Linux-specific)
        char thread_name[16];
        snprintf(thread_name, sizeof(thread_name), "MyThread%d", t);
        prctl(PR_SET_NAME, thread_name, 0, 0, 0);
    }

    // Main thread does not


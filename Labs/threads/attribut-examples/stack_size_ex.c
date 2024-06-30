#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3

void *thread_function(void *arg) {
    printf("Thread is running\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    size_t stack_size = 1024 * 1024;  // 1 MB (adjust as needed)
    // 1 KB = 1024 bytes
    // 1 MB = 1024 KB 
    // 1 MB = 1048576 bytes
    // 1 byte = 8 bits 
    
    
    int rc, t;

    // Initialize thread attribute
    pthread_attr_init(&attr);

    // Set stack size
    pthread_attr_setstacksize(&attr, stack_size);

    // Create threads
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %d\n", t);
        rc = pthread_create(&threads[t], &attr, thread_function, NULL);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Main thread does not need to join threads

    // Destroy thread attribute once it is no longer needed
    pthread_attr_destroy(&attr);

    printf("Main thread exiting\n");

    pthread_exit(NULL);
}


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void *thread_function(void *thread_id) {
    long tid;
    tid = (long)thread_id;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    printf("pid is %ld\n", pthread_self());
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    
    for(t=0; t<NUM_THREADS; t++){
        printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, thread_function, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    /* Wait for all threads to complete */
    for(t=0; t<NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("All threads completed. Exiting the main thread.\n");
    //pthread_exit(NULL);
    printf("pid is %ld\n", pthread_self());
    printf("TODO\n");
    
}


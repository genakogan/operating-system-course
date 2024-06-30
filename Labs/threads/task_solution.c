#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function prototype for the thread start routine
void *start_routine(void *arg);

int main() {
    pthread_t thread; // Thread identifier
    int num_times = 3; // Example: Print "HELLO" 3 times
    
    // Create thread
    if (pthread_create(&thread, NULL, start_routine, (void *)&num_times) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    
    // Wait for thread to finish
    if (pthread_join(thread, NULL) != 0) {
        fprintf(stderr, "Error joining thread\n");
        return 1;
    }
    
    printf("Main thread exiting\n");
    
    return 0;
}

// Thread start routine
void *start_routine(void *arg) {
    int num_times = *((int *)arg); // Cast argument back to int
    int i;
    
    for (i = 0; i < num_times; i++) {
        printf("HELLO\n");
    }
    
    pthread_exit(NULL);
}

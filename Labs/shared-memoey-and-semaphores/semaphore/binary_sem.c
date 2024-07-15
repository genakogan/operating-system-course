#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


/*

Binary Semaphore:

    A binary semaphore is a semaphore with a value of either 0 or 1.
    It is primarily used for signaling, i.e., one task can signal another to perform some action.
    It doesn't have ownership; any thread can release the semaphore.
    It can be used to synchronize tasks between different processes.

*/




sem_t bin_sem; // Declaration of a semaphore variable

void* thread_func1(void* arg) {
    printf("Thread 1 waiting for semaphore...\n");
    sem_wait(&bin_sem);
    printf("Thread 1 entered critical section\n");
    sleep(2); // Simulate some work
    printf("Thread 1 leaving critical section\n");
    sem_post(&bin_sem);
    pthread_exit(NULL);
}

void* thread_func2(void* arg) {
    printf("Thread 2 waiting for semaphore...\n");
    sem_wait(&bin_sem);
    printf("Thread 2 entered critical section\n");
    sleep(2); // Simulate some work
    printf("Thread 2 leaving critical section\n");
    sem_post(&bin_sem);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the binary semaphore
    
    /*
     int sem_init(sem_t *sem, int pshared, unsigned int value);
    
    Parameters:

    sem: A pointer to the semaphore object to be initialized. The semaphore
     object is typically of type sem_t.

    pshared: An integer that specifies whether the semaphore is shared between
     processes or between threads of a process.
        If pshared is 0, the semaphore is shared between the threads of a process.
        If pshared is non-zero, the semaphore is shared between processes. 
        In this case, the semaphore should be located in a region of shared 
        memory accessible to all processes.

    value: An unsigned integer that specifies the initial value of the semaphore.
     This value represents the number of available resources. For a binary 
     semaphore, this value is typically set to 1. For a counting semaphore,
      it can be set to any non-negative integer representing the number of resources.    
    */
    
    sem_init(&bin_sem, 0, 1);

    // Create two threads
    pthread_create(&thread1, NULL, thread_func1, NULL);
    pthread_create(&thread2, NULL, thread_func2, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the semaphore
    sem_destroy(&bin_sem);

    return 0;
}


/*

   1. sem_t sem;
        Declares a semaphore.

   
   2. sem_init(&sem, 0, 1);
        Initializes the semaphore with a value of 1. The second argument is 0, 
        meaning the semaphore is shared between threads of the process.

   3. sem_wait(&sem);
        Decrements (waits on) the semaphore. If the semaphore value is greater
         than 0, it decrements the value and proceeds. If the value is 0, it 
         blocks until the value becomes greater than 0.

   4. sem_post(&sem);
        Increments (signals) the semaphore, waking up a blocked thread if any.

   5. sem_destroy(&sem);
        Destroys the semaphore.
*/


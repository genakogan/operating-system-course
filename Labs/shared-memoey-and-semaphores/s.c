

// A semaphore consists of two fields:

   // Numeric value: This field represents the current state of the semaphore.
   // Queue of processes waiting on it: This field holds a list of processes waiting for the semaphore.

//There are two operations that can be performed on the semaphore:

  // DOWN: Decreases the value of the semaphore by 1 and waits until the semaphore value is non-negative. (Also known as wait or P operation in some contexts)
  // UP: Increases the value of the semaphore by 1 and releases one of the processes waiting in the queue. (Also known as signal or V operation in some contexts)
  
// Types of semaphores mentioned:

    // Counting Semaphore:
      //  A counting semaphore maintains a numeric value, typically denoted as N, which represents the number of available resources or the maximum number of processes that can access a resource simultaneously.
       // The initial value of a counting semaphore is set to NN, and it controls access to the resource among processes.

    // Binary Semaphore:
       // A binary semaphore is a special case of a counting semaphore where the value can only be either 0 or 1.
       // When the value is 0, it indicates that the resource is unavailable, and when the value is 1, it allows one process to access the resource.
       // It effectively acts as a simple lock that allows or prevents access to the resource.

    // Mutex (Mutual Exclusion Semaphore):
       // A mutex semaphore is similar to a binary semaphore but with additional features for ensuring mutual exclusion among processes.
       // It also has values of 0 and 1, where 0 indicates that the resource is locked (in use), and 1 indicates that the resource is available (not in use).
       // Only the process that has acquired the mutex (set its value to 0) can release it (set its value back to 1). This ensures exclusive access to the resource by the locking process until it releases the mutex.

// In inter-process communication, semaphores are commonly used for synchronization and mutual exclusion between processes. They help coordinate access to shared resources and prevent race conditions. Each type of semaphore serves different purposes and offers different levels of control over resource access and synchronization among processes.

//=============================================================================================
//=============================================================================================
// The semget() function is used to create a new semaphore set or access an existing one. It is part of the System V IPC (Inter-Process Communication) mechanism in Unix-like operating systems. Here's an explanation of the semget() function:

 

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semget(key_t key, int nsems, int semflg);

//Parameters:

   // key: A unique key used to identify the semaphore set. This key is typically generated using the ftok() function based on a file path and a project identifier.
   // nsems: The number of semaphores in the semaphore set. This parameter is ignored if the semaphore set already exists.
   // semflg: Flags to specify additional options for creating or accessing the semaphore set. Common flags include:
   //     IPC_CREAT: Create the semaphore set if it does not already exist.
   //     IPC_EXCL: Fail if the semaphore set already exists. This flag is typically used in conjunction with IPC_CREAT to ensure exclusive creation of a new semaphore set.
   //     Additional permission flags (0666, 0600, etc.) to specify permissions for the semaphore set.

// Return Value:

   // If successful, semget() returns the semaphore set identifier (a non-negative integer), which can be used in subsequent semaphore-related system calls.
   // If an error occurs, semget() returns -1, and an error code is set in the errno variable.

// Behavior:

   // If the semaphore set identified by key already exists and the IPC_CREAT flag is not specified, semget() simply returns the identifier of the existing semaphore set.
   // If the semaphore set does not exist and IPC_CREAT is specified, semget() creates a new semaphore set with nsems semaphores and returns its identifier.
   // If both IPC_CREAT and IPC_EXCL are specified and the semaphore set already exists, semget() fails with an error (returning -1).

// Usage:

   // semget() is typically used before other semaphore-related functions (semop(), semctl()) to obtain a semaphore set identifier.
   // Once obtained, the semaphore set identifier can be used to perform semaphore operations and control access to shared resources among processes.
   
//=============================================================================================
//=============================================================================================


//The semop() function is used to perform semaphore operations on one or more semaphores within a semaphore set. It is part of the System V IPC (Inter-Process Communication) mechanism in Unix-like operating systems. Here's an explanation of the semop() function:

  //  Function Signature:

//#include <sys/types.h>
//#include <sys/ipc.h>
//#include <sys/sem.h>

int semop(int semid, struct sembuf *sops, size_t nsops);

//Parameters:

  //  semid: The identifier of the semaphore set on which the operations are to be performed. This identifier is typically obtained using the semget() function.
  //  sops: A pointer to an array of struct sembuf structures, each specifying a semaphore operation to be performed.
  //  nsops: The number of semaphore operations specified in the sops array.

 // struct sembuf:

 //   This structure defines a semaphore operation and is typically defined as follows:


   /*
    struct sembuf {
        unsigned short sem_num;  // Index of the semaphore in the semaphore set
        short sem_op;            // Operation to perform on the semaphore
        short sem_flg;           // Flags to specify operation behavior
    };
    */

       // sem_num: The index of the semaphore within the semaphore set. Semaphores are zero-indexed.
       // sem_op: The operation to be performed on the semaphore. It can be a positive value to increment the semaphore value, a negative value to decrement the semaphore value, or zero to perform a "wait" operation (similar to P or DOWN operation).
       // sem_flg: Flags to specify the behavior of the operation. Common flags include SEM_UNDO to perform automatic undo of operations if the process terminates abnormally and IPC_NOWAIT to perform the operation without blocking if it cannot be immediately completed.

// Return Value:

   // If successful, semop() returns 0.
   // If an error occurs, semop() returns -1, and an error code is set in the errno variable.

// Behavior:

   // The semop() function performs the semaphore operations specified in the sops array on the semaphore set identified by semid.
   // Multiple semaphore operations can be specified in a single semop() call by providing multiple struct sembuf structures in the sops array.
   // Semaphore operations are performed atomically, ensuring that no other process can interrupt the operations.
   // If a semaphore operation would result in a negative semaphore value, and the operation's sem_flg field does not include IPC_NOWAIT, the calling process may be blocked until the semaphore value becomes non-negative.
   // Semaphore operations can be used for tasks such as locking and unlocking resources, signaling events, and implementing critical sections. 
   
   
   
   
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define NUM_SEMAPHORES 3 // Number of semaphores in the array

// Define a struct to represent the semaphore array
struct SemaphoreArray {
    int semid; // Semaphore set identifier
    key_t key; // Unique key for the semaphore set
    int num_semaphores; // Number of semaphores in the array
};

// Function to create and initialize the semaphore array
void create_semaphore_array(struct SemaphoreArray *sa) {
    struct sembuf operations[NUM_SEMAPHORES];

    // Generate a unique key for the semaphore set
    if ((sa->key = ftok(".", 'S')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a semaphore set with NUM_SEMAPHORES semaphores
    if ((sa->semid = semget(sa->key, sa->num_semaphores, IPC_CREAT | 0666)) == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphore operations
    for (int i = 0; i < sa->num_semaphores; ++i) {
        operations[i].sem_num = i;   // Index of the semaphore
        operations[i].sem_op = 1;    // Increment semaphore value by 1
        operations[i].sem_flg = 0;   // No special flags
    }

    // Perform semaphore operations
    if (semop(sa->semid, operations, sa->num_semaphores) == -1) {
        perror("semop");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore array created and initialized successfully.\n");
}

// Function to delete the semaphore array
void delete_semaphore_array(struct SemaphoreArray *sa) {
    // Delete the semaphore set
    if (semctl(sa->semid, 0, IPC_RMID) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore array deleted.\n");
}

int main() {
    struct SemaphoreArray sa;

    sa.num_semaphores = NUM_SEMAPHORES;

    // Create and initialize the semaphore array
    create_semaphore_array(&sa);

    // Delete the semaphore array
    delete_semaphore_array(&sa);

    return 0;
}


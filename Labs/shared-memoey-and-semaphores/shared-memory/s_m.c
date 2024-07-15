#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <wait.h>
#define SEGSIZE 100

void exm1();
int exm2();
void exm3();



// Ways of inter-process communication

// 1. Shared Momory
// 2. Message Queue
// 3. Semaphores

// 1. Shared Momory:

// It allows processes that share it to access the same section of memory
// For example, an array, providing tha ability to read from and write to any cell in the array.


void main(void){
   //exm1();
   //exm2();
   exm3();
   
}

// a: Creating a shared key

// key_t ftok(const char *pathname, int proj_id);

// Parameters
// pathname: A pointer to null-terminated string containing the path to existing file.
// proj_id: An integer representing the project identifier. It's usuakky a single byte.

// #include <sys/types.h> and #include <sys/ipc.h>

// Function return: unique key (non-negative value), if error accurs return -1

void exm1(){
    key_t key = ftok("shas.txt", 'A');
    printf("key is %d\n",key);

}




// b: Creating or accessing a shared memory segment

//  int shmid = shmget(key_t key, size_t shm_size, int shmflg);

//Parameters:
    //key: A unique key generated typically using the ftok function, which identifies the shared memory segment.
    //size: The desired size, in bytes, of the shared memory segment.
    //flags: Flags indicating the desired behavior, such as whether to create the segment if it doesn't exist (IPC_CREAT), to fail if the segment already exists (IPC_EXCL), and permission flags.

//Return Value:
    //If successful, shmget returns the identifier (shmid) of the shared memory segment.
    //If it fails, it returns -1, and an error code is set in the errno variable.

//Usage: Typically, after obtaining the identifier using shmget, other functions like shmat (to attach the shared memory segment) and shmdt (to detach it) are used to manipulate the shared memory.

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int exm2() {
    key_t key = ftok("shared_memory_key_file", 'A'); // Generating a unique key
    int shm_size = 1024;  // Size of the shared memory segment (bytes)

    // Creating or accessing the shared memory segment
    int shmid = shmget(key, shm_size, IPC_CREAT | 0666);

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    printf("Shared memory segment created/accessed successfully, shmid: %d\n", shmid);

    return 0;
}


// Common errors that may occur when calling the function shmget:

   // Requested memory size is smaller than allowed: If the requested size of memory is smaller than the minimum allowed size, the system may return an error indicating that the requested size is too small.

   // System unable to allocate memory: If the system is unable to allocate the requested amount of memory for the shared memory segment due to system-wide memory constraints or resource limitations, shmget may fail and return an error indicating that it couldn't allocate memory.

   // Insufficient permissions: If the process does not have the necessary permissions to create or access the shared memory segment, shmget will fail. This can occur if the process lacks the appropriate permissions for the specified key or if the process does not have the required permissions for shared memory operations.
   
 // c: Attach a shared memory segment
 
 // void *shmat(int shmid, const void *shmaddr, int shmflg);
 
 // Parameters:
 
     // shmid: Identifier of the shared memory segment obtained from shmget().
    // shmaddr: Address at which the segment should be attached. Typically set to NULL to let the system choose a suitable address.
    // shmflg: Flags that specify the attachment mode. Common flags include SHM_RDONLY for read-only access and 0 for read-write access.
    
// Return Value:

    // If successful, shmat() returns the starting address of the attached shared memory segment.
    // If it fails, it returns (void *) -1, indicating an error, and an error code is set in the errno variable
    
    



void exm3() {
    key_t key;
    int shmid;
    char *segptr;
    int r_pid;
    int status;

    // Generate a unique key
    key = ftok("shas.txt", 1);
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Attempt to create or access the shared memory segment
    shmid = shmget(key, SEGSIZE, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid == -1) {
        printf("Segment memory segment already exists, attempting to attach...\n");
        // Segment already exists, try to attach to it
        shmid = shmget(key, SEGSIZE, 0);
        if (shmid == -1) {
            perror("shmget");
            exit(1);
        }
    }

    // Attach the shared memory segment
    segptr = shmat(shmid, NULL, 0);
    if (segptr == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    // Fork a child process
    r_pid = fork();
    if (r_pid == -1) {
        perror("fork");
        exit(1);
    } else if (r_pid == 0) {
        // Child process
        printf("Child with PID number: %d (parent PID is %d) writes a text to the shared memory\n", getpid(), getppid());
        strcpy(segptr, "This text is written by the child process");
        exit(0); // Exit child process
    } else {
        // Parent process
        wait(&status);
        printf("I am the father\n");
        printf("The following text is received by the child process with PID number %d: %s\n", r_pid, segptr);
    }

    // Detach the shared memory segment
    if (shmdt(segptr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Only remove the shared memory segment if it was newly created
    if (shmid != -1) {
        if (shmctl(shmid, IPC_RMID, 0) == -1) {
            perror("shmctl");
            exit(1);
        }
    }
}

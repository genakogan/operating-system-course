#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <wait.h>
#define SEGSIZE 100



int main()
{
	// ftok to generate unique key
	key_t key = ftok("t.txt", 65);

	// shmget returns an identifier in shmid
	int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

	// shmat to attach to shared memory
	char* str = (char*)shmat(shmid, (void*)0, 0);

	printf("Write Data\n");
	strcpy(str,"Hello i write to shared memory");

	printf("Data written in memory: %s\n" str);

	// detach from shared memory
	shmdt(str);

	return 0;
}



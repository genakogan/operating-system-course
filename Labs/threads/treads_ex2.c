#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void *ThreadFun(void *vargp){
	sleep(1);
	pthread_t pid_th1 = pthread_self();
	printf("Hello, i am thread! My pid is: %ld\n", pid_th1);
	return NULL;
}


int main(void){
	pthread_t thread_id;
	printf("Before thread\n");
	pthread_create(&thread_id, NULL, ThreadFun, NULL);
	pthread_join(thread_id,NULL);
	printf("After Thread\n");
	exit(0);
}

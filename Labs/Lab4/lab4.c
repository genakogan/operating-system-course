#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>

// gcc thread_program.c -o thread_program -lpthread
// ./thread_program

void example1();
void *thread_function(void *args);

void example2();
void *threadFun(void* vargp);

pthread_t tmp_thread;
void example3();
void *func_one(void *ptr);

#define NTREADS 20
void example4();
void *thread(void *vargp);




int main(int argc, char **argv)
{

	//example1();
	//example2();
	//example3();
	//example4();
	example5();
	//example6();
	return 0;

}
//===============================================================
void example1()
{
	pthread_t thread_id;
	printf("Before Thread\n");
	pthread_create(&thread_id,NULL,thread_function,NULL);
	pthread_join(thread_id,NULL);
	printf("After Thread, the pid of thread is: %ld", thread_id);
	exit(0);
}

void *thread_function(void *args){
	sleep(1);
	printf("Printing this from Thread\n");
	
}
//===============================================================
void example2()
{
	pthread_t thread_id;
	printf("Before Thread\n");
	pthread_create(&thread_id,NULL,threadFun,NULL);
	pthread_join(thread_id,NULL);
	printf("After Thread, the pid of thread is: %ld", thread_id);
	exit(0);
}
void *threadFun(void* vargp){
	sleep(1);
	pthread_t pid_th1 = pthread_self();
	printf("Hello, i am thread! My pid is: %ld\n", pid_th1);

}
//===============================================================
void example3()
{
	//pthread_t thread_id;
	pthread_create(&tmp_thread,NULL,func_one,NULL);
	pthread_join(tmp_thread,NULL);
}
void *func_one(void *ptr){
	printf("tmp_thread is is: %ld\n pthread_self() is %ld\n", tmp_thread, pthread_self());
	if(pthread_equal(tmp_thread, pthread_self())!=0) printf("Equal\n");
	else printf("Not Equal\n");
}
//===============================================================
void example4()
{
	int i;
	pthread_t tid;
	for(i=0;i<NTREADS;i++)	{pthread_create(&tid,NULL,thread,NULL);}
	pthread_exit(NULL);
	
}
void *thread(void *vargp){
	static int cnt = 0;
	
	cnt++;
	printf("cnt res %d\n",cnt);
}
//===============================================================

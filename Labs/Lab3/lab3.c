#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
void example1();
void example2();
void example3();
void example4();
void example5();
void example6();
void example7();

int main(int argc, char **argv)
{

	//example1();
	//example2();
	//example3();
	//example4();
	//example5();
	//example6();
	example7();
	return 0;

}
void example1()
{
	printf("x = %d\n", getpid());
	printf("y = %d\n", getppid());
}
void example2()
{
	fork();
	printf("Hello\n");
}
void example3()
{
	printf("Hello");
	fork();
	printf("Bye");

}
void example4()
{
	fork();
	pid_t myPID = getpid(), pPID = getppid();
	printf("My PID is %d and my parent's PID is %d\n", myPID, pPID);
}
void example5()
{
	pid_t pid=fork(), x=1;
	if (pid == 0) printf("Child has x = %d\n", ++x);
	else printf("Parent has x = %d\n", --x);
}

/*
	Parent has x = 0
	Child has x = 2
		(or)
	Child has x = 2
	Parent has x = 0

*/
void example6()
{
	pid_t pid, status, cpid;
	pid = fork();
	if (pid == 0){
		exit(0);
		printf("I am the child process and my pid is %d\n", getpid() );

	}else{
		//cpid = wait(NULL);
		cpid = wait(&status);
		printf("I am the father process\n");
		printf("My child with pid %d exited and returned status %d\n", cpid, status);
	}
}
void example7(){
	for(int i=0;i<5;i++){
		if(fork()==0){
		printf("[son] pid %d from [parent] pid %d\n", getpid(), getppid());
		//exit(0);
		}
	}
	for(int i=0;i<5;i++){
		printf("I am pid %d pid %d\n", getpid(), getppid());
		wait(NULL);
	}
}




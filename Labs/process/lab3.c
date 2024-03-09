#include <stdio.h>
#include <unistd.h> // for fork 
#include <wait.h> //for wait
#include <stdlib.h> // for exit
//======================================

void example1(){
	fork();
	printf("Hello\n");
}

//======================================

void example2(){
	fork();
	fork();
	fork();
	printf("Hello\n");
}

//======================================

void example3(){
	printf("Hello\n");
	fork();
	printf("By\n");
}

//======================================

void example4(){
	fork();
	pid_t myPID = getpid();
	pid_t pPID = getppid();
	printf("My myPID is %d\n", myPID);
	printf("My pPID is %d\n", pPID);
}

//======================================

void example5(){
	pid_t pid, status;
	
	if(fork()==0){
		printf("I am the son process and my pid is %d\n", pid);
	
	}
	else{
		pid = wait(&status);
		printf("I am the father process.\n");
		printf("My childe with pid %d  was exited and returned status %d\n", pid, status);
				
		
	}
}

//======================================

void example6(){
	for(int i =0; i<1; i++){
		if(fork()==0){
			printf("[son] pid %d from [parent] pid %d\n", getpid(),getppid());
			//exit(0);
		}
	}
	for(int i =0; i<1; i++){
		printf("My pid is %d, my parent pid is %d\n",getpid(),getppid());
		wait(NULL);
	
	}
}

//======================================

void example7(){
	int i, stat;
	pid_t pid[5];
	for(i=0;i<5; i++){
	
		if (0 == (pid[i] = fork())){
			sleep(1);
			exit(100+i);
		}
	}
	
	for(i=0;i<5; i++){
		pid_t cpid = waitpid(pid[i],&stat,0);
		if(WIFEXITED(stat))
			printf("Child %d terminated with status %d\n", cpid, WEXITSTATUS(stat));
	
	}
}

//======================================

void example8(){
	
	if (execlp("ls","ls", "-l",NULL) == -1){
		printf("Error");	
	}
		
}

//======================================

void example9(int argc, char *argv[]){
	/*[ "./t","/bin/ls" ,"-l"]*/
	char *program = argv[1];
	// Starting from argc[1], we pass all the argiments to the program 
	char **args = &argv[1];
	args[argc -1] = NULL; 
	if(execv(program, args)==-1){
		perror("execv");
		exit(EXIT_FAILURE);
	}
	printf("This won't be printed is execv succeeds\n");
}

//======================================

int main(int argc, char *argv[]){
	
	example1();
	//example2();
	//example3();
	//example4();
	//example5();
	//example6();
	//example7();
	
	//example8();
	//example9(argc, argv);
	return 0;
	
}

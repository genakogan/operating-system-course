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
	for(int i =0; i<4; i++){
		if(fork()==0){
			printf("[son] pid %d from [parent] pid %d\n", getpid(),getppid());
			//exit(100+i);
		}
	}
	for(int i =0; i<4; i++){
		printf("My pid is %d, my parent pid is %d\n",getpid(),getppid());
		wait(NULL);
	
	}
}

//======================================

void example7(){
	int i;
	
	pid_t pid[5], stat;
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


// Macros for Interpreting the Status (see example8)
// WIFEXITED(status): Returns true if the child terminated normally.
// WEXITSTATUS(status): Returns the exit status of the child. This macro should only be used if WIFEXITED(status) returned true.
// WIFSIGNALED(status): Returns true if the child process was terminated by a signal.
// WTERMSIG(status): Returns the number of the signal that caused the child process to terminate. This macro should only be used if WIFSIGNALED(status) returned true.
// WIFSTOPPED(status): Returns true if the child process is currently stopped.
// WSTOPSIG(status): Returns the number of the signal that caused the child process to stop. This macro should only be used if WIFSTOPPED(status) returned true.
// WIFCONTINUED(status): Returns true if the child process was resumed by delivery of SIGCONT.


//======================================

int example8(){
pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) is running...\n", getpid());
        sleep(2); // Simulate some work
        printf("Child process (PID: %d) is terminating...\n", getpid());
        _exit(42); // Terminate child with exit status 42
    } else {
        // Parent process
        int status;
        pid_t child_pid = wait(&status);

        if (child_pid > 0) {
            if (WIFEXITED(status)) {
                int exit_status = WEXITSTATUS(status);
                printf("Child process (PID: %d) terminated with exit status %d\n", child_pid, exit_status);
            } else if (WIFSIGNALED(status)) {
                int signal_number = WTERMSIG(status);
                printf("Child process (PID: %d) terminated due to signal %d\n", child_pid, signal_number);
            } else if (WIFSTOPPED(status)) {
                int stop_signal = WSTOPSIG(status);
                printf("Child process (PID: %d) stopped due to signal %d\n", child_pid, stop_signal);
            } else if (WIFCONTINUED(status)) {
                printf("Child process (PID: %d) was resumed by SIGCONT\n", child_pid);
            }
        } else {
            // Handle error
            perror("wait");
        }
    }

    return 0;

}
//======================================

int global_var = 10;

void example9(){

    pid_t pid;
    
    pid = fork();
    
    if(pid<0){
        perror("Fork failed");
        exit(1);
    }else if (pid==0){
        printf("Child process\n");
        printf("global_var: %d\n",global_var);
        global_var +=5;
        printf("Modifie value of global_var: %d\n",global_var);
        
    }
    else{
        wait(NULL);
        printf("parent process\n");
        printf("global_var: %d\n",global_var);
        global_var -=3;
        printf("Modifie value of global_var: %d\n",global_var);
    }

}


//======================================

void example10(){
	
	if (execlp("ls","ls", "-l",NULL) == -1){
		printf("Error");	
	}
		
}

//======================================

void example11(int argc, char *argv[]){
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
	
	//example1();
	//example2();
	//example3();
	//example4();
	//example5();
	//example6();
	//example7();
	//example8();
	// example9();
	//example10();
	//example11(argc, argv);
	return 0;
	
}

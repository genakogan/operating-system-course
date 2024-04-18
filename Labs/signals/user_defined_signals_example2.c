#include <stdio.h
#include <wait.h>
#include <signal.h>
#include <stdlib.h>


/*SIGUSR1 and SIGUSR2 are signals in Unix-like operating
systems that are reserved for user-defined purposes.
Their names stand for "User Signal 1" and "User Signal 2,"
respectively.

These signals are provided to allow applications
to define their own custom signaling mechanisms
beyond the standard set of signals provided by
the operating system. They can be used by a process
to communicate with itself or with other processes,
typically for special purposes like triggering specific
actions, synchronizing processes, or passing information.

Since these signals are not assigned any specific
behavior by default, it's up to the programmer to
define how they should be handled within their
application. They can be used for a wide variety
of purposes depending on the needs of the application
being developed.*/


pid_t pid;
int counter = 0;

void handler1(int sig){
    counter++;
    printf("cointer = %d\n", counter);
    kill(pid,SIGUSR1);
}

void handler2(int sig){
    counter += 3;
    printf("cointer = %d\n", counter);
    exit(0);
}

int main(){
    int status;
    signal(SIGUSR1,handler1);
    if((pid = fork())==0){
        signal(SIGUSR1,handler2);
        kill(getppid(),SIGUSR1);
        while(1);
    }
    else{
        wait(&status);
        counter+=4;
        printf("cointer = %d\n", counter);
    }
}


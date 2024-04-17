#include <stdio.h
#include <wait.h>
#include <signal.h>
#include <stdlib.h>
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


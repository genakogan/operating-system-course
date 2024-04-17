#include <stdio.h>
#include <signal.h>
#include <wait.h>
int val =10;
void handler(int sig){val += 5}

int main(void){
    pid_t pid;

    /*
    When a child process terminates (either normally or abnormally),
    the operating system sends the SIGCHLD signal to the parent process
    to notify it about the termination of its child process. The parent
    process can then handle this signal and take appropriate action,
    such as cleaning up resources associated with the terminated child
    process or spawning new child processes.
    */
    signal(SIGCHLD, handler);
    if ((pid=fork())==0){
        val -= 3;
        exit(0);
    }
    waitpid(pid, NULL,0):
    printf("val = %d\n", val);
    exit(0);
}
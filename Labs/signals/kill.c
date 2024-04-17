#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void quitproc()
{
    printf("\n i am child: my father end me \n");
    exit(0);
}

int main()
{
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    else if (pid == 0){
        signal(SIGQUIT, quitproc);
        printf("\n i am child: waiting for signal \n");
        for(;;);
    }
    else{
        printf("\n i am father : i send signal quit to my child \n");
        sleep(1);
        kill(pid , SIGQUIT);
        wait(NULL); // Wait for child to exit
    }
    return 0;
}

#include <signal.h>
#include <stdio.h>
#include <stdlib.h> 

int i=0;
void my_handler(int sig){
    printf("Receive signal %d, CTRL-C pressed, num of presses: %d\n", sig, i+1);
    i=i+1;
    if (i==5){
        printf("The process will exit now");
        exit(0);
    }
}

int main(){
    signal(SIGINT,my_handler);
    while(1);
    return 0;
}

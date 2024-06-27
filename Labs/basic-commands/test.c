#include <stdio.h>

int main(int args, char *argv[]){
    printf("lab1\n");
    printf("args %d, argv %s\n",args, argv[1]); 
    for(int i =0; i<args; i++)
        printf("arg %d: %s\n",i, argv[i]);
        
    return 0;
}


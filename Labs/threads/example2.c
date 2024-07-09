#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *foo1(void *arg){
 int num_times = *((int*)arg);
 
 for(int i; i<num_times; i++){
  printf("Hello\n");
 
 }
 
}


int main(void){
  pthread_t thread;
  int num_times = 3;
  
  if(pthread_create(&thread,NULL, foo1, (void*)&num_times)!=0){
  fprintf(stderr,"Error");
  return 1;
  }
  
  if (pthread_join(thread,NULL)!=0){
    fprintf(stderr,"Error");
   return 1;
  }
  
  printf("Main exiting\n");
 
 
 return 0;
}

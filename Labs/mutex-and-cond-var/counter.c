#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

#define MAX_THREADS 3
#define MAX_COUNT 10

int counter = 0;
pthread_mutex_t mutex;
pthread_cond_t condition;


void threads_func(void *arg){
    int thread_id= *((int *)arg);
    while(1){
        pthread_mutex_lock(&mutex);
        while(counter<MAX_COUNT){
            printf("thread_id %d: counter = %d\n", thread_id,counters);
            counter++;
        }
        pthread_cond_signal(&condition);

        pthread_mutex_unlock(&mutex);

        break;

    }
    pthread_exit(NULL);
}



int main(void){

    pthread_t threads[MAX_THREADS];
    int thread_ids[MAX_THREADS];

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&condition,NULL);

    for(int i = 0; i<MAX_THREADS;i++){
        thread_ids[i]=i;
        pthread_create(&threads[i], NULL, threads_func, &thread_ids[i]);

    }
    for(int i =0;i<MAX_THREADS;i++){
        pthread_join(threads[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);

    return 0;
}
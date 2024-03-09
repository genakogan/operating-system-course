#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_t tmp_thread;

void *func_one(void *ptr) {
    printf("tmp_thread id is: %lu\npthread_self is %lu\n", (unsigned long)tmp_thread, (unsigned long)pthread_self());

    if (pthread_equal(tmp_thread, pthread_self()) != 0)
        printf("Equal\n");
    else
        printf("Not equal\n");

    return NULL;
}

int main(void) {
    pthread_create(&tmp_thread, NULL, func_one, NULL);
    pthread_join(tmp_thread, NULL);

    exit(0);
}


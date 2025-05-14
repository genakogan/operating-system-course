
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_COUNT 10

int counter = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void* incrementer(void* arg) {
    for (int i = 0; i < MAX_COUNT / 2; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        printf("Incrementer thread %ld: counter = %d\n", (long)arg, counter);

        if (counter >= MAX_COUNT) {
            pthread_cond_signal(&cond);  // Сигналим ожидающему потоку
        }

        pthread_mutex_unlock(&mutex);
        sleep(1); // Для видимости и избежания гонки
    }
    return NULL;
}

void* waiter(void* arg) {
    pthread_mutex_lock(&mutex);

    while (counter < MAX_COUNT) {
        printf("Waiter thread waiting... counter = %d\n", counter);
        pthread_cond_wait(&cond, &mutex);  // Засыпаем, пока не сигналят
    }

    printf("Waiter thread proceeding! Final counter = %d\n", counter);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&t1, NULL, incrementer, (void*)1);
    pthread_create(&t2, NULL, incrementer, (void*)2);
    pthread_create(&t3, NULL, waiter, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}

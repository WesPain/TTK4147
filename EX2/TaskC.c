#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
long globalVar = 0;
sem_t mutex;
// Note the argument and return types: void*
void* fn(void* args){
    long localVar = 0;
    for(int i = 0; i<50000000; i++){

      localVar++;
      sem_wait(&mutex);
      globalVar++;
      sem_post(&mutex);
    }
    sem_wait(&mutex);
    printf("Vars: %ld, %ld\n", localVar, globalVar);
    sem_post(&mutex);
    return NULL;
}
int main(){
    sem_init(&mutex, 0, 1);
    pthread_t threadHandle1;
    pthread_t threadHandle2;
    pthread_create(&threadHandle1, NULL, fn, NULL);
    pthread_create(&threadHandle2, NULL, fn, NULL);
    pthread_join(threadHandle1, NULL);
    pthread_join(threadHandle2, NULL);
    sem_destroy(&mutex);
}

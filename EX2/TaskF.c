

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
struct thread_args
 {
      pthread_mutex_t *mtxLeft;
      pthread_mutex_t *mtxRight;
      int threadNum;
};

struct thread_args Structthread1;

void* philosopher(void* mtxEs){

    struct thread_args *args = (struct thread_args *)mtxEs;
    pthread_mutex_t *mtxRight = args->mtxRight;
    pthread_mutex_t *mtxLeft = args->mtxLeft;

    while(1){
      printf("Runing thread: %d\n", args->threadNum);
      pthread_mutex_lock(mtxLeft);
        pthread_mutex_lock(mtxRight);
          sleep(1);
        pthread_mutex_unlock(mtxRight);
      pthread_mutex_unlock(mtxLeft);

    }
    return NULL;
}

int main(){
    printf("SOMEthing\n");
    pthread_mutex_t mtx1, mtx2, mtx3, mtx4, mtx5;

    pthread_mutex_init(&mtx1, NULL);
    pthread_mutex_init(&mtx2, NULL);
    pthread_mutex_init(&mtx3, NULL);
    pthread_mutex_init(&mtx4, NULL);
    pthread_mutex_init(&mtx5, NULL);

    pthread_t threadHandles[5];

    struct thread_args argsPhilosopher1;
    struct thread_args argsPhilosopher2;
    struct thread_args argsPhilosopher3;
    struct thread_args argsPhilosopher4;
    struct thread_args argsPhilosopher5;

    argsPhilosopher1.mtxLeft = &mtx1;
    argsPhilosopher1.mtxRight = &mtx2;
    argsPhilosopher2.mtxLeft = &mtx2;
    argsPhilosopher2.mtxRight = &mtx3;
    argsPhilosopher3.mtxLeft = &mtx3;
    argsPhilosopher3.mtxRight = &mtx4;
    argsPhilosopher4.mtxLeft = &mtx4;
    argsPhilosopher4.mtxRight = &mtx5;
    argsPhilosopher5.mtxLeft = &mtx5;
    argsPhilosopher5.mtxRight = &mtx1;

    argsPhilosopher1.threadNum = 1;
    argsPhilosopher2.threadNum = 2;
    argsPhilosopher3.threadNum = 3;
    argsPhilosopher4.threadNum = 4;
    argsPhilosopher5.threadNum = 5;

    pthread_create(&threadHandles[0], NULL, philosopher, (void *) &argsPhilosopher1);
    pthread_create(&threadHandles[1], NULL, philosopher, (void *) &argsPhilosopher2);
    pthread_create(&threadHandles[2], NULL, philosopher, (void *) &argsPhilosopher3);
    pthread_create(&threadHandles[3], NULL, philosopher, (void *) &argsPhilosopher4);
    pthread_create(&threadHandles[4], NULL, philosopher, (void *) &argsPhilosopher5);

    pthread_join(threadHandles[0], NULL);
    // for(long i = 0; i < 5; i++){
    //     pthread_join(threadHandles[i], NULL);
    // }

    // pthread_mutex_destroy(&mtx);
    return 0;
}

// C program to demonstrate working of Semaphores
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t S;

void* thread1(void* arg)
{
    //wait
    sem_wait(&S);
    printf("\nP1 Entered..\n");
  
    //critical section
    sleep(4);
      
    //signal
    printf("\nP1 Just Exiting...\n");

    sem_post(&S);
    // semop(&S,SIGNAL,1);
}
void* thread2(void* arg)
{
    //wait
    sem_wait(&S);
    printf("\nP2 Entered..\n");
  
    //critical section
    sleep(4);
      
    //signal
    printf("\nP2 Just Exiting...\n");
    // sem_post(&S);
}

int main(){
    sem_init(&S, 0, 1);
    pthread_t t1,t2,t3,t4;
    pthread_create(&t1,NULL,thread1,NULL);
    // sleep(2);
    pthread_create(&t2,NULL,thread1,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&S);
    return 0;
}
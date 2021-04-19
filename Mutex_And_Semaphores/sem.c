// C program to demonstrate working of Semaphores
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t S;
sem_t B;
sem_t C;
sem_t D;
void* thread1(void* arg)
{
  
    printf("\nP1 Entered..\n");
  
    //critical section
    sleep(2);
      
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
    sleep(2);
      
    //signal
    printf("\nP2 Just Exiting...\n");
    sem_post(&S);
    sem_post(&B);
    
    
}

void* thread3(void* arg)
{
    //wait
    sem_wait(&S);
    printf("\nP3 Entered..\n");
  
    //critical section
    sleep(2);
      
    //signal
    printf("\nP3 Just Exiting...\n");
    sem_post(&S);
    sem_post(&C);
}

void* thread4(void* arg)
{
    //wait
    sem_wait(&B);
    printf("\nP4 Entered..\n");
  
    //critical section
    sleep(2);
      
    //signal
    printf("\nP4 Just Exiting...\n");
    sem_post(&D);
}

void* thread5(void* arg)
{
    // wait
    sem_wait(&B);
    sem_wait(&C);
    printf("\nP5 Entered..\n");
  
    //critical section
    sleep(2);
      
    //signal
    printf("\nP5 Just Exiting...\n");
    sem_post(&B);
  
}
void* thread6(void* arg)
{
    // wait
    sem_wait(&D);
    printf("\nP6 Entered..\n");
  
    //critical section
    sleep(2);
      
    //signal
    printf("\nP6 Just Exiting...\n");
   // sem_post(&B);
  
}

int main(){
    sem_init(&S, 0, 0);
    sem_init(&B, 0, 0);
    sem_init(&C, 0, 0);
    sem_init(&D, 0, 0);
    pthread_t t1,t2,t3,t4,t5, t6;
    pthread_create(&t1,NULL,thread1,NULL);
    pthread_create(&t2,NULL,thread2,NULL);
    pthread_create(&t3,NULL,thread3,NULL);
    pthread_create(&t4,NULL,thread4,NULL);
    pthread_create(&t5,NULL,thread5,NULL);
    pthread_create(&t6,NULL,thread6,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_join(t5,NULL);
    pthread_join(t6,NULL);
    sem_destroy(&S);
    sem_destroy(&B);
    sem_destroy(&C);
    sem_destroy(&D);
    return 0;
}

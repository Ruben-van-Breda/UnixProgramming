/**
 * Ruben van Breda 
 * COMP20180 OS Assignment 2 Browser and Update
 */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int count = 0;
sem_t s_db;
sem_t s_count;

void *browser(void *arg)
{
    sem_wait(&s_count);
    count++;
    if (count == 1)
        sem_wait(&s_db);
    sem_post(&s_count);

    // Critical Section
    printf("browser is browsing...\n");

    sem_wait(&s_count);
    count--;
    if(count==0){
        sem_post(&s_db);
    }
    sem_post(&s_count);

}

void *updater(void *arg)
{
    sem_wait(&s_db);
    // Critical Section
    printf("updater is updating...\n");
    sem_post(&s_db);
}
int main()
{
    sem_init(&s_db, 0, 1);
    sem_init(&s_count, 0, 1);
    pthread_t b1;
    pthread_t u1;

    pthread_create(&b1, NULL, browser, NULL);
    pthread_create(&u1, NULL, updater, NULL);

    pthread_join(b1, NULL);
    pthread_join(u1, NULL);
    sem_destroy(&s_db);
    sem_destroy(&s_count);
}
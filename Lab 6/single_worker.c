#include "lab6.h"
#include <time.h>
#include <sys/wait.h>
#define NUMTHREADS 1
double sroots[];

void square_roots()
{
    for (int i = 0; i < 100; i++)
    {
        sroots[i] = sqrt(i);
    }


}
void *TaskCode(void *argument)
{
    int tid;
    tid = *((int *)argument);

    printf("Hello World! It’s me, thread %d!\n", tid);
    /* optionally: insert more useful stuff here */
    square_roots();
  
    return NULL;
}
int main()
{

    pthread_t threads[NUMTHREADS];
    int thread_args[NUMTHREADS];
    int rc, i = 0;
 
    thread_args[i] = i;
    printf("In main: creating thread %d\n", i);
    rc = pthread_create(&threads[i], NULL, TaskCode, (void *)&thread_args[i]);
    assert(0 == rc);
    
    /* wait for all threads to complete */ 
    rc = pthread_join(threads[i], NULL);
    assert(0 == rc); // assert that the thread has been freed of the resources
  
    printf("In main: \n");
    for (int i = 0; i < 100; i++)
    {
        printf("[%d] = %f\n", i, sroots[i]);
    }
    return 0;
}
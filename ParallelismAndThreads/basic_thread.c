#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
#define NUMTHREADS 5
void *TaskCode(void *argument) {
	int tid ;
	tid = *((int *) argument);
	printf("Hello World! It’s me, thread %d!\n", tid);
	/* optionally: insert more useful stuff here */
	return NULL;
}
int main(void) {
	pthread_t threads[NUMTHREADS]; 
	int thread_args[NUMTHREADS]; 
	int rc, i;
	/* create all threads */
	for (i=0; i<NUMTHREADS; ++i) {
		thread_args[i] = i;
		printf("In main: creating thread %d\n", i);
		rc = pthread_create(&threads [ i ] , NULL, TaskCode , (void *)&thread_args[i]);
        assert(0 == rc);
	}
	/* wait for all threads to complete */ 
	for (i=0; i<NUMTHREADS; ++i) {
		rc = pthread_join(threads[i], NULL);
		assert(0 == rc);
	}
	exit (EXIT_SUCCESS) ;
}
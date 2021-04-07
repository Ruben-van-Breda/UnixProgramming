#include "A3.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Matrix.c"
#include <assert.h>
#define NUMTHREADS 1
int main(){
    float** A = getMatrix(); 
    float** B = getMatrix(); 

    printf("\nMatrix A:\n");
    displayMatrix(A);
    printf("\nMatrix B:\n");
    displayMatrix(B);

    float** C = multiplyMatrix(A,B);
    printf("\nMatrix C:\n");
    displayMatrix(C);
    return EXIT_SUCCESS;
}

void createThread(){
    pthread_t threads[NUMTHREADS]; 
	int thread_args[NUMTHREADS]; 
	int rc, i;
	/* create all threads */
	for (i=0; i<NUMTHREADS; ++i) {
		thread_args[i] = i;
		printf("In main: creating thread %d\n", i);
		rc = pthread_create(&threads [ i ] , NULL, ThreadFunc , (void *)&thread_args[i]);
        assert(0 == rc);
	}
	/* wait for all threads to complete */ 
	for (i=0; i<NUMTHREADS; ++i) {
		rc = pthread_join(threads[i], NULL);
		assert(0 == rc);
	}
}

void * ThreadFunc(void *argument){

}
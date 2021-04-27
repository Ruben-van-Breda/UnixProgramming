#include "Matrix.c"
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
#define NUMTHREADS 3

void *TaskCode(void *argument);

SomeMatrix A;
SomeMatrix B;
SomeMatrix C;
int x = 5;
pthread_mutex_t mutexsum;

void *TaskCode(void *argument) {
	int tid ;
	tid = *((int *) argument);
    //C.array[0][tid] += 1;
    x += 1;
	printf("Hello World! It’s me, thread %d!\n", tid);
	/* optionally: insert more useful stuff here */
	return NULL;
}

void *printMatrix(void* argument){
    // Block
    pthread_mutex_lock (&mutexsum);
    
    int arg = *((int*)argument);
    printf("\n%c\n",arg==0?'A':'B');
    if(arg == 0){
         displayMatrix(A);
    }
    if(arg == 1){
         displayMatrix(B);
    }
    pthread_mutex_unlock (&mutexsum);
    return NULL;
}
void *Multiply(void* argument){
    // Block
    pthread_mutex_lock (&mutexsum);
    int arg = *((int *)argument);
    SomeMatrix slice = GetRow(arg, A);
    SomeMatrix vector = MultiplyBySlice(slice,B,arg);
    C.array[arg] = *vector.array;
    displayMatrix(vector);
    pthread_mutex_unlock (&mutexsum);
    pthread_exit((void*) 0);
    return NULL;
}

int main(){

    A = createA(3);
    B = createB(3);
    C.array = create2DArray(3,3);
    C.size = 3;
    C.rows = C.cols = 3;

    /* Threads */
    pthread_t threads[NUMTHREADS]; 
    int thread_args[NUMTHREADS];

    pthread_mutex_init(&mutexsum, NULL);
    // thread_args[0] = A;
    // thread_args[1] = B;

    int i; int rc; // pthread_create return
    for(int i = 0; i < NUMTHREADS; i++){
        thread_args[i] = i;
        printf("In main: creating thread %d\n", i);
        rc = pthread_create(&threads [ i ] , NULL, Multiply , (void *)&thread_args[i]);
        assert(rc == 0); // assert that the pthread creation was successful
       
    }

    /* wait for all threads to complete */ 
	for (i=0; i<NUMTHREADS; ++i) {
		rc = pthread_join(threads[i], NULL);
		assert(0 == rc);
	}
    printf("In main: x = %d\n", x);
    displayMatrix(C);
    free (A.array); free (B.array);
    pthread_mutex_destroy(&mutexsum);
    return EXIT_SUCCESS;
}


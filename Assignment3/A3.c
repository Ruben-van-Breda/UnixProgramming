#include "A3.h"

int N = 2; // default value is 2
int numOfWorkers = 1;

int main(){

	// Get size of matrices
	printf("Enter size of n: ");
	scanf("%d",&N);


    float** A = createA(); 
    float** B = createB(); 

    printf("\nMatrix A:\n");
	for(int r = 0 ; r < 3; r ++){
		for(int c = 0; c < 3; c++){
			printf("%.02f ",A[r][c]);
		}
		printf("\n");
	}
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
#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#define NUMTHREADS 5
void *PrintHello(void *threadid) {
	long tid ;
	tid = *((long*)threadid);
	printf("Hello World! It ’s me, thread #%ld!\n", tid);
	pthread_exit (NULL) ; 
}
	
int main (int argc, char *argv[]) { 
	pthread_t threads[NUMTHREADS]; 
	int rc; 
	long t;
	for(t=0; t<NUMTHREADS; t++){
		printf("In main: creating thread %ld\n", t);
		// Not good −− open to race condition, NUll is the properites argument. Null means use defualt properties. Defualt stack-size created.
		rc = pthread_create(&threads[t], NULL, PrintHello , (void *)&t);
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	exit (0) ; 
}
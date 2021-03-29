#include <pthread.h>
void* threadfunction(void* arg) {
	int* incoming = (int*)arg; 
	(* incoming )++;
	return NULL;
}
int main(void) {
	pthread_t threadID ; 
	void* exitstatus ; 
	int value ;
	value = 42;
	pthread_create(&threadID,NULL,threadfunction,&value); 
	pthread_join(threadID,&exitstatus);
	return 0;
}
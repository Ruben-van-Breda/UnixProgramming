

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#include "Matrix.c"
#include "StandardNetwork.c"

#define NUMTHREADS 1


void * ThreadFunc(void *argument);



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#include "Matrix.c"
#include "StandardNetwork.c"

#define NUMTHREADS 1

float** getMatrix();
float** create2DArray(int n, int m);

float** createA(int N);
float** createB(int N);

void displayMatrix(float **matrix, int N);
float** multiplyMatrix(float ** A,float ** B, int N);
float** REFF (float **matrix);
int det(float **matric,int rStart,int cStart);

void * ThreadFunc(void *argument);

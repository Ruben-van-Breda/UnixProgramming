

#include "Matrix.c"

float** getMatrix();
float** create2DArray(int n, int m);

float** createA();
float** createB();

void displayMatrix(float **matrix);
float** multiplyMatrix(float ** A,float ** B);
float** REFF (float **matrix);
int det(float **matric,int rStart,int cStart);

void * ThreadFunc(void *argument);


#include "A3.h"

int N = 2; // size of the matrices
int p = 1; // number Of Worker Threads

int main(){
    printf("\n--- Master --- \n");
    printf("Enter size of matrices n: ");
    scanf("%d",&N);

    float** A = createA(N);
    displayMatrix(A,N);

    float** B = createB(N);
    displayMatrix(B,N);

    float** C = multiplyMatrix(A,B,N);
    displayMatrix(C,N);
}
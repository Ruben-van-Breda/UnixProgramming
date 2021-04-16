
#include "A3.h"

void DebugCode();

int N = 3; // size of the matrices
int p = 1; // number Of Worker Threads

int main()
{
    /* printf("\n--- Master --- \n");
    printf("Enter size of matrices n: ");
    scanf("%d",&N);

    float** A = createA(N);
    displayMatrix(A,N);

    float** B = createB(N);
    displayMatrix(B,N);

    float** C = multiplyMatrix(A,B,N);
    displayMatrix(C,N);

    int socketID = ConnectToAsServerSocket();
    printf("\n%d",socketID);

    SeverActive(socketID); */
    DebugCode();
}

void DebugCode()
{
    SomeMatrix A = createA(N);
    displayMatrix(A);

    SomeMatrix slice = GetSlice(0, A);
    displayMatrix(slice);

    // SomeMatrix p1 = MultiplyByRows(slice,A,0);
    // displayMatrix(p1);
}
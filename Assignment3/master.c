
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
    printf("Address \n");
    for (int i = 0; i < A.size; i++)
    {

        for (int j = 0; j < A.size; j++)
        {
            printf("%p ", &A.array[i][j]);
        }
        printf("\n");
    }

    SomeMatrix slice = GetSlice(0, A);
    displayMatrix(slice);
    SomeMatrix slice2 = GetSlice(1, A);
    displayMatrix(slice2);
    SomeMatrix slice3 = GetSlice(2, A);
    displayMatrix(slice3);
}
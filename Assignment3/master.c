
#include "A3.h"

void DebugCode();

int N = 3; // size of the matrices
int p = 1; // number Of Worker Threads

void MyServerRecieve(int fd, char buf[BUFSIZE]);
void breakIntoSlices(SomeMatrix A, SomeMatrix B);

int main()
{
    /* printf("\n--- Master --- \n");
    printf("Enter size of matrices n: ");
    scanf("%d",&N);

    SomeMatrix A = createA(N);
    displayMatrix(A);

    // float** B = createB(N);
    // displayMatrix(B,N);

    // float** C = multiplyMatrix(A,B,N);
    // displayMatrix(C,N);

    int socketID = ConnectToAsServerSocket();
    printf("\n%d",socketID);
    ServerRecieveFunc = MyServerRecieve;
    SeverActive(socketID); */
    DebugCode();
}

void DebugCode()
{
    SomeMatrix A = createA(N);
    displayMatrix(A);
    SomeMatrix B = createB(N);
    displayMatrix(B);

    breakIntoSlices(A,B);
   
    
}
void breakIntoSlices(SomeMatrix A, SomeMatrix B){
    /* Each slice has n/p rows*/
    SomeMatrix C;
    SomeMatrix slice;
    

    for(int k = 0; k < A.cols; k++){
   
        slice = GetSlice(k, A);
        printf("slice \t");
        displayMatrix(slice);
        SomeMatrix vector = MultiplyBySlice(slice, B,k);
        displayMatrix(vector);
    }
    
}

/* Impelement a send functon for the server host */
void MyServerRecieve(int fd, char buf[BUFSIZE]) { 
    printf("My Custom Server Send Function");
}

#include "A3.h"

void DebugCode();

int N = 3; // size of the matrices
int p = 1; // number Of Worker Threads

void MyServerRecieve(int fd, char buf[BUFSIZE]);
void MyServerSends(int fd, char buf[BUFSIZE]);
void breakIntoSlices(SomeMatrix A, SomeMatrix B);

SomeMatrix A;
SomeMatrix B;
SomeMatrix C;
int client_counter = 0;
int main()
{
    printf("\n--- Master --- \n");
    printf("Enter size of matrices n: ");
    scanf("%d", &N);

    A = createA(N);
    displayMatrix(A);

    B = createB(N);
    displayMatrix(B);

    // float** C = multiplyMatrix(A,B,N);
    // displayMatrix(C,N);

    int socketID = ConnectToAsServerSocket();
    printf("\n%d", socketID);
    /* Set the StandardNetwork.ServerRecieveFunc pointer
    to point to the local MyServerRecieve */
    ServerRecieveFunc = MyServerRecieve;
    ServerSendFunc = MyServerSends;
    SeverActive(socketID); //*/
    // DebugCode();
}

void DebugCode()
{
    SomeMatrix A = createA(N);
    // displayMatrix(A);
    char *vectorStr = SlicetoString(A, 0);
    int i = 0;
    while (*(vectorStr + i) != '\0')
    {
        printf("String %c \t", *(vectorStr + i));
        i++;
    }
    char msg[10];
    // msg[0] = *(vectorStr+0);

    for (int i = 0; i < BUFSIZE; i++)
    {
        if (*(vectorStr + i) != '\0')
        {
            msg[i] = *(vectorStr + i);
        }

        printf("msg[%d] = %c\n", i, *(vectorStr + i));
        
    }

// SomeMatrix CSM = StringToMatrix(vectorStr);
// printf("\nConverted String: %d\n",CSM.cols);
// displayMatrix(CSM);
// printf("\ntoString: %s\n", toString(A));
// SomeMatrix B = createB(N);
// displayMatrix(B);

// breakIntoSlices(A, B);
}

/**
 *
 * @param A some matrix
 * @param B another matrix
 * 
 * 'Chop' the matrix  A int slices
 * GetSlice(0) [   1,0,0       [1,0,0]    \
 *                 0,1,0    -> [1,0,0]  = [1,0,0] = Slice
 *                 0,0,1   ]   [0,0,1]    /
 *                 Slice * Matrix B. then
 * MultiplyBySlice
 * [1,0,0] *   [   2,0,0       [1,0,0] * [2, = 2 
 *                 0,3,0                  0,
 *                 1,0,4 ]                1]
 *                         
 * 
 * 
 * 

*/
void breakIntoSlices(SomeMatrix A, SomeMatrix B)
{
    /* Each slice has n/p rows*/
    SomeMatrix C;
    SomeMatrix slice;

    for (int k = 0; k < A.cols; k++)
    {

        slice = GetSlice(k, A);
        printf("slice \t");
        displayMatrix(slice);
        SomeMatrix vector = MultiplyBySlice(slice, B, k);
        displayMatrix(vector);
    }
}

/* Impelement a send functon for the server host */
void MyServerRecieve(int fd, char buf[BUFSIZE])
{
    printf("My Custom Server Recieved Function:\n");

    size_t totRead;
    char *bufr = buf;
    for (totRead = 0; totRead < BUFSIZE;)
    {
        ssize_t numRead = read(fd, bufr, BUFSIZE - totRead);
        if (numRead == 0)
            break;
        if (numRead == -1)
        {
            if (errno == EINTR)
                continue;
            else
            {
                fprintf(stderr, "Read error.\n");
            }
        }
        totRead += numRead;
        bufr += numRead;
    }
    printf("Server Received %s\n", buf);
}

void MyServerSends(int client_file_descriptor, char buf[BUFSIZE])
{
    /* Server Writes / ServerSend */
    if (client_counter >= A.size)
    {
        printf("COMPLETED MATRIX.\n");
        return;
    }
    SomeMatrix slice = GetSlice(client_counter, A);
    printf("Server is partitioning ...");
    bzero(buf, BUFSIZE);
    char *vectorStr = SlicetoString(slice, client_counter);
    printf("\nSlice is : %c\n", *(vectorStr));
    int readCounter = 0;

    // Populate buffer
     for (int i = 0; i < BUFSIZE; i++)
    {
        if (*(vectorStr + i) != '\0')
        {
            buf[i] = *(vectorStr + i);
        }

        printf("msg[%d] = %c\n", i, *(vectorStr + i));
        
    }
   
    buf[BUFSIZE - 1] = '\0'; // add a end of line character

    displayMatrix(slice);
    // char _buf[BUFSIZE];

    /* Network sending stuff */
    // char _buf[MAX_ROW] = SlicetoString(slice,client_counter);;
    char _buf2[BUFSIZE] = "0 1 0";
    size_t totWritten;

    const char *bufw = buf; //client_counter<1?_buf:_buf2;

    for (totWritten = 0; totWritten < BUFSIZE;)
    {
        ssize_t numWritten = write(client_file_descriptor, bufw, BUFSIZE - totWritten);
        if (numWritten <= 0)
        {
            if (numWritten == -1 && errno == EINTR)
                continue;
            else
            {
                fprintf(stderr, "Write error.\n");
                exit(EXIT_FAILURE);
            }
        }
        totWritten += numWritten;
        bufw += numWritten;
    }
    client_counter++;
}

#include "A3.h"

void DebugCode();

int N = 3; // size of the matrices
int p = 1; // number Of Worker Threads

void MyServerRecieve(int fd, char buf[BUFSIZE]);
void MyServerSends(int fd, char buf[BUFSIZE]);
void breakIntoSlices(SomeMatrix a, SomeMatrix b);

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

    C.array = create2DArray(3,3);
    C.size = 3;
    C.rows = C.cols = 3;
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
    // char *vectorStr = SlicetoString(A, 0);
    // int i = 0;
    // while (*(vectorStr + i) != '\0')
    // {
    //     printf("String %c \t", *(vectorStr + i));
    //     i++;
    // }
    // char msg[10];
    // // msg[0] = *(vectorStr+0);

    // for (int i = 0; i < BUFSIZE; i++)
    // {
    //     if (*(vectorStr + i) != '\0')
    //     {
    //         msg[i] = *(vectorStr + i);
    //     }

    //     printf("msg[%d] = %c\n", i, *(vectorStr + i));
        
    // }

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
        displayMatrix(C);
        return;
    }
    SomeMatrix slice = GetSlice(client_counter, A);
    printf("Server is partitioning ...");
    bzero(buf, BUFSIZE);
    
    char vectorStr[MAX_ROW][MAX_CHAR_LEN];
    // Get the slice
    SlicetoString(slice, client_counter,vectorStr);
    
    // and spaces 
    char* finalStr = malloc(sizeof(char) *  MAX_ROW * MAX_COL * MAX_CHAR_LEN);
    for(int n = 0; n < slice.cols; n++){
        
        strcat(finalStr,vectorStr[n]);
        strcat(finalStr," ");

    }
    strcat(finalStr,"#");

    // add B
   
    char bStr[MAX_ROW][MAX_CHAR_LEN];
    SlicetoString(B,client_counter,bStr);
    printf("B String : %s\n",bStr);
   for(int n = 0; n < BUFSIZE; n++){
        strcat(finalStr,bStr[n]);
        strcat(finalStr," ");
    }
    strcat(finalStr,"#");
    // printf("\nfinalString is -> %s",finalStr);
    // for(int r = 0; r  < B.rows; r++){
    //     for(int c = 0; c < B.cols; c++){
    //         strcat(finalStr, B.array[r][c]);
    //         strcat(finalStr," ");
    //     }
    // }



    buf[0] = client_counter;
    // Populate buffer
     for (int i = 1; i < BUFSIZE; i++)
    {
        if (finalStr[i-1] != '\0')
        {
            buf[i] = finalStr[i-1];
        }
        // buf[i] = '\0';

        
    }
   
    buf[BUFSIZE - 1] = '\0'; // add a end of line character

    displayMatrix(slice);

    /* Network sending stuff */
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
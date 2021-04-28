
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

     /* Set the StandardNetwork.ServerRecieveFunc pointer
    to point to the local MyServerRecieve */
    ServerRecieveFunc = MyServerRecieve;
    ServerSendFunc = MyServerSends;

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

        slice = GetRow(k, A);
        printf("slice \t");
        displayMatrix(slice);
        SomeMatrix vector = MultiplyBySlice(slice, B, k);
        displayMatrix(vector);
    }
}

/* Impelement a send functon for the server host */
void MyServerRecieve(int fd, char buf[BUFSIZE])
{   bzero(buf, BUFSIZE);
    printf("My Custom Server Recieved Function:\n");

    size_t totRead;
    char *bufr = buf;

    int client_id = buf[0];
    
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
    printf("\nServer Received data from client %d:  %s\n",client_id, buf);
    printf("\nMyServerRecieve: C[%d] <= %s",client_id,buf);
    
    /*      Modify Matrix C    */
    C.array[client_id][0] = 1;
}

void MyServerSends(int client_file_descriptor, char buf[BUFSIZE])
{
    /* Server Writes / ServerSend */
    
    if (client_counter >= A.size) // matrix complete
    {
        printf("COMPLETED MATRIX.\n");
        displayMatrix(C);
        exit(EXIT_SUCCESS);
    }
    printf("\nServer is partitioning ...\n");
    /*  Get the slice matrix of matrix A */
    SomeMatrix slice = GetRow(client_counter, A);
    bzero(buf, BUFSIZE);
        // Get the slice as a string
    char vectorStr[MAX_ROW][MAX_CHAR_LEN];
    SlicetoString(slice, client_counter,vectorStr);
    
        // and spaces inorder to identify the start and end of a number
    /* Create and append numbers to the finalStr char * */
    char* finalStr = malloc(sizeof(char) *  MAX_ROW * MAX_COL * MAX_CHAR_LEN);
    int bufIndexCounter = 0;
    int n = 0;
    for(n = 0; n < slice.cols; n++){
        
        strcat(finalStr,vectorStr[n]); // append the vectorStr
        strcat(finalStr," ");

    }
    strcat(finalStr,"# "); // append end tokken
    bufIndexCounter += n;

    /* Append Matrix B */
    char bStr[MAX_ROW][MAX_CHAR_LEN];
    MatrixToString(B,bStr);
    printf("B String : \n");
    int i; // B size counater
    for(i = 0; i < MAX_ROW; i ++){
        if(*bStr[i] == '\0') break;
        printf("%s\n",bStr[i]);
    }
    /*  Populate finalStr with matrix B*/
    for(int j = 0; j <= i; j++){
        strcat(finalStr,bStr[j]);
        strcat(finalStr,"& ");
    }
    strcat(finalStr,"# ");
    // printf("\nfinalString is -> %s",finalStr);
    // for(int r = 0; r  < B.rows; r++){
    //     for(int c = 0; c < B.cols; c++){
    //         strcat(finalStr, B.array[r][c]);
    //         strcat(finalStr," ");
    //     }
    // }


    sprintf(&buf[0], "%d", client_counter);  // add client counter prefix
    // buf[0] = client_counter;
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
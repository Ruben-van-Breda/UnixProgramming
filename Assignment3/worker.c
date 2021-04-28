
#include "A3.h"

char* mybuf;;

int main(int argc, char *argv[])
{   
   
    int socket_fd = ConnectToSocketAsClient();
    // char *msg = "Computing Partition";
    // ClientSend(socket_fd,msg);

    mybuf = ClientRecieve(socket_fd);
    int client_counter = mybuf[0] - '0';

    printf("\n%d Client Recieved: %s\n",client_counter,mybuf);

    char* B_matrix_str;
    /* Break up data recieved. # end of matrix  */
    for(int i = 1; i < BUFSIZE; i++){
        if(mybuf[i] == '#'){
            mybuf[i] = '\0';
            B_matrix_str = &mybuf[i+1];
            break;
            printf("\n B \n");
        }
        printf("mybuf[%d] -> %c \n",i,mybuf[i]);
    }

    printf("\nparsing matrix now ...\n");
    mybuf = &mybuf[1]; // trim off the client counter value

  
    SomeMatrix vector = StringToMatrix(mybuf);
    printf("\n Vector Matrix \n");
    displayMatrix(vector);

    SomeMatrix bMatrix = FromStringToMatrix(B_matrix_str);
    printf("\n B Matrix \n");
    displayMatrix(bMatrix);

    printf("\nPerforming dot product...\n");
  

    SomeMatrix product = MultiplyBySlice(vector,bMatrix,client_counter);
    product.rows = 1;
    product.cols = vector.cols;
    displayMatrix(product);
   
    char productStr [MAX_ROW][MAX_CHAR_LEN];
    bzero(productStr,BUFSIZE);

    MatrixToString(product,productStr);
    strcat(productStr, "#");
    /* Send product back to the master */
    char* buffer_out[BUFSIZE];





    // *out_buf[0] = 'r';
    ClientSend(socket_fd, *productStr,client_counter);

    if (close(socket_fd) == -1) /* Close connection */
    {
        fprintf(stderr, "close error.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}



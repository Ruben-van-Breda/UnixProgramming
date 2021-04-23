
#include "A3.h"

char* mybuf;;

int main(int argc, char *argv[])
{   
   
    int socket_fd = ConnectToSocketAsClient();
    char *msg = "Computing A";
    ClientSend(socket_fd,msg);

    mybuf = ClientRecieve(socket_fd);
    int client_counter = (int)mybuf[0];
    printf("\nClient Recieved: %d %s\n",client_counter,mybuf);

    for(int i = 0; i < BUFSIZE; i++){
        if(mybuf[i+1] == '#'){
            mybuf[i+1] = '\0';
            break;
            printf("\n B \n");
        }
        printf("mybuf[%d] -> %c \n",i,mybuf[i]);
    }
    // displayMatrix(B);
    printf("\nparsing matrix now ...\n");
    mybuf = &mybuf[1];
    // break char* up for A slice and B matrix
    SomeMatrix vector = StringToMatrix(mybuf);
    displayMatrix(vector);

    printf("\nPerforming dot product...\n");
  

    SomeMatrix product = MultiplyBySlice(vector,B,0);
    // product.rows = 1;
    // product.cols = vector.cols;
    // // printf("product [0][0] -> %.f\n",product.array[0][0]);
    displayMatrix(product);

    if (close(socket_fd) == -1) /* Close connection */
    {
        fprintf(stderr, "close error.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}



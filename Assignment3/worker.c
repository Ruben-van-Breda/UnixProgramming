
#include "A3.h"

char* mybuf;;

int main(int argc, char *argv[])
{   
   
    int socket_fd = ConnectToSocketAsClient();
    char *msg = "Computing A";
    ClientSend(socket_fd,msg);

    mybuf = ClientRecieve(socket_fd);
   
    printf("\nClient Recieved: %s",mybuf);

    printf("parsing matrix now ...");
    SomeMatrix vector = StringToMatrix(mybuf);
    displayMatrix(vector);

    if (close(socket_fd) == -1) /* Close connection */
    {
        fprintf(stderr, "close error.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}



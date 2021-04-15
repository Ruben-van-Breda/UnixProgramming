
#include "StandardNetwork.c"

char mybuf[BUFSIZE];

int main(int argc, char *argv[])
{   
   
    int socket_fd = ConnectToSocketAsClient();
    char *msg = "Computing A";
    ClientSend(socket_fd,msg);

    *mybuf = ClientRecieve(socket_fd);
    printf("Client Recieved %s",buf);

    if (close(socket_fd) == -1) /* Close connection */
    {
        fprintf(stderr, "close error.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

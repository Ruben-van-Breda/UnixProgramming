
#include "StandardNetwork.c"

int main(int argc, char *argv[])
{
    int socket_fd = ConnectToSocketAsClient();
    ClientSend(socket_fd);
    ClientRecieve(socket_fd);

    if (close(socket_fd) == -1) /* Close connection */
    {
        fprintf(stderr, "close error.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

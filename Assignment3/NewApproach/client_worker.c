
#define _BSD_SOURCE /* For NI_MAXHOST and NI_MAXSERV */
#include <netdb.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

#define PORTNUM "49999"    /* Port number for server */
#define BACKLOG 10
#define BUFSIZE 32

int main(int argc, char *argv[]) 
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL; 
    hints.ai_addr = NULL;
    hints.ai_next = NULL; 
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;

    if (getaddrinfo(argv[1], PORTNUM, &hints, &result) != 0)
       exit(-1);

    int cfd;
    for (rp = result; rp != NULL; rp = rp->ai_next) {
         cfd = socket(rp->ai_family, rp->ai_socktype, 
                      rp->ai_protocol);

         if (cfd == -1)
            continue;   /* On error, try next address */

         if (connect(cfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break; /* Success */

         /* close() failed, close this socket, try next address */
         close(cfd);
    }

    if (rp == NULL)
       exit(-1);

    freeaddrinfo(result);

    {
        char buf[BUFSIZE];
        int c;
        srand(time(NULL));
         /*  Populate buffer   */
        for (c = 0; c < BUFSIZE-1; c++)
        {
           buf[c] = 'A' + (random() % 26);
        }
        buf[BUFSIZE-1] = '\0'; // add EOF character

        printf("Sending %s to localhost:%s\n",buf, PORTNUM);
        /*    Write to client fd   */
        size_t totWritten;
        const char* bufw = buf;
        for (totWritten = 0; totWritten < BUFSIZE; ) {
            ssize_t numWritten = write(cfd, bufw, BUFSIZE - totWritten);
            if (numWritten <= 0) {
               if (numWritten == -1 && errno == EINTR)
                  continue;
               else {
                  fprintf(stderr, "Write error.\n");
                  exit(EXIT_FAILURE);
               }
            }
            totWritten += numWritten;
            bufw += numWritten;
        }
        /*      Read to client     */
        size_t totRead;
        char* bufr = buf;
        for (totRead = 0; totRead < BUFSIZE; ) {
            ssize_t numRead = read(cfd, bufr, BUFSIZE - totRead);
            if (numRead == 0)
               return totRead;
            if (numRead == -1) {
               if (errno == EINTR)
                  continue;
               else {
                  fprintf(stderr, "Read error.\n");
               }
            }
            totRead += numRead;
            bufr += numRead;
        }
        printf("Received %s\n", buf);
    }

    if (close(cfd) == -1) /* Close connection */
    {
        fprintf(stderr, "close error.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

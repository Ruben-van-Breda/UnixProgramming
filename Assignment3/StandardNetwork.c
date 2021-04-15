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


int ConnectToSocket(){
    struct addrinfo hints;
    struct addrinfo *result, *rp;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL; 
    hints.ai_addr = NULL;
    hints.ai_next = NULL; 
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;
      // Get an available address
    if (getaddrinfo(NULL, PORTNUM, &hints, &result) != 0)
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
    {
       fprintf(stderr, "No socket to bind...\n");
       exit(-1);
    }
   // free the list generated in the getaddrinfo call
    freeaddrinfo(result); 
    return 1;
}
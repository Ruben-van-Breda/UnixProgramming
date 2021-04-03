
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
#include <getopt.h>

#define PORTNUM "49999"    /* Port number for server */
void host2IP(char *hostname);
void ip2Host(char *hostname);
int main(int argc, char **argv){
    int option;
    int hflag; // header flag
    int tflag; // tail flag
    int kflag;
    int eflag;
   
    printf("Argument passed %s\n",argv[1]);

    struct addrinfo hints;
    struct addrinfo *result, *rp;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL; 
    hints.ai_addr = NULL;
    hints.ai_next = NULL; 
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICHOST;

    // host2IP(argv[1]);
    ip2Host(argv[1]);
}

void host2IP(char *hostname){
    struct addrinfo hints;
    struct addrinfo *result, *rp;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, NULL, &hints, &result) != 0) //populate result
       exit(EXIT_FAILURE);

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        char host[NI_MAXHOST];
        if (getnameinfo((struct sockaddr *)rp->ai_addr, rp->ai_addrlen,host, NI_MAXHOST, NULL, NI_MAXSERV, NI_NUMERICHOST) == 0)
           fprintf(stdout, "Hostname is %s, IP address is %s\n", hostname, host);
        else
           fprintf(stderr, "getnameinfo error.\n");
    }

    freeaddrinfo(result);

    exit(EXIT_SUCCESS);
}

void ip2Host(char * arg){
    struct addrinfo hints;
    struct addrinfo *result, *rp;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICHOST;

    if (getaddrinfo(arg, NULL, &hints, &result) != 0)
       exit(EXIT_FAILURE);

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        char host[NI_MAXHOST];
        if (getnameinfo((struct sockaddr *)rp->ai_addr, rp->ai_addrlen,
                 host, NI_MAXHOST, NULL, NI_MAXSERV, NI_NAMEREQD) == 0)
           fprintf(stdout, "Hostname is %s, IP address is %s\n", arg, host);
        else
           fprintf(stderr, "getnameinfo error.\n");
    }

    freeaddrinfo(result);

    exit(EXIT_SUCCESS);
}
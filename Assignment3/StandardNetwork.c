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

#define PORTNUM "49999" /* Port number for server */
#define BACKLOG 10
#define BUFSIZE 32
char buf[BUFSIZE];
void SetUp()
{
}

// Pointer functions 
void (*ServerRecieveFunc) (int file_descriptor, char buf[BUFSIZE]);
void (*ServerSendFunc) (int file_descriptor, char buf[BUFSIZE]);

void ServerReceive(int client_fd, char buf[BUFSIZE]);

/**
 * return socket id 
 */
int ConnectToAsServerSocket()
{
   struct addrinfo hints;
   struct addrinfo *result, *rp;

   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_canonname = NULL;
   hints.ai_addr = NULL;
   hints.ai_next = NULL;
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;

   if (getaddrinfo(NULL, PORTNUM, &hints, &result) != 0)
      exit(-1);

   int mysocket, optval = 1;
   for (rp = result; rp != NULL; rp = rp->ai_next)
   {
      mysocket = socket(rp->ai_family, rp->ai_socktype,
                        rp->ai_protocol);

      if (mysocket == -1)
         continue; /* On error, try next address */

      if (setsockopt(mysocket, SOL_SOCKET, SO_REUSEADDR,
                     &optval, sizeof(optval)) == -1)
         exit(-1);

      if (bind(mysocket, rp->ai_addr, rp->ai_addrlen) == 0)
         break; /* Success */

      /* bind() failed, close this socket, try next address */
      close(mysocket);
   }

   if (rp == NULL)
      exit(-1);

   {
      char host[NI_MAXHOST];
      char service[NI_MAXSERV];
      if (getnameinfo((struct sockaddr *)rp->ai_addr, rp->ai_addrlen,
                      host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
         fprintf(stdout, "Listening on (%s, %s)\n", host, service);
      else
         exit(-1);
   }

   freeaddrinfo(result);

   if (listen(mysocket, BACKLOG) == -1)
      exit(-1);

   return mysocket;
}

int ConnectToSocketAsClient()
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
   // Get an available address
   // argv[1] = null
   if (getaddrinfo(NULL, PORTNUM, &hints, &result) != 0)
      exit(-1);

   int client_file_descriptor;
   for (rp = result; rp != NULL; rp = rp->ai_next)
   {
      client_file_descriptor = socket(rp->ai_family, rp->ai_socktype,
                                      rp->ai_protocol);

      if (client_file_descriptor == -1)
         continue; /* On error, try next address */

      if (connect(client_file_descriptor, rp->ai_addr, rp->ai_addrlen) != -1)
         break; /* Success */

      /* close() failed, close this socket, try next address */
      close(client_file_descriptor);
   }

   if (rp == NULL)
   {
      fprintf(stderr, "No socket to bind...\n");
      exit(-1);
   }
   // free the list generated in the getaddrinfo call
   freeaddrinfo(result);
   return client_file_descriptor;
}

int SeverActive(int mysocket)
{
   for (;;) /* Handle clients iteratively */
   {
      struct sockaddr_storage claddr;
      socklen_t addrlen = sizeof(struct sockaddr_storage);
      int client_file_descriptor = accept(mysocket, (struct sockaddr *)&claddr, &addrlen);
      if (client_file_descriptor == -1)
      {
         continue; /* Print an error message */
      }

      {
         char host[NI_MAXHOST];
         char service[NI_MAXSERV];
         if (getnameinfo((struct sockaddr *)&claddr, addrlen,
                         host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
            fprintf(stdout, "Connection from (%s, %s)\n", host, service);
         else
            fprintf(stderr, "Connection from (?UNKNOWN?)");
      }

      char buf[BUFSIZE];
      ServerRecieveFunc = ServerRecieveFunc == NULL? ServerReceive: ServerRecieveFunc;
      ServerRecieveFunc(client_file_descriptor, buf);

      size_t totWritten;
      const char *bufw = buf;
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

      if (close(client_file_descriptor) == -1) /* Close connection */
      {
         fprintf(stderr, "close error.\n");
         exit(EXIT_FAILURE);
      }
   }

   exit(EXIT_SUCCESS);
}

void ServerReceive(int file_descriptor, char buf[BUFSIZE])
{
   size_t totRead;
   char *bufr = buf;
   for (totRead = 0; totRead < BUFSIZE;)
   {
      ssize_t numRead = read(file_descriptor, bufr, BUFSIZE - totRead);
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
   printf("Received %s\n", buf);
}

void ClientSend(int socket_fd, char msg[])
{

   int c; // counter
   srand(time(NULL));
   for (c = 0; c < BUFSIZE - 1; c++) // populate buffer with desired data
   {
      //   buf[c] = 'A' + (random() % 26);
      if (c < strlen(msg))
         buf[c] = msg[c];
   }
   buf[BUFSIZE - 1] = '\0'; // add a end of line character

   printf("Sending %s to localhost:%s\n", buf, PORTNUM);

   size_t totWritten;
   const char *bufw = buf;
   for (totWritten = 0; totWritten < BUFSIZE;)
   {
      ssize_t numWritten = write(socket_fd, bufw, BUFSIZE - totWritten);
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
}

char* ClientRecieve(int socket_fd)
{
   size_t totRead;
   char *bufr = buf;
   for (totRead = 0; totRead < BUFSIZE;)
   {
      ssize_t numRead = read(socket_fd, bufr, BUFSIZE - totRead);
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
   // printf("Received %s\n", buf);
   return buf;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
extern char **environ;

int main(int argc, char **argv)
{
    char prompt[10];
    printf("#");

    int size = 100;
    char *line[150];
    while (getline(&line, &size, stdin) != -1)
    {
        printf("#");
        // printf("%s", line);
        if (strcmp(*line, "ls") == 0)
        {
            printf("List Directory...\n");
            int f = fork();
            if (f == 0)
            {
                execve("/bin/ls", argv, environ);
                return 0;
            }
            else
            {
                printf("waiting for child  process...\n");
                wait(&f);
                printf("child  process complete.\n");
            }
        }else{
            printf("Command not found. %s",*line);
        }
       
    }

   
    return 0;
}
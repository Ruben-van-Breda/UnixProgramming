
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
void  com_ls (char **argv, char ** environ){
    printf("Child process.\n");
    execve("/bin/ls", argv, environ);
    exit(0);
}
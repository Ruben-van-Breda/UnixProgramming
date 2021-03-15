
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char** environ; // list in unistd an array of strings

int main(int argc, char **argv){
    execve("/bin/pwd",argv,environ); //executes this command in the shell
    printf("Hello ?\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
    char* this_argv[4];
    char command[] = "echo";
    char arg1[] = "Hello";
    char arg2[] = "Aliens";

    this_argv[0] = command;
    this_argv[1] = arg1;
    this_argv[2] = arg2;
    this_argv[3] = NULL;
    
    execvp(command,this_argv);
    printf("Unknown command\n");
    exit(1);
}


#include "my_shell.h"

void execute_command (char **argv, char ** environ){
    printf("execute_command");
    char* command = "/bin/";
    // strcat(command,argv[0]);
    printf("Child process. is running command %s\n","command");
    execve("/bin/pwd", argv, environ);
    exit(0);
}
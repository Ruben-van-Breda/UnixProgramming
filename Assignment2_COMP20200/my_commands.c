#include "my_shell.h"

int execute_command (char **argv, char ** environ){
    // printf("execute_command");
    char command[100] = "/bin/";
    strcat(command,argv[0]);
    // argv[1] = "-a";
    // if(argv[1] != NULL){
    //     printf("arg(1) %s",argv[1]);
    //      strcat(command,argv[1]);
    // }
    printf("Child process. is running command %s\n",command);
    // execvp(command, argv);
    // execve("/bin/ls -a", argv, environ);
    // exit(0);
    sleep(5);
    return 1;
}

void command_input(char** str){
    int argCounter = 0;
    printf("Str: %s\n",str);
    char* StrPtr =  (*str);
    printf("Copy %s",StrPtr);
    // printf(&str == &StrPt);
    printf("Address of str (%d) Address of StrPtr(%d)\n",&str,&StrPtr);
    while(*StrPtr != '\0'){
        if(*StrPtr == ' '){
            argCounter++;
        }
        printf("char : %c ",*StrPtr);
        StrPtr = (StrPtr + 1);
    }

    // char** args = malloc(argCounter * sizeof(char));
    for(int i = 0; i < argCounter;i++){
      
        printf("out %s\n",(str[i]));
    }
    printf("argC = %d, *str %s",argCounter,*str);
}


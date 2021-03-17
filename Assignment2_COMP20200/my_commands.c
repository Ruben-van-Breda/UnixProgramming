#include "my_shell.h"

int execute_command (char **argv, char ** environ){
    // printf("execute_command");
    int len = sizeof(char*)/sizeof(argv[0]);
    char command[100] = "/bin/";

    strcat(command,argv[0]);
    
    // for(int i = 1; i < len; i++){
    //     printf(" str [%d] -> %s",i,argv[i]);
    //     argv[i] = argv[i-1];
    // }
    // command[len] = '\0';
    printf("\nChild process. is running command %s\n",argv[0]);
    execvp(argv[0], argv);
    // execve(command, argv, environ);
    // execv("/bin/sh/",argv);
    // execl(command,*argv);
    // system(*argv);
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


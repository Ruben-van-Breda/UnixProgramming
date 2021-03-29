/*
 *  Ruben van Breda, 19200704, ruben.vanbreda@ucdconnect.ie 
 */
#include "my_shell.h"

/*void command_input(char** str){
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
}*/

int execute_command(char **argv, char **environ)
{

    // printf("\nChild process. is running command %s\n",argv[0]);

    if (strcmp(argv[0], "cd") == 0)
    {

        if (chdir(argv[1]) == -1)
        {
            perror("");
        }
        return 1;
    }
    else if (strcmp(argv[0], "relp") == 0)
    {

        
            perror("-v for version and -i for information.\nCurrently having trouble having the piping and basics commands at the same time for some reason.\n");
        
    }

        // // execvp(argv[0], argv);
        // if (strcmp(argv[2], ">") == 0)
        // {
        //     // printf("True");
        //     char *na[3];
        //     na[0] = argv[0];
        //     na[1] = argv[1];
        //     na[2] = NULL;
        //     // execvp(argv[0], na);
        //     redirect(argv);
        // }
        else
        {
            execvp(argv[0], argv);
        }
     
    
    return 1;
}
int isPiping(char **str)
{
    while (**str != '\0')
    {
        if (**str == '>')
        {
            return 1;
        }
        str = str + 1;
    }
    return 0;
}
void print_prompt()
{
    time_t t = time(NULL);
    struct tm *tmp;

    char *time_str;
    tmp = localtime(&t);
    time_str = ctime(&t);
    strftime(time_str, 100, "%x", tmp);
    printf("%s@ ", time_str);
}
void sig_handler(int signo)
{
    // printf("Catched signal\n");
    // if (signo == SIGINT)
    //     printf("received SIGUSR1\n");
    // else if (signo == SIGKILL)
    //     printf("received SIGKILL\n");
    // else if (signo == SIGSTOP)
    //     printf("received SIGSTOP\n");
    // print_prompt();
}

void redirect(char **argv)
{
    // perror("REDIRECTING");
    // char * new_args[3];

    // new_args[0] = argv[0];
    // new_args[1] = argv[1];
    // new_args[2] = NULL;

    // sleep(0.4);
    int count = 0;
    char *str = strtok(*argv, ">");
    char **out = malloc(8 * sizeof(char *));
    
    
    // while (str != NULL)
    // {
    //     out[count] = str;
    //     count++;
    //     out = realloc(out, (count + 1) * sizeof(char *));
    //     str = strtok(NULL, " ");
    // }
 
    const char *filename = argv[3];
    // if (filename)
    // {
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC  , 0640);
        //take the value in fd and output it to stdout
        dup2(fd, 1); // Check `man stdin` for more info
        // dup2(fd, STDERR_FILENO);
        // Check the return values of dup2 here
        argv[2] = NULL;
        close(fd);
    // }
    return;
}

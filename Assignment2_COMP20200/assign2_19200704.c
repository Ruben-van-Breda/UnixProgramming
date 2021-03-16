
#include "my_shell.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <getopt.h>
#include <sys/wait.h>
extern char **environ;
int pid_status;
int child_pid;
int arg_len = 0;
#define LEN(arr) ((char) (sizeof (arr) / sizeof (arr)[0]))/sizeof(char)
int main(int argc, char **argv)
{
    char prompt[10];
    printf("Welcome\n$");

    size_t size = 150;
    char *line;
    line = calloc(sizeof(char *), size);
    // line = malloc(sizeof(char *)*size);
    // for(int i = 0; i < size;i++){
    //    printf("%c ",*line);
    //     (++line);
    // }
    char command[150];
    // get_command(command);
    // printf("Command is %s\n",command);
    // run_command(command, argv, environ);

    while (getline(&line, &size, stdin) != -1)
    {
        printf("$");
        int len = strlen(line);
        *(line + len - 1) = '\0'; // remove the null character

        char **user_com = (char **)malloc(10 * sizeof(char *));
        for (int i = 0; i < 10; i++)
        {
            user_com[i] = (char *)malloc(50 * sizeof(char));
        }
        get_command(line, user_com);
        // command_input(&line);

        run_command(user_com, argv, environ);
        printf("$");
        // sleep(1);
        // if (strcmp(line, "ls") == 0)
        // {
        //     // printf("List Directory...\n");
        //     int f = fork();
        //     if (f == 0)
        //     {
        //         execve("/bin/ls", argv, environ);
        //         return 0;
        //     }
        //     else
        //     {
        //         // printf("waiting for child  process...\n");
        //         waitpid(f, &pid_status, 0);
        //         // printf("child  process complete.\n");
        //     }
        // }

        // if (strcmp(line, "pwd") == 0)
        // {
        //     // printf("List Directory...\n");
        //     int f = fork();
        //     if (f == 0)
        //     {
        //         execve("/bin/pwd", argv, environ);
        //         return 0;
        //     }
        //     else
        //     {
        //         // printf("waiting for child  process...\n");
        //         waitpid(f, &pid_status, 0);
        //         // printf("child  process complete.\n");
        //     }
        // }

        // line = realloc(line,sizeof(char *)*size);
    }

    return 0;
}

char **get_command(char *com, char **out)
{
    
    printf("line %s",com);
    //scanf("%s", com);
    out = (char **)malloc(10 * sizeof(char *));
    for (int i = 0; i < 10; i++)
    {
        out[i] = (char *)malloc(50 * sizeof(char));
    }
    // split command
    char *str = strtok(com, " ");

    printf("piece %s\n", str);
    while (str != NULL)
    {
        // printf("args(%d) is %s", count, str);
        out[arg_len] = str;
        arg_len++;
        out = realloc(out, (arg_len + 1) * sizeof(char *));
        str = strtok(NULL, " ");
    }

    // printf("args = %d", count);
    for (int i = 0; i < arg_len; i++)
    {

        printf("OUT %s\n", out[i]);
    }
    int len = strlen(*out);
    **(out + len - 1) = '\0';
    return out;
    //catch SIGNALS
}

int run_command(char **com, char **argv, char **environ)
{
    //printf("Running command %s\n", com[0]);
  
    argv[0] = com[0];
    for(int i = 1; i < arg_len; i++){
        *argv[i-1] = *com[i]; 
    }
    for(int i = 0; i < arg_len; i++){
        printf("arguments %s",argv[i]);
    }

    int len = sizeof(*com) / sizeof(com[0]);
    printf("argc = %ul\n",arg_len);

    char* command = strcat("/bin/",com[0]);

    int child_pid = fork();
  
    if (child_pid == 0)
    {   
        
        
        // if(*com[1] != '\0'){
        //     printf("ARG{1} %s",com[1]);
        // }
        execute_command(argv, environ);
        // waitpid(child_pid,&pid_status,0);
        
       
        return 1;
        // if (strcmp(com[0], "ls") == 0)
        // {
        //     // system("ls /");
        //     execve("/bin/ls", argv, environ);

        //     sleep(10);
        //     // com_ls(argv, environ);
        //     // exit(0);
        // }

        // if (strcmp(com[0], "pwd") == 0)
        // {
        //     // system("ls /");
        //     execve("/bin/pwd", argv, environ);

        //     sleep(10);
        //     // com_ls(argv, environ);
        //     // exit(0);
        // }
        // else
        // {
        //     //  execvp(command,argv);
        // }
      
    }else{
        printf("Parent\n");
    }

    // waitpid(child_pid,&pid_status,0);
    return 0;
}
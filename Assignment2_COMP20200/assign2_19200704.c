
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
int main(int argc, char **argv)
{
    char prompt[10];
    printf("Welcome\n#");

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
        printf("#");
        int len = strlen(line);
        *(line + len - 1) = '\0'; // remove the null character

        char **user_com = (char **)malloc(10 * sizeof(char *));
        for (int i = 0; i < 10; i++)
        {
            user_com[i] = (char *)malloc(50 * sizeof(char));
        }
        get_command(line, user_com);
        run_command(user_com, argv, environ);
        sleep(1);
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
    int count = 0;
    // printf("$");
    //scanf("%s", com);
    // out = (char **)malloc(10 * sizeof(char *));
    // for (int i = 0; i < 10; i++)
    // {
    //     out[i] = (char *)malloc(50 * sizeof(char));
    // }
    // split command
    char *str = strtok(com, " ");

    //printf("piece %s\n", str);
    while (str != NULL)
    {
        // printf("args(%d) is %s", count, str);
        out[count] = str;
        count++;
        out = realloc(out, (count + 1) * sizeof(char *));
        str = strtok(NULL, " ");
    }

    // printf("args = %d", count);
    for (int i = 0; i < count; i++)
    {

        // printf("OUT %s\n", out[i]);
    }
    int len = strlen(*out);
    **(out + len - 1) = '\0';
    return out;
    //catch SIGNALS
}

int run_command(char **com, char **argv, char **environ)
{
    printf("Running command %s\n", com[0]);
    int i = 0;
    // while(com[i] != 0){
    //     printf("arg[%d] -> %s",i,com[i]);
    //     i++;
    // }

    // char* command = strcat("/bin/",com[0]);

    child_pid = fork();
    printf("run_command _");
    if (child_pid == 0)
    {   
        printf("run_command");
        argv[0] = com[0];
        execute_command(argv, environ);

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
        
    }

    else
    {
        waitpid(child_pid, &pid_status, 0);
        return 0;
    }

    return 0;
}
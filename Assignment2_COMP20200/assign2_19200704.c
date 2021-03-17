
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
        printf("Got command %s",*user_com);
        run_command(user_com, argv, environ);
        sleep(1);
        printf("#");
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

    // int len = strlen(*out);
    // **(out + len - 1) = '\0';
    out[count] = NULL; // add null terminator

    // for (int i = 0; i < count; i++)
    // {

    //     printf("OUT[%d] %s\n", i, out[i]);
    // }

    return out;
    //catch SIGNALS
}

int run_command(char **com, char **argv, char **environ)
{
    
    int len = sizeof(char*)/sizeof(com[0]);
    printf("Running command len %d %s\n",len,*com);
    // argv[0] = com[0];
    // for(int i = 1; i <= len; i++){
    //     // printf("Char %c ",*com[i]);
    //     argv[i] = com[i];
    //     printf("%s ",argv[i-1]);
    // }

    // while (*com[i] != '\0')
    // {
    //     printf("arg[%d] -> %s", i, com[i]);
    //     argv[i] = com[i];
    //     i++;
    // }
  
    // char* command = strcat("/bin/",com[0]);

    child_pid = fork();

    if (child_pid == 0)
    {

        *argv = *com;
        execute_command(com, environ);
    }

    else
    {
        waitpid(child_pid, &pid_status, 0);
        return 0;
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include "my_commands.c"

extern char **environ;

void get_command(char line[150]);
int run_command(char *com, char **argv, char **environ);

int main(int argc, char **argv)
{
    char prompt[10];
    printf("#");
    int pid_status;
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

        if (strcmp(line, "ls") == 0)
        {
            // printf("List Directory...\n");
            int f = fork();
            if (f == 0)
            {
                execve("/bin/ls", argv, environ);
                return 0;
            }
            else
            {
                // printf("waiting for child  process...\n");
                waitpid(f, &pid_status, 0);
                // printf("child  process complete.\n");
            }
        }

        if (strcmp(line, "pwd") == 0)
        {
            // printf("List Directory...\n");
            int f = fork();
            if (f == 0)
            {
                execve("/bin/pwd", argv, environ);
                return 0;
            }
            else
            {
                // printf("waiting for child  process...\n");
                waitpid(f, &pid_status, 0);
                // printf("child  process complete.\n");
            }
        }

        // line = realloc(line,sizeof(char *)*size);
    }

    return 0;
}

void get_command(char com[])
{
    int count = 0;
    printf("$");
    scanf("%s", com);
    char **out = malloc(sizeof(char *));
    // split command
    char *str = strtok(com, " ");

    printf("piece %s\n", str);
    while (str != NULL)
    {
        printf("args(%d) is %s", count, str);
        out[count] = str;
        count++;
        out = realloc(out, (count + 1) * sizeof(char *));
        str = strtok(NULL, " ");
    }
    printf("args = %d", count);
    for (int i = 0; i <= count; i++)
    {
        printf("OUT %s\n", out[i]);
    }

    //catch SIGNALS
}

int run_command(char *com, char **argv, char **environ)
{
    int f = fork();
    if (f == 0)
    {
        if (strcmp(com, "ls") == 0)
        {
            // system("ls /");
            execve("/bin/ls", argv, environ);
            //execvp(com,argv);
            // com_ls(argv, environ);
            exit(0);
        }
    }
    else
    {
        return 0;
    }

    return 0;
}
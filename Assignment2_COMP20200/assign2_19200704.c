
#include "my_shell.h"

extern char **environ;
int pid_status;
int child_pid;
int main(int argc, char **argv)
{
    char prompt[10];
    printf("Welcome\n");
    print_prompt();
    size_t size = 150;
    char *line;
    line = calloc(sizeof(char *), size);
  
    signal(SIGINT,sig_handler);
    while (getline(&line, &size, stdin) != -1)
    {
        // printf("#");
        signal(SIGINT,sig_handler);
        print_prompt();
        int len = strlen(line);
        *(line + len - 1) = '\0'; // remove the null character

        char **user_com = (char **)malloc(10 * sizeof(char *));
        for (int i = 0; i < 10; i++)
        {
            user_com[i] = (char *)malloc(50 * sizeof(char));
        }
        user_com = get_command(line);
        // printf("Got command %s",*user_com);
        run_command(user_com, environ);
        sleep(1);
        // printf("#");
        // line = realloc(line,sizeof(char *)*size);
    }
    signal(SIGINT,sig_handler);
    return 0;
}


char **get_command(char *com)
{
    int count = 0;
    // split command
    char *str = strtok(com, " ");
    char **out = malloc(8 * sizeof(char *));
    //printf("piece %s\n", str);
    while (str != NULL)
    {
        // printf("args(%d) is %s", count, str);
        out[count] = str;
        count++;
        out = realloc(out, (count + 1) * sizeof(char *));
        str = strtok(NULL, " ");
    }

    out[count] = NULL; // add null terminator

    return out;
    //catch SIGNALS
}

int run_command(char **argv, char **environ)
{
    
    // int len = sizeof(char*)/sizeof(com[0]);
    // printf("Running command len %d %s\n",len,*com);
 
    child_pid = fork();

    if (child_pid == 0)
    {
        
      
        execute_command(argv, environ);
    }

    else
    {
        waitpid(child_pid, &pid_status, 0);
        return 0;
    }
    free(argv);
    return 0;
}

#include "my_shell.h"

#define LEN(arr) ((char) (sizeof (arr) / sizeof (arr)[0]))/sizeof(char)
extern char **environ;
int arg_len = 0;
int pid_status;
int child_pid;
int main(int argc, char **argv)
{
    
    passed_arguments(argc,argv);
   

    char prompt[10];
    printf("\nRubio_Shell\n");
    print_prompt();
    size_t size = 150;
    char *line;
    line = calloc(sizeof(char *), size);
  
    signal(SIGINT,sig_handler);
    while (getline(&line, &size, stdin) != -1)
    {
        
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
        
        run_command(user_com, environ);
        sleep(1);
        
    }
    signal(SIGINT,sig_handler);
    return 0;
}


char** get_command(char *com)
{
    int count = 0;
    // split command
    char *str = strtok(com, " ");
    char **out = malloc(8 * sizeof(char *));
    
    while (str != NULL)
    {
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

void passed_arguments(int argc, char**argv){
    int option;
  
    int vflag; // header flag
    int iflag; // tail flag
  
    option = getopt(argc, argv, "vi");
    if(option != -1)
    {
        switch (option)
        {
        case 'v':
            if (vflag)
            {
               printf("kop\n");
            }
            else
            {
                vflag++;
                iflag++;
            }
            printf("MY_Shell Version : %s","S");
            break;
        case 'i':
        if (iflag)
            {
               printf("kop\n");
            }
            else
            {
                vflag++;
                iflag++;
            }
            printf("Made by Ruben van Breda, 19200704. Bugs: Version : %s","Ss");
            break;
        }
    }
    return;
}
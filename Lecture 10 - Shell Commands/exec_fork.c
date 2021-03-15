#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(int argc, char **argv)
{
    pid_t child_pid;
    int child_status;

    child_pid = fork();
    if (child_pid == 0)
    { //child process
        sleep(5);
        execve("./exec", argv, environ); // call a seperate process
        printf("Unknown command\n"); // execve failed
        exit(0);
    }
    else
    {
        //Parent Process waits for child to finish
        printf("parent waiting\n");
        // wait until the child terminates, change its status
        wait(&child_pid); // waitpid (child_pid, &child_status, 0)
    }
    printf("parent exiting\n");
    return 0;
}

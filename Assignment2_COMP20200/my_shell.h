#ifndef MY_SHELL_H
#define MY_SHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <getopt.h>
#include <sys/wait.h>
extern char **environ;
char **get_command(char *str);

int execute_command (char **argv, char ** environ);
int run_command(char **argv, char **environ);
#endif
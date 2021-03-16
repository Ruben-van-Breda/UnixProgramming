#ifndef MY_SHELL_H
#define MY_SHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <getopt.h>
#include <sys/wait.h>
#include <signal.h>

char **get_command(char *str, char **out);
void command_input(char** str);
int execute_command (char **argv, char ** environ);
int run_command(char **com, char **argv, char **environ);
#endif
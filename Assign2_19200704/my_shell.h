/*
 *  Ruben van Breda, 19200704, ruben.vanbreda@ucdconnect.ie 
 */
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

#include <time.h>
#include <signal.h>
#include <fcntl.h> 

extern char **environ;
char **get_command(char *str);

int execute_command (char **argv, char ** environ);
int run_command(char **argv, char **environ);
void print_prompt();
void sig_handler(int signo);
void redirect(char ** argv);
void passed_arguments(int argc, char**argv);
void print_manual();
int isPiping(char **str);
// char RUBYSHELL[4] = "1.0";
#endif
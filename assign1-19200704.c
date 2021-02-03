/*
    Created by Ruben van Breda
*/
/*
    Practical 1: args
*/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


int main(int argc, char **argv){
    int option;
    while((option = getopt(argc, argv, "ht")) != -1){
        switch(option){
            case 'h':
                printf("%c",argv[2][0]);
                break;
            case 't':
                printf("you choose this t option\n");
                break;
            default: 
                printf("Error");
        }
    }
    //printf("%s",argv[3]);
    return 0;
}
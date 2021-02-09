/*
    Created by Ruben van Breda
*/
/*
    Practical 1: args
*/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void print_manaul();
void head_of_file(int n);
void tail_of_file(int n);

int main(int argc, char **argv)
{
    int option;
    int hflag; // header flag
    int tflag; // tail flag
    int kflag;
    int numOfLines = 10;
    while ((option = getopt(argc, argv, "h:n:t:v")) != -1)
    {
        switch (option)
        {
            case 'h':
                if(hflag){
                    print_manaul();
                }else{
                    hflag++; tflag++; kflag++;// increase to avoid errors in arguments
                }
                head_of_file(numOfLines);
                break;
            case 't':
                if(tflag){
                    print_manaul();
                }else{
                    hflag++; tflag++; kflag++;// increase to avoid errors in arguments
                }
                tail_of_file(numOfLines);
                break;

            case 'v':
                printf("Ruben van Breda,\truben.vanbreda@ucdconnect.ie,\t19200704\n");
                break;
            case 'n':
                
                numOfLines = atoi(optarg);
                
                break;
            default:
                printf("Error");
        }
    }
    //printf("%s",argv[3]);
    return 0;
}
void print_manaul(){
    printf("\nUsage: -h <file> | -t <file>\n");
    exit(1);
}

void head_of_file(int n){
    FILE *fp;
    char *file_name;
    char cur_char;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if(optarg == 0){
         printf("File could not be opened.");
    }
    // has file argument
    fp = fopen(optarg,"r");
    if(fp != NULL){
        printf("Head of file:\n");
    
        while((read = getline(&line,&len,fp)) != -1){
            printf("%s",line);
            n--;
            if(n<= 0){break;}
        }
    }
    else{
        printf("File could not be opened.");
    }
    
}

void tail_of_file(int n){
    printf("Tail of file:");
    
    FILE *fp;
    char *file_name;
    char cur_char;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int counter = 0;
    if(optarg == 0){
         printf("File could not be opened.");
    }
    // has file argument
    fp = fopen(optarg,"r");
    if(fp != NULL){
        printf("Head of file:\n");
    
        while((read = getline(&line,&len,fp)) != -1){
            printf("%s",line);
            n--;
            if(n<= 0){break;}
        }
    }
    else{
        printf("File could not be opened.");
    }
    
}




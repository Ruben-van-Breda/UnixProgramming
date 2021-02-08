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
void head_of_file();
void tail_of_file();

int main(int argc, char **argv)
{
    int option;
    int hflag; // header flag
    int tflag; // tail flag
    while ((option = getopt(argc, argv, "h:tv")) != -1)
    {
        switch (option)
        {
            case 'h':
                if(hflag){
                    print_manaul();
                }else{
                    hflag++; tflag++; // increase to avoid errors in arguments
                }
                head_of_file(2);
                break;
            case 't':
                if(tflag){
                    print_manaul();
                }else{
                    hflag++; tflag++; // increase to avoid errors in arguments
                }
                tail_of_file();
                break;

            case 'v':
                printf("Ruben van Breda,\truben.vanbreda@ucdconnect.ie,\t19200704\n");
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

    fp = fopen(optarg,"r");
    if(fp != NULL){
        printf("Head of file:\n");
        // //loop thru characters in file
        // while( (cur_char = fgetc(fp)) != EOF){
        //     printf("%c",cur_char);
        //     n--;
        //     if(n<=0){
        //         break;
        //     }
        // }

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

void tail_of_file(){
    printf("Tail of file:");
}




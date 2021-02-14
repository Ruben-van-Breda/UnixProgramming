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
int lineCount(char *str);
void odd_even(int p);

#define MAX_LINE_LENGTH 100
#define MAX_NUM_LINES 100

int numOfLines = 5;

int main(int argc, char **argv)
{
    int option;
    int hflag; // header flag
    int tflag; // tail flag
    int kflag;
    int eflag;
   
    while ((option = getopt(argc, argv, "e:o:h:n:t:v")) != -1)
    {
        switch (option)
        {
        case 'h':
            if (hflag)
            {
                print_manaul();
            }
            else
            {
                hflag++;
                tflag++;
                kflag++;
                eflag++; // increase to avoid errors in arguments
            }
            head_of_file(numOfLines);
            break;
        case 't':
            if (tflag)
            {
                print_manaul();
            }
            else
            {
                hflag++;
                tflag++;
                kflag++;
                eflag++; // increase to avoid errors in arguments
            }
            tail_of_file(numOfLines);
            break;
        case 'e':
            if (eflag)
            {
                print_manaul();
            }
            else
            {
                hflag++;
                tflag++;
                kflag++;
                eflag++; // increase to avoid errors in arguments
            }
            odd_even(2);
            break;
        case 'o':
            if (eflag)
            {
                print_manaul();
            }
            else
            {
                hflag++;
                tflag++;
                kflag++;
                eflag++; // increase to avoid errors in arguments
            }
            odd_even(1);
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
void print_manaul()
{
    printf("\nUsage: -h <file> | -t <file>\n");
    exit(1);
}

void head_of_file(int n)
{
    FILE *fp;
    char *file_name;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (optarg == 0)
    {
        printf("File could not be opened.");
    }
    // has file argument
    fp = fopen(optarg, "r");
    if (fp != NULL)
    {
        printf("Head of file:\n");

        while ((read = getline(&line, &len, fp)) != -1)
        {
            printf("%s", line);
            n--;
            if (n <= 0)
            {
                break;
            }
        }
    }
    else
    {
        printf("File could not be opened.");
    }
    fclose(fp);
}

void tail_of_file(int n)
{
    printf("Tail of file:\n");

    FILE *fp;        // pointer to file
    char *file_name; // file path
    char cur_char;
    char *line = NULL; // line array
    size_t len = 0;
    ssize_t read;
    int counter = 0;

    //char content[MAX_NUM_LINES][MAX_LINE_LENGTH];
    char strArray[150][150];
    if (optarg == 0)
    {
        printf("File could not be opened.");
        return;
    }
    // has file argument
    fp = fopen(optarg, "r");

    if (fp != NULL)
    {

        while ((read = getline(&line, &len, fp)) != -1) // poor counting the lines in the file
        {
            // fgets(line, 100, fp);
            int i = 0;
            while(line[i] != '\n'){
                strArray[counter][i] = line[i];
                i++;
            }
            
            counter++;
            // /printf("%s", line);
        }
        int n = 0;
       
        // printf("Counter %d", counter);
        for(int i = 0; i <counter;i++){
            if(i >= counter-numOfLines){
                printf("%s\n", strArray[i]);         
            }
            
        }
    }

    else
    {
        printf("File could not be opened.");
    }
    fclose(fp);
}

void odd_even(int p)
{
    FILE *fp;
    char *file_name;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (optarg == 0)
    {
        printf("File could not be opened.");
    }
    // has file argument
    fp = fopen(optarg, "r");
    int parity = 0;
    // has file argument
    fp = fopen(optarg, "r");
    if (fp != NULL)
    {
        printf("%s lines of %s:\n", (p == 1 ? "Odd" : "Even"), optarg);

        while ((read = getline(&line, &len, fp)) != -1)
        {
            if (p == 1)
            {

                if (parity % 2 == 0) // odd
                {
                    printf("%s", line);
                }
            }
            else if (p == 2)
            {
                if (parity % 2 != 0) // even
                {
                    printf("%s", line);
                }
            }
            parity++;
        }
    }
    else
    {
        perror("File could not be opened.");
        exit(-1);
    }
    fclose(fp);
}
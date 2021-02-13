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
void odd_even (int p);

#define MAX_LINE_LENGTH 100
#define MAX_NUM_LINES 100
int main(int argc, char **argv)
{
    int option;
    int hflag; // header flag
    int tflag; // tail flag
    int kflag;
    int eflag;
    int numOfLines = 5;

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
                eflag++;  // increase to avoid errors in arguments
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
    char line[MAX_LINE_LENGTH]; // line array
    size_t len = 0;
    ssize_t read;
    int counter = 0;

    char *content = "";
    if (optarg == 0)
    {
        printf("File could not be opened.");
        return;
    }
    // has file argument
    fp = fopen(optarg, "r");

    if (fp != NULL)
    {

        while (!feof(fp))
        {
            fgets(line, MAX_LINE_LENGTH, fp);
            content[counter] = &line;
            counter++;
            printf("%s", line);
        }

        for (int i = 0; i < counter; i++)
        {
            printf("%d, %c\n", i, (content + i));
        }
    }

    else
    {
        printf("File could not be opened.");
    }
    fclose(fp);
}

void odd_even (int p){
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
    int parity=0;
      // has file argument
    fp = fopen(optarg, "r");
    if (fp != NULL)
    {
        printf("%s lines of %s:\n",(p==1?"Odd":"Even"),optarg);

        while ((read = getline(&line, &len, fp)) != -1)
        {   
            if(p == 1){ 
                if(parity%2 == 0){
                    printf("%s", line);
                }
            } // odd
            if(p == 2){ 
                if(parity%2 != 0){
                    printf("%s", line);
                }
            } // even
           
            parity++;
            
           
        }
    }
    else
    {
        printf("File could not be opened.");
    }
    fclose(fp);
}
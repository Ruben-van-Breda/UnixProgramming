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

int numOfLines = 10;
void print_manaul()
{
    printf("\nDeveloped by Ruben van Breda, 19200704\t 14 Feb 2020\nDesc:\n\t"
    "This program can read in and print out the first|last n lines from a file argument. \n\tThe options -e -o prints out the even or odd lines contained in the file ");
    printf("\nUsage: \n\t-n <Integer> number of lines to read ( Defualt 10)\n\t-h <file> : header of a file\n\t-t <file> : tail of a file\n\t"
    "-v  : version\n");
    printf("note: I did not implement reading from standard input as Im not sure what\nyou will do with 1 string of text ? whould the lines then be split spaces?"
    "\nNot to sure. So works with files. \n");
    exit(1);
}
int main(int argc, char **argv)
{
    int option;
    int hflag; // header flag
    int tflag; // tail flag
    int kflag;
    int eflag;
   
    while ((option = getopt(argc, argv, "e:o:h::n::t::vi")) != -1)
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
        case ':':
            printf("Jellow My Mellow");
            break;
        case 'n':
            numOfLines = atoi(optarg);
            break;
        case 'i':
            print_manaul();
            exit(0);
            break;
        default:
            printf("Error");
        }
    }
    //printf("%s",argv[3]);
    return 0;
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
        printf("File could not be opened. %s",optarg);
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
    char strArray[MAX_NUM_LINES][MAX_LINE_LENGTH];
    // if (optarg == 0)
    // {
    //     printf("File could not be opened.");
    //     return;
    // }
    // has file argument
    fp = fopen(optarg, "r");

    if (fp != NULL)
    {

        while ((read = getline(&line, &len, fp)) != -1) // loop thru lines and add them to the strArray
        {
            // fgets(line, 100, fp);
            int i = 0;
            while(line[i] != '\n'){ // loop thru the characters in the current line
                strArray[counter][i] = line[i];
                i++;
            }
            
            counter++;//counts the number of lines in the file
         
        }
        int n = 0;
       
        
        for(int i = 0; i <counter;i++){
            if(i >= counter-numOfLines){
                printf("%s\n", strArray[i]);         
            }
            
        }
    }

    else
    {
        printf("File could not be opened. %s",optarg);

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

    int parity = 0;
    int counter;
    if (optarg == 0)
    {
        printf("File could not be opened.");
    }
    // has file argument
    fp = fopen(optarg, "r");
   
    // has file argument
    fp = fopen(optarg, "r");
    counter = 0;
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
                    counter++;
                }
            }
            else if (p == 2)
            {
                if (parity % 2 != 0) // even
                {
                    printf("%s", line);
                    counter++;
                }
                
            }
            parity++;
          
            if(numOfLines != 0 &&counter >= numOfLines){
                break;
            }
        }
    }
    else
    {
        perror("File could not be opened.");
        exit(-1);
    }
    fclose(fp);
}
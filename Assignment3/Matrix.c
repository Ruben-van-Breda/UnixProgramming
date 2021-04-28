#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ROW 20
#define MAX_COL 20
#define MAX_CHAR_LEN 32
struct MatrixObject
{
    int size;
    int cols;
    int rows;
    float **array;

} typedef SomeMatrix;

SomeMatrix getMatrix();
float **create2DArray(int n, int m);

/* Function Headers */
SomeMatrix createA(int N);
SomeMatrix createB(int N);
SomeMatrix multiplyMatrix(SomeMatrix A, SomeMatrix B);
void displayMatrix(SomeMatrix matrix);
void SlicetoString(SomeMatrix M, int index, char str[MAX_ROW][MAX_CHAR_LEN]);
SomeMatrix MultiplyBySlice(SomeMatrix slice, SomeMatrix M, int index);

SomeMatrix A;
SomeMatrix B;
SomeMatrix C;
/* Methods */

/**
 *  Get the user to enter a matrix 
 *  @return user populated matrix
 */
SomeMatrix getMatrix()
{
    SomeMatrix res;
    /* Get dimensions */
    int n;
    int m;
    printf("Enter size for matrix: ");
    scanf("%d", &n);
    res.size = n;
    res.rows = res.cols = n;

    /* Create and populate matrix */
    float **M = create2DArray(n, m);
    int value; // element
    for (int r = 0; r < res.rows; r++)
    {
        for (int c = 0; c < res.cols; c++)
        {
            printf("Enter element [%d][%d]: ", r, c);
            scanf("%d", &value); // get value
            M[r][c] = value;     // set value
        }
    }
    res.array = M;
    return res;
}

SomeMatrix createA(int N)
{
    SomeMatrix res;
    res.size = N;
    res.rows = res.cols = N;
    res.array = create2DArray(N, N);
    if (N == 3)
    {
        res.array[0][0] = 11;
        res.array[0][1] = 2;
        res.array[0][2] = 3;
        res.array[1][0] = 1;
        res.array[1][1] = 2;
        res.array[1][2] = 1;
        res.array[2][0] = 3;
        res.array[2][1] = 1;
        res.array[2][2] = 2;
    }
    if (N == 2)
    {
        res.array[0][0] = 1;
        res.array[0][1] = 2;
        res.array[1][0] = 2;
        res.array[1][1] = -1;
    }

    return res;
}
SomeMatrix createB(int N)
{
    SomeMatrix res;
    res.size = N;
    res.rows = res.cols = N;

    res.array = create2DArray(N, N);
    if (N == 3)
    {
        res.array[0][0] = 1;
        res.array[0][1] = 2;
        res.array[0][2] = 3;
        res.array[1][0] = 0;
        res.array[1][1] = 1;
        res.array[1][2] = 5;
        res.array[2][0] = 1;
        res.array[2][1] = 0;
        res.array[2][2] = 3;
    }
    if (N == 2)
    {
        res.array[0][0] = 13;
        res.array[0][1] = 1;
        res.array[1][0] = 4;
        res.array[1][1] = -2;
    }

    return res;
}

/**
 * Allocate memory for a two dimensional array of type float
 * @param m row size of matrix 
 * @param n column size of matrix
 * @return memory allocated array
 */
float **create2DArray(int m, int n)
{
    float *values = calloc(m * n, sizeof(float));
    float **rows = malloc(n * sizeof(float *));

    for (int i = 0; i < n; ++i)
    {
        rows[i] = values + i * m;
    }

    return rows;
}
/**
 * Prints out the given matrix to the console
 * @param matrix to print
 */
void displayMatrix(SomeMatrix matrix)
{
    for (int r = 0; r < matrix.rows; r++)
    {
        for (int c = 0; c < matrix.cols; c++)
        {
            printf("%.0f ", matrix.array[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Multiply matrices A and B
 * @param A first matrix
 * @param B second matrix
 * @return C the resultent matrix of A and B
 */
SomeMatrix multiplyMatrix(SomeMatrix A, SomeMatrix B)
{

    // Create resultent matrix
    SomeMatrix product;
    int N = A.size; // assumptions : A and B are square matrix
    product.array = create2DArray(N, N);
    product.size = N;
    int sum = 0;
    /* Multiply Matrices */
    for (int r = 0; r < A.size; r++)
    {
        for (int c = 0; c < B.size; c++)
        {
            // inside loop for index
            for (int i = 0; i < N; i++)
            {
                sum += A.array[r][i] * B.array[i][c];
            }
            product.array[r][c] = sum;
            sum = 0;
        }
    }

    return product;
}
SomeMatrix MultiplyBySlice(SomeMatrix slice, SomeMatrix M, int index)
{

    SomeMatrix vector;
    vector.array = create2DArray(1, M.cols);
    vector.size = M.size;
    vector.rows = 1;
    vector.cols = M.cols;
    float sum = 0;
    /* Multiply Matrices */
    for (int r = 0; r < M.rows; r++)
    {
        // inside loop for index
        for (int i = 0; i < M.cols; i++)
        {
            // printf("%.0f , %.0f\n", slice.array[0][i],M.array[i][r]);
            sum += slice.array[0][i] * M.array[i][r];
        }

        vector.array[r][0] = sum;
        // printf("vector sum = %.0f\n",vector.array[0][0]);
        sum = 0;
    }

    return vector;
}

SomeMatrix GetRow(int sliceIndex, SomeMatrix m)
{
    /*  Get the row of matrix m at index of sliceIndex*/
    SomeMatrix res;
    res.size = m.size;
    res.array = create2DArray(1, m.size);
    res.rows = 1;
    res.cols = m.size;

    for (int k = 0; k < m.size; k++)
    {
        res.array[0][k] = m.array[sliceIndex][k];
    }

    return res;
}

void MatrixToString(SomeMatrix M, char str[MAX_ROW][MAX_CHAR_LEN])
{
    /* initialise the str */
    for (int r = 0; r < MAX_ROW; r++)
    {
        for (int c = 0; c < MAX_CHAR_LEN; c++)
        {
            str[r][c] = '\0';
        }
    }

    int r = 0;
    int c = 0;
    for (r = 0; r < M.rows; r++)
    {
        char _buf[32];
        for (c = 0; c < M.cols; c++)
        {
            // make sure to break numbers up into units
            sprintf(_buf, "%.0f ", M.array[r][c]);
            strcat(str[r], _buf);
            if (c == M.cols)
                strcat(_buf, "#");
            // if(c==M.cols)
            //       str[r][c] = '#' ; // end of [,,,] col
        }
        
        // if(r == M.rows) strcat(str[r],"#");
    }
}

void SlicetoString(SomeMatrix M, int index, char str[MAX_ROW][MAX_CHAR_LEN])
{
    /* initialise the str */
    for (int r = 0; r < MAX_ROW; r++)
    {
        for (int c = 0; c < MAX_CHAR_LEN; c++)
        {
            str[r][c] = '\0';
        }
    }

    printf("\nSlicing...\n");
    /*  Get the values of the matrix and cast it to a string and place this in the str char array */
    int r = 0;
    int c = 0;
    for (r = 0; r < M.rows; r++)
    {
        for (c = 0; c < M.cols; c++)
        {
            // make sure to break numbers up into units
            sprintf(str[c], "%.02f", M.array[r][c]);
        }
        *str[r + c] = '&';
    }
}
/**
 * Create a vector from string
 */
SomeMatrix StringToMatrix(char vectorStr[MAX_CHAR_LEN])
{
    SomeMatrix ret;
    ret.rows = 1;

    float array[MAX_ROW];
    int c_count = 0;
    char **numbers[MAX_CHAR_LEN];
    float values[strlen(vectorStr)];

    // printf("\nTRANSFORMING %s\n",vectorStr);

    char *num = strtok(vectorStr, " ");
    while (num != NULL)
    {
        if (*num != '\0')
        {
            numbers[c_count] = &num;
            if (**numbers[c_count] == '#')
            {

                break;
            }
            float value = atoi(*numbers[c_count]);
            array[c_count] = value;
            printf("numberStr : %s\t", *numbers[c_count]);
            printf("value : %f\n", value);
            c_count++;
            num = strtok(NULL, " ");
        }
        else{
            break;
        }
    }
    /*  Populate our matrix array   */
    ret.array = create2DArray(1, c_count);
    ret.cols = c_count;
    for (int i = 0; i < ret.cols; i++)
    {
        ret.array[0][i] = array[i];
    }
    return ret;
}

/**
 * Create a vector from string
 */
SomeMatrix FromStringToMatrix(char vectorStr[MAX_CHAR_LEN])
{
    SomeMatrix ret;
    float array[MAX_ROW][MAX_COL];
    float values[strlen(vectorStr)];

    int c_count = 0;
    int r_count = 0;
    char **numbers[MAX_CHAR_LEN];

    // printf("\nTRANSFORMING %s\n",vectorStr);
    int num_index = 0;
    int col_index = 0;
    int row_index = 0;
    char *num = strtok(vectorStr, " ");
    while (num != NULL)
    {
        if (*num != '\0')
        {
            if(*num == '#') break;
            

            if (*num == '&')
            {
                if (c_count == 0)
                    c_count = num_index; // count the number of coloums
                r_count++;
                row_index++;
                num = strtok(NULL, " "); // get next number in vector string
                // break;
            }
           
            else
            {
                numbers[num_index] = &num;
                float value = atoi(*numbers[num_index]);

                int _cIndex = c_count != 0 ? (int)(num_index % c_count) : num_index;

                array[row_index][_cIndex] = value;
                printf("numberStr : %s\t", *numbers[num_index]);
                printf("value : %f\n", value);
                num_index++;
                num = strtok(NULL, " "); // get next number in vector string

                
               
            }
        }
    }
    row_index--; // for the extra '&'
    /*  Populate our matrix array   */
    printf("\nrow_index = %d\n", row_index);
    printf("\nc_count = %d\n", c_count);

    ret.rows = row_index;
    ret.cols = c_count;
    ret.array = create2DArray(row_index, c_count);
    for (int r = 0; r < ret.rows; r++)
    {
        for (int c = 0; c < ret.cols; c++)
        {
            ret.array[r][c] = array[r][c];
        }
    }

    return ret;
}
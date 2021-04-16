#include <stdlib.h>
#include <stdio.h>

#define MAX_ROW 10
#define MAX_COL = 10

struct MatrixObject
{
    int size;
    int cols;
    int rows;
    float **array;

} typedef SomeMatrix;

SomeMatrix getMatrix();
float **create2DArray(int n, int m);

/* Headers */

/* Easy debugging */
SomeMatrix createA(int N);
SomeMatrix createB(int N);

void displayMatrix(SomeMatrix matrix);
SomeMatrix multiplyMatrix(SomeMatrix A, SomeMatrix B);
float **REFF(float **matrix);
int det(float **matric, int rStart, int cStart);

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
        res.array[0][0] = 1;
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
        res.array[1][0] = 1;
        res.array[1][1] = 2;
        res.array[1][2] = 1;
        res.array[2][0] = 3;
        res.array[2][1] = 1;
        res.array[2][2] = 2;
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
    /** 
     * @todo The dimensions might not be calculated correctly 
     */
    // Calculate dimensions
    // int row_len = sizeof(matrix[0])/sizeof(float);
    // int col_len = sizeof(matrix[0]) /sizeof(float) - 1;

    // printf("sizeof(matrix) = %d\n",sizeof(matrix));
    // printf("sizeof(matrix[0][0]) = %d\n",sizeof(matrix[0][0]));
    // printf("sizeof(matrix) / sizeof(matrix[0][0]) = %d\n",sizeof(matrix)/sizeof(matrix[0][0]));
    // printf("row lasen %d,  col len %d",row_len,col_len);
    /* loop through and print matrix */

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

    // Calculate dimensions
    // int rowA_len = sizeof(A) / sizeof(A[0][0]);
    // int colA_len = sizeof(A[0]) /sizeof(A[0][0]);

    // int rowB_len = sizeof(B) / sizeof(B[0][0]);
    // int colB_len = sizeof(B[0]) /sizeof(B[0][0]);

    // Invalid Dimensions
    // if(colA_len != rowB_len){
    //     perror("Invalid dimentions for the matrices to multiply\n");
    //     return NULL;
    // }

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
SomeMatrix MultiplyByRows(SomeMatrix slice, SomeMatrix B, int index)
{   
    SomeMatrix product;
    product.rows = 1;
    product.cols = B.size;
    int sum = 0;
    /* Multiply Matrices */
    for (int r = 0; r < slice.rows; r++)
    {
       
            // inside loop for index
            for (int i = 0; i < B.cols; i++)
            {
                sum += slice.array[r][i] * B.array[i][index];
            }
            product.array[r][index] = sum;
            sum = 0;
        
    }
    return product;
}

SomeMatrix GetSlice(int sliceIndex, SomeMatrix m)
{
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


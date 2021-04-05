#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 10
#define MAX_COL = 10

float** getMatrix();
float** create2DArray(int n, int m);

float** createA();
float** createB();

void displayMatrix(float **matrix);
float** multiplyMatrix(float ** A,float ** B);


int main(){
    float** A = createA();
    float** B = createB();
    displayMatrix(A);
    displayMatrix(B);
    float** C = multiplyMatrix(A,B);
    displayMatrix(C);
    return 0;   
}

float** getMatrix(){
    int n; int m;
    printf("Enter number of rows for matrix A: ");
    scanf("%d", &n);

    printf("Enter number of columns of matrix A: ");
    scanf("%d", &m);

    float** M = create2DArray(n,m);
    int value; // element
    for(int r = 0; r < n; r++){
        for(int c = 0; c < m; c ++){
            printf("Enter element [%d][%d]: ", r,c);
            scanf("%d",&value);
            M[r][c] = value;

        }
    }
    return M;


}

float** createA(){
    float** M = create2DArray(2,2);
    M[0][0] = 0;
    M[0][1] = 2;
    M[1][0] = 3;
    M[1][1] = 4;
    return M;
}
float** createB(){
    float** M = create2DArray(2,2);
    M[0][0] = 1;
    M[0][1] = 2;
    M[1][0] = 3;
    M[1][1] = 4;
    return M;
}

float** create2DArray(int m, int n)
{
    float* values = calloc(m*n, sizeof(float));
    float** rows = malloc(n*sizeof(float*));

    for (int i=0; i<n; ++i)
    {
        rows[i] = values + i*m;
    }
    return rows;
}

void displayMatrix(float **matrix){

    // Calculate dimensions
    int row_len = sizeof(matrix) / sizeof(matrix[0][0]);
    int col_len = sizeof(matrix[0]) /sizeof(matrix[0][0]);

    // loop through matrix
    for(int r = 0; r < row_len; r++){
        for(int c = 0; c < col_len;c++){
            printf("%.0f ", matrix[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

float** multiplyMatrix(float ** A,float ** B){

    // Calculate dimensions
    int rowA_len = sizeof(A) / sizeof(A[0][0]);
    int colA_len = sizeof(A[0]) /sizeof(A[0][0]);

    int rowB_len = sizeof(B) / sizeof(B[0][0]);
    int colB_len = sizeof(B[0]) /sizeof(B[0][0]);
    
    // Invalid Dimensions
    if(colA_len != rowB_len){
        printf("Invalid dimentions for the matrices to multiply\n");
        return NULL;
    }
    // Create resultent matrix
    float** C = create2DArray(colA_len,rowB_len);
    
    // Multiply 
    for(int r = 0 ; r < rowB_len; r++){
        for(int c = 0; c < colA_len;c++){
            C[r][c] = A[r][c] * B[r][c];
        }
    }


    return C;
}

float** REFF (float **matrix){
    return NULL;
}
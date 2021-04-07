#include <stdlib.h>
#include <stdio.h>

#define MAX_ROW 10
#define MAX_COL = 10

float** getMatrix();
float** create2DArray(int n, int m);

float** createA();
float** createB();

void displayMatrix(float **matrix);
float** multiplyMatrix(float ** A,float ** B);
float** REFF (float **matrix);
int det(float **matric,int rStart,int cStart);



// int main(){
//     float** A = createA();
//     float** B = createB();
//     displayMatrix(A);
//     // det(A,3,3);
//     displayMatrix(B);
//     float** C = multiplyMatrix(A,B);
//     displayMatrix(C);

//     // REFF(C);
//     return 0;   
// }

float** getMatrix(){
    /* Get dimensions */
    int n; int m;
    printf("Enter number of rows for matrix: ");
    scanf("%d", &n);

    printf("Enter number of columns of matrix: ");
    scanf("%d", &m);
    /* Create and populate matrix */
    float** M = create2DArray(n,m);
    int value; // element
    for(int r = 0; r < n; r++){
        for(int c = 0; c < m; c ++){
            printf("Enter element [%d][%d]: ", r,c);
            scanf("%d",&value); // get value
            M[r][c] = value; // set value

        }
    }
    return M;


}

float** createA(){
    float** M = create2DArray(2,2);
    M[0][0] = 1;
    M[0][1] = 2;
    M[1][0] = -1;
    M[1][1] = 0; 
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
    int row_len = sizeof(matrix) / sizeof(float);
    int col_len = sizeof(matrix[0]) /sizeof(matrix[0][0]);

    // loop through matrix
    for(int r = 0; r < row_len; r++){
        for(int c = 0; c < col_len;c++){
            printf("%.0f ", matrix[r][c]);
        }
        printf("\n");
    }
    // printf("sizeof(matrix) %lu\n",sizeof(matrix));
    // printf("sizeof(matrix[0]) %lu\n",sizeof(float));


    // printf("n=%d m=%d\n",row_len,col_len);
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
   // Calculate dimensions
    int row_len = sizeof(matrix) / sizeof(matrix[0][0]);
    int col_len = sizeof(matrix[0]) /sizeof(matrix[0][0]);
    printf("REFF 1: \n");
    for(int r = 0; r < row_len; r++){
        for(int c = 0; c < col_len; c++){
                printf("[%.0f] ",matrix[r][c]);
        }
         printf("\n");
    }
    printf("\n");
    
    return NULL;
}

int  det(float **matrix,int rStart,int cStart){
     // Calculate dimensions
    int row_len = sizeof(matrix) / sizeof(matrix[0][0]);
    int col_len = sizeof(matrix[0]) /sizeof(matrix[0][0]);
    int res = 0;
    rStart = row_len-rStart;
    if (rStart > 2 || cStart > 2 ){
        res += det(matrix,rStart+1,cStart+1);
    }
    printf("DET: \n");
    

    // Right Diagonal
    for(int r = rStart; r < row_len-1; r++){
        for(int c = cStart; c < col_len-1; c++){
               
                if(r+1<=row_len && c+1<=col_len){
                    res += matrix[r][c] * matrix[r+1][c+1];
                    printf("(*) %.0f , %.0f = %d\n", matrix[r][c], matrix[r+1][c+1],res);

                }
          
               
        }
         printf("\n");
    }

    // Left Diagonal
    for(int r = 0; r < row_len-1; r++){
        for(int c = col_len-1; c >= 0; c--){
               
                if(r>=0 && c-1>=0){
                    res -= matrix[r][c] * matrix[r+1][c-1];
                    printf("(*) %.0f , %.0f = %d\n", matrix[r][c], matrix[r+1][c-1],res);

                }
          
               
        }
         printf("\n");
    }
    printf("Det -> %d ",res);
    if(res!=0)
        printf(" != 0\n");
    return res;
}




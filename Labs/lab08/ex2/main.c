#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int **generateMatrix(int);
int **generateMatrix2(int);
void grayCode(int **,int,int);
void printMatrix(int **,int);
int main(int argc,char *argv[])
{
    /*if(argc != 2){
        fprintf(stdout,"Wrong number of parameters!\n");
        return EXIT_FAILURE;
    }*/
    //int n = atoi(argv[1]);
    int n=4;
    int **matrix = generateMatrix(n);
    matrix[1][n-1] = 1;
    printMatrix(matrix,n);
    grayCode(matrix,0,n);
    printMatrix(matrix,n);
    return 0;
}
int **generateMatrix(int n){
    int **matrix = (int **) malloc(pow(2,n) * sizeof(int *));
    for(int i=0;i<pow(2,n);i++)
        matrix[i] = (int *) calloc(n,sizeof(int));
    return matrix;
}
int **generateMatrix2(int n){
    int **matrix = (int **) malloc(pow(2,n) * sizeof(int *));
    for(int i=0;i<pow(2,n);i++)
        matrix[i] = (int *) calloc(n+1,sizeof(int));
    return matrix;
}
void grayCode(int **matrix,int pos,int n){
    if(pos == n-1)
        return;
    int **matrix2 = generateMatrix2(pos+1);
    for(int i=0,i2=pow(2,pos+1)-1;i<pow(2,pos+1);i++,i2--){
        for(int j=1,j2=n-pos-1;j<pos+2;j++,j2++)
            matrix2[i][j] = matrix[i2][j2];
    }
    for(int i=0;i<pow(2,pos+1);i++) //ADDING 1s TO THE REFLECTED MATRIX
        matrix2[i][0] = 1;
    for(int i=pow(2,pos+1),i2=0;i<pow(2,pos+2);i++,i2++){
        for(int j=n-2-pos,j2=0;j<n;j++,j2++)
            matrix[i][j] = matrix2[i2][j2];
    }
    grayCode(matrix,pos+1,n);
}
void printMatrix(int **matrix,int n){
    for(int i=0;i<pow(2,n);i++){
        for(int j=0;j<n;j++)
            fprintf(stdout,"%d ",matrix[i][j]);
        fprintf(stdout,"\n");
    }
    fprintf(stdout,"\n");
}

#include <stdio.h>
#include <stdlib.h>
#define FILENAME 20+1
int **loadMatrix(int *);
void printMatrix(int **,int);
int main()
{
    int n;
    int **matrix = loadMatrix(&n);
    printMatrix(matrix,n);
    return 0;
}
int **loadMatrix(int *n){
    char filename[FILENAME];
    fprintf(stdout,"graph filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    fscanf(f,"%d\n",n);
    int **matrix = (int **) malloc(*n * sizeof(int *));
    for(int i=0;i<*n;i++){
        matrix[i] = (int *) malloc(*n * sizeof(int));
        for(int j=0;j<*n;j++){
            matrix[i][j] = 0;
        }
    }
    char startingNode,destinationNode;
    int weight;
    while(fscanf(f,"%c %c %d\n",&startingNode,&destinationNode,&weight) != EOF){
        matrix[(int)startingNode-97][(int)destinationNode-97] = weight;
    }
    return matrix;
}
void printMatrix(int **matrix,int n){
    fprintf(stdout,"\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fprintf(stdout,"%d ",matrix[i][j]);
        }
        fprintf(stdout,"\n");
    }
}

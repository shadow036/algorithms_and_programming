#include <stdio.h>
#include <stdlib.h>
#define FILENAME 20+1
int **loadMatrix(int *,int *,int);
void multiply(int **,int **,int,int,int,int);
int main()
{
    int r1,c1,r2,c2;
    int **m1 = loadMatrix(&r1,&c1,1);
    int **m2 = loadMatrix(&r2,&c2,2);
    multiply(m1,m2,r1,c1,r2,c2);
    return 0;
}
int **loadMatrix(int *rows,int *columns,int index){
    char filename[FILENAME];
    fprintf(stdout,"matrix %d filename => ",index);
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    fscanf(f,"%d %d",rows,columns);
    int **matrix = (int **) malloc(*rows * sizeof(int *));
    for(int i=0;i<*rows;i++){
        matrix[i] = (int *) malloc(*columns * sizeof(int));
        for(int j=0;j<*columns;j++){
            fscanf(f,"%d",&matrix[i][j]);
        }
    }
    return matrix;
}
void multiply(int **m1,int **m2,int r1,int c1,int r2,int c2){
    if(c1 != r2){
        fprintf(stdout,"\nThe two matrices are not compatible!\n");
        return EXIT_FAILURE;
    }
    int **m3 = (int **) malloc(r1 * sizeof(int *));
    for(int i=0;i<r1;i++){
        m3[i] = (int *) malloc(c2 * sizeof(int));
        for(int j=0;j<c2;j++){
            m3[i][j] = 0;
        }
    }
    for(int i=0;i<r1;i++){
        for(int j=0;j<c2;j++){
            for(int k=0;k<c1;k++){
                m3[i][j] += (m1[i][k] * m2[k][j]);
            }
        }
    }
    char filename[FILENAME];
    fprintf(stdout,"matrix 3 filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"w");
    fprintf(f,"%d %d\n",r1,c2);
    for(int i=0;i<r1;i++){
        for(int j=0;j<c2;j++){
            fprintf(f,"%d ",m3[i][j]);
        }
        fprintf(f,"\n");
    }
}

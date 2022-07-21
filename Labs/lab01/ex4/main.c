#include <stdio.h>
#include <stdlib.h>
#define MAX_DIM 10
int main()
{
    int r1,c1,r2,c2;
    fprintf(stdout,"r1 c1 r2 c2 => ");
    fscanf(stdin,"%d %d %d %d",&r1,&c1,&r2,&c2);
    if(r1 >= MAX_DIM || c1 >= MAX_DIM || r2 >= MAX_DIM || c2 >= MAX_DIM || c1 != r2)
        return EXIT_FAILURE;
    float **m1 = (float **) malloc(r1 * sizeof(float *));
    for(int i=0;i<r1;i++){
        m1[i] = (float *) malloc(c1 * sizeof(float));
        for(int j=0;j<c1;j++){
            fprintf(stdout,"m1[%d][%d] => ",i,j);
            fscanf(stdin,"%f",&m1[i][j]);
        }
    }
    float **m2 = (float **) malloc(r2 * sizeof(float *));
    for(int i=0;i<r2;i++){
        m2[i] = (float *) malloc(c2 * sizeof(float));
        for(int j=0;j<c2;j++){
            fprintf(stdout,"m2[%d][%d] => ",i,j);
            fscanf(stdin,"%f",&m2[i][j]);
        }
    }
    float **m3 = (float **) malloc(r1 * sizeof(float *));
    for(int i=0;i<r1;i++){
        m3[i] = (float *) calloc(c2,sizeof(float));
        for(int j=0;j<c2;j++){
            for(int k=0;k<r2;k++)
                m3[i][j] += (m1[i][k] * m2[k][j]);
        }
    }
    for(int i=0;i<r1;i++){
        for(int j=0;j<c2;j++)
            fprintf(stdout,"%f ",m3[i][j]);
        fprintf(stdout,"\n");
    }
    return 0;
}

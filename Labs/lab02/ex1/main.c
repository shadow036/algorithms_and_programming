#include <stdio.h>
#include <stdlib.h>
#define FILENAME 20+1
void readDim(int *,int *);
int checkDim(int,int,int,int);
void readMatrix(float **,int,int);
void computeProduct(float **,int,int,
                    float **,int,int,
                    float **,int *,int *);
void writeMatrix(float **,int,int,
                float **,int,int,
                float **,int,int);
int main()
{
    int r1,c1,r2,c2;
    readDim(&r1,&c1);
    readDim(&r2,&c2);
    if(checkDim(r1,c1,r2,c2) == 0){
        return EXIT_FAILURE;
    }
    float **m1 = (float **) malloc(r1 * sizeof(float *));
    for(int i=0;i<r1;i++)
        m1[i] = (float *) malloc(c1 * sizeof(float));
    float **m2 = (float **) malloc(r2 * sizeof(float *));
    for(int i=0;i<r2;i++)
        m2[i] = (float *) malloc(c2 * sizeof(float));
    return 0;
}
void readDim(int *r,int *c){
    char filename[FILENAME];
    fprintf(stdout,"matrix filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    fscanf(f,"%d %d",r,c);
    fclose(f);
}
int checkDim(int r1,int c1,int r2,int c2){
    if(r1 < 0 || c1 < 0 || r2 < 0 || c2 < 0 || c1 != r2)
        return 0;
    return 1;
}

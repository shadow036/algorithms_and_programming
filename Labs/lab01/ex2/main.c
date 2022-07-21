#include <stdio.h>
#include <stdlib.h>
#define DIM 10
int main()
{
    int n1,n2;
    printf("N1 N2 => ");
    fscanf(stdin,"%d %d",&n1,&n2);
    if(n1 > DIM || n2 > DIM)
        return EXIT_FAILURE;
    int *v1 = (int *) malloc(n1 * sizeof(int));
    for(int i=0;i<n1;i++){
        fprintf(stdout,"v1[%d] => ",i);
        fscanf(stdin,"%d",v1+i);
    }
    float *v2 = (float *) malloc(n1 * sizeof(float));
    for(int i=0;i<n1;i++){
        int startingPosition = i-n2;
        int endingPosition = i+n2;
        if(startingPosition < 0)
            startingPosition = 0;
        if(endingPosition >= n1)
            endingPosition = n1-1;
        int sum = 0;
        for(int j=startingPosition;j<=endingPosition;j++)
            sum += v1[j];
        v2[i] = (float) sum/(endingPosition-startingPosition+1);
    }
    for(int i=0;i<n1;i++)
        fprintf(stdout,"%f ",v2[i]);
    return 0;
}

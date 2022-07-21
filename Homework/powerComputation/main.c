#include <stdio.h>
#include <stdlib.h>
float power(float,int);
int main()
{
    float x;
    int n;
    fprintf(stdout,"x n => ");
    fscanf(stdin,"%f %d",&x,&n);
    fprintf(stdout,"%f",power(x,n));
    return 0;
}
float power(float x,int n){
    if(n == 0)
        return 1;
    return x * power(x,n-1);
}

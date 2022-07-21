#include <stdio.h>
#include <stdlib.h>
int fact(int);
int main()
{
    int n;
    fprintf(stdout,"n => ");
    fscanf(stdin,"%d",&n);
    fprintf(stdout,"%d",fact(n));
    return 0;
}
int fact(int n){
    if(n == 0)
        return 1;
    return n * fact(n-1);
}

#include <stdio.h>
#include <stdlib.h>
int fibonacci(int);
int main()
{
    int n;
    fprintf(stdout,"n => ");
    fscanf(stdin,"%d",&n);
    fprintf(stdout,"%d",fibonacci(n));
    return 0;
}
int fibonacci(int n){
    if(n == 0 || n == 1)
        return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

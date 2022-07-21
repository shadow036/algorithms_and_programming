#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define R 5
#define C 3
int factorial(int);
int smallestPower(int);
int main()
{
    int m1[R][C];
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            fprintf(stdout,"m1[%d][%d] => ",i,j);
            fscanf(stdin,"%d",&m1[i][j]);
        }
    }
    int m2[R][C];
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            if(m1[i][j] == 0)
                m2[i][j] = 0;
            else if(m1[i][j] < 0)
                m2[i][j] = factorial(m1[i][j]*(-1));
            else
                m2[i][j] = smallestPower(m1[i][j]);
        }
    }
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++)
            fprintf(stdout,"%d ",m2[i][j]);
        fprintf(stdout,"\n");
    }
    return 0;
}
int factorial(int value){
    for(int j=value-1;j>=1;j--)
        value*=j;
    return value;
}
int smallestPower(int value){
    int i=10;
    while(value >= i){
        i*=10;
    }
    return i;
}

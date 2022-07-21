#include <stdio.h>
#include <stdlib.h>
#define max(a,b) (a>b?a:b)
int greatestCommonDivisor(int,int);
int main()
{
    int value1,value2;
    fprintf(stdout,"value1 value2 => ");
    fscanf(stdin,"%d %d",&value1,&value2);
    fprintf(stdout,"%d",greatestCommonDivisor(value1,value2));
    return 0;
}
int greatestCommonDivisor(int value1,int value2){
    int remainder;
    if(max(value1,value2) == value1){
        remainder = value1%value2;
        if(remainder == 0)
            return value2;
        else
            greatestCommonDivisor(value2,remainder);
    }else{
        remainder = value2%value1;
        if(remainder == 0)
            return value1;
        else
            greatestCommonDivisor(value1,remainder);
    }
}

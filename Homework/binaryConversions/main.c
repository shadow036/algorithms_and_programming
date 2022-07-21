#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIMENSION 10
int main()
{
    int number;
    int base;
    char convertedNumber[DIMENSION];
    fprintf(stdout,"number => ");
    fscanf(stdin,"%d",&number);
    fprintf(stdout,"base => ");
    fscanf(stdin,"%d",&base);
    int i=0;
    while(number != 0){
        if(base > 9 && (number % base > 9))
            convertedNumber[i] = 'a' + (number % base) - 10;
        else
            convertedNumber[i] = (number % base) + '0';
        number /= base;
        i++;
    }
    for(int j=i-1;j>=0;j--)
        fprintf(stdout,"%c",convertedNumber[j]);
    return 0;
}

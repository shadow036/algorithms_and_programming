#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"
int main()
{
    srand(time(0));
    int counter = 0;
    while(counter < 10){
        int n = 5 + rand()%6;
        int *array = (int *) malloc(n * sizeof(int));
        for(int i=0;i<n;i++)
            array[i] = rand()%10;
        for(int i=0;i<n;i++)
            fprintf(stdout,"%d ",array[i]);
        mergeSortWrapper(array,n);
        fprintf(stdout,"\n");
        for(int i=0;i<n;i++)
            fprintf(stdout,"%d ",array[i]);
        fprintf(stdout,"\n----------------------\n");
        counter++;
    }
    return 0;
}

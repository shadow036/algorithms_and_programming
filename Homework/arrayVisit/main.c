#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
void arrayVisit(int *,int,int,int,int);
int main()
{
    srand(time(0));
    int size = 5 + rand()%6;
    int *array = (int *) malloc(size * sizeof(int));
    for(int i=0;i<size;i++)
        array[i] = rand()%10;
    arrayVisit(array,size,0,INT_MAX,INT_MIN);
    return 0;
}
void arrayVisit(int *array,int size,int i,int min,int max){
    fprintf(stdout,"%d ",array[i]);
    if(array[i] > max)
        max = array[i];
    if(array[i] < min)
        min = array[i];
    if(i == size-1){
        fprintf(stdout,"\nMin: %d\nMax: %d",min,max);
        return;
    }
    arrayVisit(array,size,i+1,min,max);
}

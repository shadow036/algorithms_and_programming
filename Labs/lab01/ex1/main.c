#include <stdio.h>
#include <stdlib.h>
#define DIM 15
int main()
{
    int array[DIM];
    for(int i=0;i<DIM;i++){
        fprintf(stdout,"array[%d] => ",i);
        fscanf(stdin,"%d",array+i);
    }
    int maxLength=0;
    int start=0;
    for(int i=0;i<DIM-1;i++){
        int length=1;
        int j=i+1;
        while(array[j-1] < array[j] && j < DIM){
            length++;
            j++;
        }
        if(length > maxLength){
            maxLength = length;
            start = i;
        }
    }
    for(int i=start;i<start+maxLength;i++)
        fprintf(stdout,"%d ",array[i]);
    return 0;
}

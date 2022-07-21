#include <stdio.h>
#include <stdlib.h>
#define BASE 2
void findBinary(int *,int,int,int *);
int main()
{
    int count = 0;
    int numberOfBits;
    fprintf(stdout,"Number of bits => ");
    fscanf(stdin,"%d",&numberOfBits);
    int *array = (int *) malloc(numberOfBits * sizeof(int));
    fprintf(stdout,"\n");
    findBinary(array,0,numberOfBits,&count);
    fprintf(stdout,"Total: %d\n",count);
    return 0;
}
void findBinary(int *array,int pos,int numberOfBits,int *count){
    if(pos >= numberOfBits){
        fprintf(stdout,"{");
        for(int i=0;i<numberOfBits;i++){
            fprintf(stdout,"%d",array[i]);
        }
        fprintf(stdout,"}\n");
        (*count)++;
        return;
    }
    for(int i=0;i<BASE;i++){
        array[pos] = i;
        findBinary(array,pos+1,numberOfBits,count);
    }
    return;
}

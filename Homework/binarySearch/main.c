#include <stdio.h>
#include <stdlib.h>
int *loadArray(int *);
void printArray(int *,int);
void selectionSort(int *,int);
void swap(int *,int,int);
void binarySearch(int *,int,int,int);
int main()
{
    int arraySize;
    int *array = loadArray(&arraySize);
    fprintf(stdout,"\n");
    printArray(array,arraySize);
    selectionSort(array,arraySize);
    fprintf(stdout,"\n\nSorted array: ");
    printArray(array,arraySize);
    int targetValue;
    fprintf(stdout,"\n\ntarget value => ");
    fscanf(stdin,"%d",&targetValue);
    binarySearch(array,targetValue,0,arraySize);
    return 0;
}
int *loadArray(int *arraySize){
    fprintf(stdout,"Array size => ");
    fscanf(stdin,"%d",arraySize);
    fprintf(stdout,"\n");
    int *array = (int *) malloc(*arraySize * sizeof(int));
    for(int i=0;i<*arraySize;i++){
        fprintf(stdout,"array[%d] => ",i);
        fscanf(stdin,"%d",array+i);
    }
    return array;
}
void printArray(int *array,int arraySize){
    for(int i=0;i<arraySize;i++)
        fprintf(stdout,"%d(%d) ",array[i],i);
}
void selectionSort(int *array,int arraySize){
    for(int i=0;i<arraySize-1;i++){
        int min = i;
        for(int j=i+1;j<arraySize;j++)
            if(array[j] < array[min])
                min = j;
        if(min != i)
            swap(array,i,min);
    }
}
void swap(int *array,int i,int min){
    int temp = array[i];
    array[i] = array[min];
    array[min] = temp;
}
void binarySearch(int *array,int targetValue,int left,int right){
    int median = (left+right)/2;
    if(targetValue == array[median]){
        fprintf(stdout,"\nTarget value found in position %d!\n",median);
        return;
    }
    if(left == right){
        fprintf(stdout,"\nTarget value not found!\n");
        return;
    }
    if(targetValue > array[median])
        binarySearch(array,targetValue,median+1,right);
    else
        binarySearch(array,targetValue,left,median-1);
}

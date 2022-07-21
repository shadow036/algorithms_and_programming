#include "implementation.h"
int *loadArray(int *size){
    fprintf(stdout,"size => ");
    fscanf(stdin,"%d",size);
    int *array = (int *) malloc(*size * sizeof(int));
    for(int i=0;i<*size;i++){
        fprintf(stdout,"array[%d] => ",i);
        fscanf(stdin,"%d",array+i);
    }
    return array;
}
void print(int *array,int size){
    for(int i=0;i<size;i++)
        fprintf(stdout,"%d ",array[i]);
}
int searchSubArray(int *array1,int *array2,int size1,int size2){
    for(int i=0;i<=size1-size2;i++){
        if(array1[i] == array2[0]){
            int j;
            for(j=1;j<size2;j++){
                if(array1[i+j] != array2[j])
                    break;
            }
            if(j == size2)
                return i;
        }
    }
    return -1;
}

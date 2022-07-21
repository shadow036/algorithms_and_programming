#include "rotate.h"
int *loadArray(int *n,int *shift){
    fprintf(stdout,"n => ");
    fscanf(stdin,"%d",n);
    int *array = (int *) malloc(*n * sizeof(int));
    for(int i=0;i<*n;i++){
        fprintf(stdout,"array[%d] => ",i);
        fscanf(stdin,"%d",array+i);
    }
    fprintf(stdout,"shift => ");
    fscanf(stdin,"%d",shift);
    return array;
}
int *rotateArray(int *array,int n,int shift){
    int *auxArray = (int *) calloc(n,sizeof(int));
    for(int i=0;i<n;i++)
        if(i+shift >= 0)
            auxArray[(i+shift)%n] = array[i];
        else
            auxArray[(n+i+shift)%n] = array[i];
    return auxArray;
}
void print(int *array,int n){
    fprintf(stdout,"\n");
    for(int i=0;i<n;i++)
        fprintf(stdout,"%d ",array[i]);
    fprintf(stdout,"\n");
}

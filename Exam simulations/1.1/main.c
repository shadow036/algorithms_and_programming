#include <stdio.h>
#include <stdlib.h>
int *loadArray(int *);
void selectionSort(int *,int);
int *merge(int *,int *,int *,int,int,int);
void showMergedArray(int *,int);
int main()
{
    int *a,*b,*c;
    int na,nb,nc;
    a = loadArray(&na);
    b = loadArray(&nb);
    c = loadArray(&nc);
    selectionSort(a,na);
    selectionSort(b,nb);
    selectionSort(c,nc);
    int *mergedArray = merge(a,b,c,na,nb,nc);
    showMergedArray(mergedArray,(na+nb+nc));
    return 0;
}
int *loadArray(int *numberOfElements){
    fprintf(stdout,"Number of elements => ");
    fscanf(stdin,"%d",numberOfElements);
    int *array = (int *) malloc(*numberOfElements * sizeof(int));
    for(int i=0;i<*numberOfElements;i++){
        fprintf(stdout,"Element #%d: ",i);
        fscanf(stdin,"%d",array+i);
    }
    return array;
}
void selectionSort(int *array,int length){
    for(int i=0;i<length-1;i++){
        int min = i;
        for(int j=i+1;j<length;j++){
            if(array[j] < array[min])
                min = j;
        }
        if(min != i){
            int temp = array[i];
            array[i] = array[min];
            array[min] = temp;
        }
    }
}
int *merge(int *a,int *b,int *c,int na,int nb,int nc){
    int length = na+nb+nc;
    int *mergedArray = (int *) malloc(length * sizeof(int));
    int x = 0;
    int y = 0;
    int z = 0;
    for(int i=0;i<length;i++){
        if(a[x] <= b[y] && a[x] <= c[z]){
            mergedArray[i] = a[x];
            x++;
        }else if(b[y] <= a[x] && b[y] <= c[z]){
            mergedArray[i] = b[y];
            y++;
        }else if(c[z] <= a[x] && c[z] <= b[y]){
            mergedArray[i] = c[z];
            z++;
        }
    }
    return mergedArray;
}
void showMergedArray(int *mergedArray,int length){
    for(int i=0;i<length;i++){
        fprintf(stdout,"%d ",mergedArray[i]);
    }
}

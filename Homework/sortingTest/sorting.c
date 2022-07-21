#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
void selectionSort(int *array,int n){
    for(int i=0;i<n-1;i++){
        int min = i;
        for(int j=i+1;j<n;j++){
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
void bubbleSort(int *array,int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}
void insertionSort(int *array,int n){
    for(int i=1;i<n;i++){
        int x = array[i];
        int j = i - 1;
        while(j >= 0 && x < array[j]){
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = x;
    }
}
void countingSort(int *A,int n,int k){
    /*
    1)  initialize C to all zeros (C1) [can also use calloc to skip this part]
    2)  simple occurences (C2)
    3)  multiple occurences (C3)
    4)  generate B
    5)  copy B into A
    */
    int *B = (int *) malloc(n * sizeof(int));
    int *C = (int *) malloc(k * sizeof(int));
    for(int i=0;i<k;i++)
        C[i] = 0;
    for(int i=0;i<n;i++)
        C[A[i]]++;
    for(int i=1;i<k;i++)
        C[i] += C[i-1];
    for(int i=n-1;i>=0;i--){
        B[C[A[i]]-1] = A[i];
        C[A[i]]--;
    }
    for(int i=0;i<n;i++)
        A[i] = B[i];
}
void shellSort();
void mergeSortWrapper(int *A,int n){
    int *B = (int *) malloc(n * sizeof(int));
    mergeSort(A,B,0,n-1);
}
void mergeSort(int *A,int *B,int l,int r){
    if(r <= l)
        return;
    int q = (l+r)/2;
    mergeSort(A,B,l,q);
    mergeSort(A,B,q+1,r);
    merge(A,B,l,q,r);
}
void merge(int *A,int *B,int l,int q,int r){
    int i,j,k;
    for(i=l,j=q+1,k=l;i<=q && j<=r;){
        if(A[i] <= A[j])
            B[k++] = A[i++];
        else
            B[k++] = A[j++];
    }
    while(i<=q)
        B[k++] = A[i++];
    while(j<=r)
        B[k++] = A[j++];
    for(int i=l;i<=r;i++)
        A[i] = B[i];
}

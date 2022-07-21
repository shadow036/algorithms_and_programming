#ifndef HEAPPUBLIC_H_INCLUDED
#define HEAPPUBLIC_H_INCLUDED
#include "heapPrivate.h"
void heapify(heapT *h,int i){
    int largest = i;
    if(LEFT(i) < h->heapsize)
        if(h->A[i] < h->A[LEFT(i)])
            largest = LEFT(i);
    if(RIGHT(i) < h->heapsize)
        if(h->A[largest] < h->A[RIGHT(i)])
            largest = RIGHT(i);
    if(largest != i){
        int temp = h->A[i];
        h->A[i] = h->A[largest];
        h->A[largest] = temp;
        heapify(h,largest);
    }
}
void heapBuild(heapT *h){
    for(int i=(h->heapsize/2)-1;i>=0;i--)
        heapify(h,i);
}
void heapSort(heapT *h){
    int initialSize = h->heapsize;
    for(int i=h->heapsize-1;i>=0;i--){
        int temp = h->A[0];
        h->A[0] = h->A[i];
        h->A[i] = temp;
        h->heapsize--;
        heapify(h,0);
    }
    h->heapsize = initialSize;
}
void printHeap(heapT *h){
    for(int i=0;i<h->heapsize;i++)
        fprintf(stdout,"%d ",h->A[i]);
    fprintf(stdout,"\n");
}
#endif // HEAPPUBLIC_H_INCLUDED

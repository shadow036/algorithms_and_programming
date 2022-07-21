#include <stdio.h>
#include <stdlib.h>
#include "heapPublic.h"
#include "time.h"
int main()
{
    srand(time(0));
    heapT *h = (heapT *) malloc(sizeof(heapT));
    h->heapsize = 10;
    h->A = (int *) malloc(h->heapsize * sizeof(int));
    for(int i=0;i<h->heapsize;i++)
        h->A[i] = rand()%100;
    fprintf(stdout,"Initial array: ");
    printHeap(h);
    heapBuild(h);
    fprintf(stdout,"Heap: ");
    printHeap(h);
    heapSort(h);
    fprintf(stdout,"Heap sorted: ");
    printHeap(h);
    return 0;
}

#ifndef HEAPPRIVATE_H_INCLUDED
#define HEAPPRIVATE_H_INCLUDED
#define LEFT(i) (i*2)+1
#define RIGHT(i) (i*2)+2
#define PARENT(i) (i-1)/2
typedef struct heapS heapT;
struct heapS{
    int *A;
    int heapsize;
};


#endif // HEAPPRIVATE_H_INCLUDED

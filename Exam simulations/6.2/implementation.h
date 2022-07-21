#ifndef IMPLEMENTATION_H_INCLUDED
#define IMPLEMENTATION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
typedef struct nodeS nodeT;
struct nodeS{
    int key;
    nodeT *left;
    nodeT *right;
};
nodeT *createNode(int);
nodeT *insertNode(nodeT *,int);
void writePath(nodeT *,int,int,int *);
#endif // IMPLEMENTATION_H_INCLUDED

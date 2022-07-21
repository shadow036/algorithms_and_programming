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
void duplicateTree(nodeT *);
nodeT *createNode(int);
nodeT *insertNode(nodeT *,int);
void inOrderVisit(nodeT *);
#endif // IMPLEMENTATION_H_INCLUDED

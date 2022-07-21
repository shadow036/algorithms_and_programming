#ifndef IMPLEMENTATION_H_INCLUDED
#define IMPLEMENTATION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define N 5
typedef struct nodeS nodeT;
struct nodeS{
    int key;
    nodeT *child[N];
};
void levelByLevelVisit(nodeT *,int,int);
void preOrderVisit(nodeT *,int,int);
#endif // IMPLEMENTATION_H_INCLUDED

#ifndef TREEPRIVATE_H_INCLUDED
#define TREEPRIVATE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
typedef struct nodeS nodeT;
struct nodeS{
    int key;
    nodeT *left;
    nodeT *right;
};


#endif // TREEPRIVATE_H_INCLUDED

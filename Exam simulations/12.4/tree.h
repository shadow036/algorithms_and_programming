#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME 10+1
#include "list.h"
typedef struct nodeS nodeT;
struct nodeS{
    char id[ID];
    nodeT **children;
    int numberOfChildren;
    nodeT *parent;
};
nodeT *loadTree(FILE *);
nodeT *createNode(char *);
nodeT *searchNode(char *,nodeT *);
void findMaxDepth(nodeT *,int *,int);
void visitWrapper(nodeT *,int);
void visit(nodeT *,int,int);
void findLongestID(nodeT *,elementT *,elementT **,int *);
#endif // TREE_H_INCLUDED

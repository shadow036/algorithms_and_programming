#ifndef TREEPUBLIC_H_INCLUDED
#define TREEPUBLIC_H_INCLUDED
#include "treePrivate.h"
nodeT *createNode(int);
nodeT *searchNode(nodeT *,int);
nodeT *createTree(FILE *);
nodeT *insertNode(nodeT *,nodeT *);
void inOrderTraversal(nodeT *);
nodeT *removeNode(nodeT *,int);
nodeT *minimumNode(nodeT *);
nodeT *maximumNode(nodeT *);
#endif // TREEPUBLIC_H_INCLUDED

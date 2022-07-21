#ifndef TREEPUBLIC_H_INCLUDED
#define TREEPUBLIC_H_INCLUDED
#include "treePrivate.h"
nodeT *createNode(char *);
nodeT *insertNode(nodeT *,nodeT *);
void inOrderTraversal(nodeT *);
nodeT *createBST(FILE *);
int treeIsomorphism(nodeT *,nodeT *);
#endif // TREEPUBLIC_H_INCLUDED

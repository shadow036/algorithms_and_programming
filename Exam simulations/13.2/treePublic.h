#ifndef TREEPUBLIC_H_INCLUDED
#define TREEPUBLIC_H_INCLUDED
#include "treePrivate.h"
nodeT *createNode(int);
nodeT *insertNode(nodeT *,nodeT *);
void inOrderTraversal(nodeT *);
nodeT *createBST(FILE *);
nodeT *treeMirror(nodeT *);
#endif // TREEPUBLIC_H_INCLUDED

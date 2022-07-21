#ifndef IMPLEMENTATION_H_INCLUDED
#define IMPLEMENTATION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct nodeS nodeT;
struct nodeS{
    char *firstName;
    char *lastName;
    int mark;
    nodeT *leftChild;
    nodeT *rightSibling;
};
char *generateRandomName();
nodeT *insertNode(nodeT *,char *,char *,int);
nodeT *createNode(char *,char *,int);
void visit(nodeT *);
#endif // IMPLEMENTATION_H_INCLUDED

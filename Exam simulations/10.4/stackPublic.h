#ifndef STACKPUBLIC_H_INCLUDED
#define STACKPUBLIC_H_INCLUDED
#include "stackPrivate.h"
void push(nodeT **,char *);
void pop(nodeT **);
nodeT *createNode(char *);
void printStack(nodeT *);
#endif // STACKPUBLIC_H_INCLUDED

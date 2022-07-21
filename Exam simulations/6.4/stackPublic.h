#ifndef STACKPUBLIC_H_INCLUDED
#define STACKPUBLIC_H_INCLUDED
#include "stackPrivate.h"
nodeT *createNode(char *id);
void push(nodeT **,nodeT **,char *);
void pop(nodeT **,nodeT **);
#endif // STACKPUBLIC_H_INCLUDED

#ifndef IMPLEMENTATION_H_INCLUDED
#define IMPLEMENTATION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
typedef struct nodeS nodeT;
struct nodeS{
    char *str;
    nodeT *next;
};
nodeT *stringSplit(char *);
nodeT *createNode(char *,int,int);
void printList(nodeT *);
#endif // IMPLEMENTATION_H_INCLUDED

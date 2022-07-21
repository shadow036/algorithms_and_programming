#ifndef STACKPRIVATE_H_INCLUDED
#define STACKPRIVATE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ID 20+1
typedef struct nodeS nodeT;
struct nodeS{
    char id[ID];
    nodeT *nextNode;
};


#endif // STACKPRIVATE_H_INCLUDED

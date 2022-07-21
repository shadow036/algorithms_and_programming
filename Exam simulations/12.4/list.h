#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#define ID 100+1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct elementS elementT;
struct elementS{
    char id[ID];
    elementT *next;
};
void addElement(elementT **,char *);
void removeElement(elementT **);
elementT *createElement(char *);
#endif // LIST_H_INCLUDED

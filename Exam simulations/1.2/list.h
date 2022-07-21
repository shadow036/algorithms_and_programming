#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 20+1
typedef struct personS personT;
struct personS{
    char *surname;
    char *name;
    personT *next;
};
int orderedInsertion(personT **,char *,char *);
personT *createPerson(char *,char *);
void printPeople(personT *);
#endif // LIST_H_INCLUDED

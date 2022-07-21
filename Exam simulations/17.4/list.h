#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LENGTH 50+1
#define DATE 10+1
typedef struct optionalS optionalT;
struct optionalS{
    char optionalName[LENGTH];
    char availabilityData[DATE];
    int price;
    optionalT *next;
};
optionalT *createList(FILE *);
optionalT *createOptional(char *,char *,int);
optionalT *deleteOptional(optionalT *,char *);
void printOptionals(optionalT *);
#endif // LIST_H_INCLUDED

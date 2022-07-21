#include <stdio.h>
#include <stdlib.h>
typedef struct dataS dataT;
struct dataS{
    char id;
    int priority;
    dataT *next;
};
void push(dataT **,char,int);
void pop(dataT **);
void peek(dataT *);
dataT *createData(char,int);
int isAlreadyPresent(dataT *,char);
void show(dataT *);

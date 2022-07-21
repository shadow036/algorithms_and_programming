#ifndef TREEPRIVATE_H_INCLUDED
#define TREEPRIVATE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATE 10+1
#define PROGRAM 5+1
#define FILENAME 20+1
#define NAME 20+1
#define COMMAND 20+1
typedef struct nodeS nodeT;
struct nodeS{
    int registerNumber;
    char *lastName;
    char *firstName;
    char birthDate[DATE];
    char program[PROGRAM];
    int enrollmentYear;
    nodeT *rightName;
    nodeT *leftName;
    nodeT *rightNumber;
    nodeT *leftNumber;
};


#endif // TREEPRIVATE_H_INCLUDED

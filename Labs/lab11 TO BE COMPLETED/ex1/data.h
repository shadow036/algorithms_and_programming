#ifndef _DATA_INCLUDED
#define _DATA_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define REGISTER_NUMBER 9+1
#define LAST_NAME 100+1

typedef struct data data_t;
struct data{
    char registerNumber[REGISTER_NUMBER];
    char lastName[LAST_NAME];
    int numberCreditLoaded;
    int numberCreditPassed;
};
int readData (FILE *, data_t *);
void writeData (FILE *, data_t);
int compare (data_t, data_t);

#endif

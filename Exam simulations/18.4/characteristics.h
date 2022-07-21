#ifndef CHARACTERISTICS_H_INCLUDED
#define CHARACTERISTICS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 50+1
typedef struct characteristicS characteristicT;
struct characteristicS{
    char name[LENGTH];
    char value[LENGTH];
    characteristicT *nextCharacteristic;
};
characteristicT *createSecondaryList(FILE *);
characteristicT *createCharacteristic(char *,char *);
#endif // CHARACTERISTICS_H_INCLUDED

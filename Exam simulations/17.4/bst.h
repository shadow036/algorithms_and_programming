#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include "list.h"
typedef struct carS carT;
struct carS{
    char modelName[LENGTH];
    char availabilityData[DATE];
    int price;
    char optionFile[LENGTH];
    optionalT *optionalsList;
    carT *left;
    carT *right;
};
carT *createBST(FILE *);
carT *createCar(char *,char *,int,char *);
carT *insertCar(carT *,carT *);
carT *deleteCar(carT *,char *);
carT *searchCar(carT *,char *);
void findBestMatch(carT *,optionalT *,carT **,int *);
int countMatches(optionalT *,optionalT *);
carT *minimumCar(carT *);
carT *maximumCar(carT *);
void inOrderTraversal(carT *);
#endif // BST_H_INCLUDED

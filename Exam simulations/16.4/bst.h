#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#define LENGTH 50+1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct customerS customerT;
struct customerS{
    char lastName[LENGTH];
    char firstName[LENGTH];
    char iban[LENGTH];
    int finalDeposit;
    customerT *left;
    customerT *right;
};
customerT *createBST(FILE *);
customerT *createCustomer(char *,char *,char *,int);
customerT *insertCustomer(customerT *,customerT *);
void findCustomer(customerT *,char *,char *,char *,char *,char *,char *);
#endif // BST_H_INCLUDED

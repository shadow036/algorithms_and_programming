#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "bst.h"
typedef struct bankS bankT;
struct bankS{
    char bankName[LENGTH];
    char branchName[LENGTH];
    char abi[LENGTH];
    char cab[LENGTH];
    char filename[LENGTH];
    customerT *customersBST;
    bankT *next;
};
bankT *createBank(char *,char *,char *,char *,char *);
bankT *createList(FILE *);
void findAccounts(bankT *,char *,char *);
#endif // LIST_H_INCLUDED

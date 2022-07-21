#include <stdio.h>
#include <stdlib.h>
#include "list.h"
int main()
{
    char lastName[LENGTH];
    char firstName[LENGTH];
    bankT *banks = createList(fopen("banks.txt","r"));
    while(strcmp(lastName,"exit")){
        fprintf(stdout,"lastName firstName => ");
        fscanf(stdin,"%s %s",lastName,firstName);
        findAccounts(banks,lastName,firstName);
        fprintf(stdout,"\n");
    }
    return 0;
}

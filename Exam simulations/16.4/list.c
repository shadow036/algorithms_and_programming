#include "list.h"
bankT *createBank(char *bankName,char *branchName,char *abi,char *cab,char *filename){
    bankT *newBank = (bankT *) malloc(sizeof(bankT));
    strcpy(newBank->bankName,bankName);
    strcpy(newBank->branchName,branchName);
    strcpy(newBank->abi,abi);
    strcpy(newBank->cab,cab);
    strcpy(newBank->filename,filename);
    newBank->customersBST = NULL;
    newBank->next = NULL;
    return newBank;
}
bankT *createList(FILE *f){
    char bankName[LENGTH];
    char branchName[LENGTH];
    char abi[LENGTH];
    char cab[LENGTH];
    char filename[LENGTH];
    bankT *banks = NULL;
    while(fscanf(f,"%s %s %s %s %s",bankName,branchName,abi,cab,filename) != EOF){
        bankT *newBank = createBank(bankName,branchName,abi,cab,filename);
        newBank->customersBST = createBST(fopen(filename,"r"));
        newBank->next = banks;
        banks = newBank;
    }
    return banks;
}
void findAccounts(bankT *banks,char *lastName,char *firstName){
    bankT *temp = banks;
    while(temp != NULL){
        findCustomer(temp->customersBST,lastName,firstName,temp->bankName,temp->branchName,temp->abi,temp->cab);
        temp = temp->next;
    }
}

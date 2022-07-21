#include "bst.h"
customerT *createBST(FILE *f){
    customerT *bst = NULL;
    char lastName[LENGTH];
    char firstName[LENGTH];
    char iban[LENGTH];
    int finalDeposit;
    while(fscanf(f,"%s %s %s %d",lastName,firstName,iban,&finalDeposit) != EOF){
        customerT *newCustomer = createCustomer(lastName,firstName,iban,finalDeposit);
        bst = insertCustomer(bst,newCustomer);
    }
    return bst;
}
customerT *createCustomer(char *lastName,char *firstName,char *iban,int finalDeposit){
    customerT *newCustomer = (customerT *) malloc(sizeof(customerT));
    strcpy(newCustomer->lastName,lastName);
    strcpy(newCustomer->firstName,firstName);
    strcpy(newCustomer->iban,iban);
    newCustomer->finalDeposit = finalDeposit;
    newCustomer->left = NULL;
    newCustomer->right = NULL;
    return newCustomer;
}
customerT *insertCustomer(customerT *bst,customerT *newCustomer){
    if(bst == NULL)
        return newCustomer;
    if(strcmp(bst->lastName,newCustomer->lastName) <= 0)
        bst->left = insertCustomer(bst->left,newCustomer);
    else
        bst->right = insertCustomer(bst->right,newCustomer);
    return bst;
}
void findCustomer(customerT *customers,char *lastName,char *firstName,char *bankName,char *branchName,char *abi,char *cab){
    if(customers == NULL)
        return;
    if(!strcmp(customers->lastName,lastName) && !strcmp(customers->firstName,firstName)){
        fprintf(stdout,"%s %s %s %s %s %d\n",bankName,branchName,abi,cab,customers->iban,customers->finalDeposit);
        findCustomer(customers->left,lastName,firstName,bankName,branchName,abi,cab);
    }else if(strcmp(customers->lastName,lastName) < 0)
        findCustomer(customers->left,lastName,firstName,bankName,branchName,abi,cab);
    else
        findCustomer(customers->right,lastName,firstName,bankName,branchName,abi,cab);
    return;
}

#include "bst.h"
carT *createBST(FILE *f){
    carT *bst = NULL;
    char modelName[LENGTH];
    char availabilityData[DATE];
    int price;
    char optionFile[LENGTH];
    while(fscanf(f,"%s %s %d %s",modelName,availabilityData,&price,optionFile) != EOF){
        carT *newCar = createCar(modelName,availabilityData,price,optionFile);
        newCar->optionalsList = createList(fopen(optionFile,"r"));
        bst = insertCar(bst,newCar);
    }
    return bst;
}
carT *createCar(char *modelName,char *availabilityData,int price,char *optionFile){
    carT *newCar = (carT *) malloc(sizeof(carT));
    strcpy(newCar->modelName,modelName);
    strcpy(newCar->availabilityData,availabilityData);
    newCar->price = price;
    strcpy(newCar->optionFile,optionFile);
    newCar->optionalsList = NULL;
    newCar->left = NULL;
    newCar->right = NULL;
    return newCar;
}
carT *insertCar(carT *bst,carT *newCar){
    if(bst == NULL)
        return newCar;
    if(strcmp(newCar->modelName,bst->modelName) <= 0)
        bst->left = insertCar(bst->left,newCar);
    else
        bst->right = insertCar(bst->right,newCar);
    return bst;
}
carT *deleteCar(carT *bst,char *modelName){
    if(bst == NULL) //BST IS EMPTY OR THE CAR IS NOT PRESENT
        return NULL;
    else if(strcmp(bst->modelName,modelName) > 0)
        bst->left = deleteCar(bst->left,modelName);
    else if(strcmp(bst->modelName,modelName) < 0)
        bst->right = deleteCar(bst->right,modelName);
    else{    //FOUND
        if(bst->left == NULL)
            return bst->right;
        else if(bst->right == NULL)
            return bst->left;
        else{
            carT *temp = minimumCar(bst->right);
            strcpy(bst->modelName,temp->modelName);
            strcpy(bst->availabilityData,temp->availabilityData);
            bst->optionalsList = temp->optionalsList;
            strcpy(bst->optionFile,temp->optionFile);
            bst->price = temp->price;
            bst->right = deleteCar(bst->right,temp->modelName);
        }
    }
    return bst;
}
carT *searchCar(carT *bst,char *modelName){
    if(!strcmp(bst->modelName,modelName))
        return bst;
    if(bst == NULL)
        return NULL;
    if(strcmp(modelName,bst->modelName) < 0)
        return searchCar(bst->left,modelName);
    else
        return searchCar(bst->right,modelName);
}
void findBestMatch(carT *bst,optionalT *optionals,carT **bestCar,int *bestMatches){
    if(bst == NULL)
        return;
    findBestMatch(bst->left,optionals,bestCar,bestMatches);
    int currentMatches = countMatches(optionals,bst->optionalsList);
    if(currentMatches > *bestMatches || (currentMatches == *bestMatches && bst->price < (*bestCar)->price)){
        *bestCar = bst;
        *bestMatches = currentMatches;
    }
    findBestMatch(bst->right,optionals,bestCar,bestMatches);
}
int countMatches(optionalT *requiredOptionals,optionalT *currentCarOptionals){
    int matches = 0;
    optionalT *temp = requiredOptionals;
    while(temp != NULL){
        optionalT *temp2 = currentCarOptionals;
        while(temp2 != NULL){
            if(!strcmp(temp->optionalName,temp2->optionalName))
                matches++;
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    return matches;
}
carT *minimumCar(carT *currentCar){
    if(currentCar == NULL)
        return NULL;
    if(currentCar->left == NULL)
        return currentCar;
    return minimumCar(currentCar->left);
}
carT *maximumCar(carT *currentCar){
    if(currentCar == NULL)
        return NULL;
    if(currentCar->right == NULL)
        return currentCar;
    return maximumCar(currentCar->right);
}
void inOrderTraversal(carT *bst){
    if(bst == NULL)
        return;
    inOrderTraversal(bst->left);
    fprintf(stdout,"\n%s (availability: %s, price: %d, file: %s)",bst->modelName,bst->availabilityData,bst->price,bst->optionFile);
    printOptionals(bst->optionalsList);
    inOrderTraversal(bst->right);
}

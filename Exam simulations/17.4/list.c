#include "list.h"
optionalT *createList(FILE *f){
    if(f == NULL)
        return NULL;
    optionalT *optionals = NULL;
    char optionalName[LENGTH];
    char availabilityData[DATE];
    int price;
    while(fscanf(f,"%s %s %d",optionalName,availabilityData,&price) != EOF){
        optionalT *newOptional = createOptional(optionalName,availabilityData,price);
        newOptional->next = optionals;
        optionals = newOptional;
    }
    return optionals;
}
optionalT *createOptional(char *optionalName,char *availabilityData,int price){
    optionalT *newOptional = (optionalT *) malloc(sizeof(optionalT));
    strcpy(newOptional->optionalName,optionalName);
    strcpy(newOptional->availabilityData,availabilityData);
    newOptional->price = price;
    newOptional->next = NULL;
    return newOptional;
}
optionalT *deleteOptional(optionalT *optionalsList,char *optionalName){
    if(!strcmp(optionalsList->optionalName,optionalName))
        return optionalsList->next;
    optionalT *temp = optionalsList;
    while(!strcmp(temp->next->optionalName,optionalName))
        temp = temp->next;
    temp->next = temp->next->next;
    return optionalsList;
}
void printOptionals(optionalT *optionals){
    optionalT *temp = optionals;
    while(temp != NULL){
        fprintf(stdout,"\n  %s (availability: %s, price: %d)",temp->optionalName,temp->availabilityData,temp->price);
        temp = temp->next;
    }
}

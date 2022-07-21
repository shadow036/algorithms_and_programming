#include "list.h"
int orderedInsertion(personT **people,char *surname,char *name){
    personT *temp = *people;
    while(temp != NULL){
        if(!strcmp(temp->name,name) && !strcmp(temp->surname,surname))
            return 0;
        temp = temp->next;
    }
    personT *newPerson = createPerson(surname,name);
    if(*people == NULL || strcmp((*people)->surname,surname) > 0 || (strcmp((*people)->surname,surname) == 0 && strcmp((*people)->name,name) > 0)){
        newPerson->next = *people;
        *people = newPerson;
    }else{
        temp = *people;
        while(temp->next != NULL && (strcmp(temp->next->surname,surname) < 0 || (strcmp(temp->next->surname,surname) == 0 && strcmp(temp->next->name,name) < 0)))
            temp = temp->next;
        newPerson->next = temp->next;
        temp->next = newPerson;
    }
    return 1;
}
personT *createPerson(char *surname,char *name){
    personT *newPerson = (personT *) malloc(sizeof(personT));
    newPerson->name = (char *) malloc((strlen(name)+1) * sizeof(char));
    newPerson->surname = (char *) malloc((strlen(surname)+1) * sizeof(char));
    strcpy(newPerson->name,name);
    strcpy(newPerson->surname,surname);
    newPerson->next = NULL;
    return newPerson;
}
void printPeople(personT *people){
    fprintf(stdout,"\n");
    personT *temp = people;
    while(temp != NULL){
        fprintf(stdout,"%s %s -> ",temp->surname,temp->name);
        temp = temp->next;
    }
    fprintf(stdout,"NULL\n\n");
}

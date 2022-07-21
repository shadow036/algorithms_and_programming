#include "list.h"
void addElement(elementT **head,char *id){
    elementT *newElement = createElement(id);
    if(*head == NULL){
        *head = newElement;
    }else{
        elementT *temp = *head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = newElement;
    }
}
void removeElement(elementT **head){
    if(*head == NULL){
        fprintf(stdout,"Underflow!");
    }else if((*head)->next == NULL){
        *head = NULL;
    }else{
        elementT *temp = *head;
        while(temp->next->next != NULL)
            temp = temp->next;
        temp->next = NULL;
    }
}
elementT *createElement(char *id){
    elementT *newElement = (elementT *) malloc(sizeof(elementT));
    strcpy(newElement->id,id);
    newElement->next = NULL;
    return newElement;
}

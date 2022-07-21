#include <stdio.h>
#include <stdlib.h>
#include "queuePublic.h"
void enqueue(elementT **head,elementT **tail,char newElementId){
    elementT *newElement = createElement(newElementId);
    if(*head == NULL)
        *head = newElement;
    else
        (*tail)->nextElement = newElement;
    *tail = newElement;
}
elementT *dequeue(elementT **head,elementT **tail){
    if(*head == NULL)
        return NULL;
    else{
        elementT *temp = *head;
        *head = (*head)->nextElement;
        return temp;
    }
}
elementT *createElement(char id){
    elementT *newElement = (elementT *) malloc(sizeof(elementT));
    newElement->id = id;
    newElement->nextElement = NULL;
    return newElement;
}

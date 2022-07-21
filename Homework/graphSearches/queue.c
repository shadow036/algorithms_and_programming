#include <stdlib.h>
#include <stdio.h>
#include "queuePublic.h"
void enqueue(elementT **head,elementT **tail,elementT *newElement){
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
        (*head) = (*head)->nextElement;
        return temp;
    }
}
elementT *createElement(vertexT *vertex){
    elementT *newElement = (elementT *) malloc(sizeof(elementT));
    newElement->vertex = vertex;
    newElement->nextElement = NULL;
    return newElement;
}

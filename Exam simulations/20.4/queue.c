#include "queue.h"
void enqueue(elementT **head,elementT **tail,vertexT *vertex){
    elementT *newElement = createElement(vertex);
    if(*head == NULL){
        *head = newElement;
        *tail = newElement;
    }else{
        (*tail)->nextElement = newElement;
        *tail = newElement;
    }
}
vertexT *dequeue(elementT **head,elementT **tail){
    if(*head == NULL)
        return NULL;
    elementT *temp = *head;
    *head = (*head)->nextElement;
    return temp->vertex;
}
elementT *createElement(vertexT *vertex){
    elementT *newElement = (elementT *) malloc(sizeof(elementT));
    newElement->vertex = vertex;
    newElement->nextElement = NULL;
    return newElement;
}

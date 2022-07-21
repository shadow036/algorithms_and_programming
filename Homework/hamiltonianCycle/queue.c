#include <stdio.h>
#include <stdlib.h>
#include "queuePublic.h"
queueT *createQueue(int vertexId){
    queueT *newQueue = (queueT *) malloc(sizeof(queueT));
    newQueue->vertexId = vertexId;
    newQueue->nextQueue = NULL;
    return newQueue;
}
void enqueue(queueT **head,queueT **tail,int vertexId){
    queueT *newQueue = createQueue(vertexId);
    if(*head == NULL)
        *head = newQueue;
    else
        (*tail)->nextQueue = newQueue;
    *tail = newQueue;

}
queueT *dequeue(queueT **head,queueT **tail){
    if(*head == NULL)
        return NULL;
    else{
        queueT *temp = *head;
        (*head) = (*head)->nextQueue;
        if(*head == NULL)
            free(*tail);
        return temp;
    }
}
void printQueue(queueT *head){
    for(queueT *temp = head;temp != NULL;temp = temp->nextQueue)
        fprintf(stdout,"%d ",temp->vertexId);
}

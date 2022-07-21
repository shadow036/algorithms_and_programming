#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stackPublic.h"
/*
bos = bottom of stack
top = top of stack
*/
nodeT *createNode(char *id){
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    strcpy(newNode->id,id);
    newNode->nextNode = NULL;
    return newNode;
}
void push(nodeT **bos,nodeT **tos,char *id){
    nodeT *newNode = createNode(id);
    if(*bos == NULL){
        *bos = newNode;
        *tos = newNode;
        return;
    }
    (*tos)->nextNode = newNode;
    *tos = newNode;
}
void pop(nodeT **bos,nodeT **tos){
    nodeT *temp;
    for(temp = *bos;temp->nextNode->nextNode != NULL;temp = temp->nextNode);
    temp->nextNode = NULL;
    *tos = temp;
}

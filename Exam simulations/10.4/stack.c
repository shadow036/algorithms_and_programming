#include "stackPublic.h"
void push(nodeT **stack,char *id){
    if(*stack == NULL)
        *stack = createNode(id);
    else{
        nodeT *temp = *stack;
        while(temp->nextNode != NULL)
            temp = temp->nextNode;
        temp->nextNode = createNode(id);
    }
}
void pop(nodeT **stack){
    if(*stack == NULL || (*stack)->nextNode == NULL)
        *stack = NULL;
    else{
        nodeT *temp = *stack;
        while(temp->nextNode->nextNode != NULL)
            temp = temp->nextNode;
        temp->nextNode = NULL;
    }
}
nodeT *createNode(char *id){
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    strcpy(newNode->id,id);
    newNode->nextNode = NULL;
    return newNode;
}
void printStack(nodeT *stack){
    fprintf(stdout,"\n\n");
    nodeT *temp = stack;
    while(temp != NULL){
        fprintf(stdout,"%s -> ",temp->id);
        temp = temp->nextNode;
    }
    fprintf(stdout,"NULL\n");
}

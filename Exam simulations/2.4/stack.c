#include "stack.h"
void push(edgeT **currentSolution,edgeT *newEdge){
    if(*currentSolution == NULL)
        *currentSolution = newEdge;
    else{
        edgeT *temp = *currentSolution;
        while(temp->nextEdge != NULL)
            temp = temp->nextEdge;
        temp->nextEdge = newEdge;
    }
}
void pop(edgeT **currentSolution){
    if(*currentSolution == NULL || (*currentSolution)->nextEdge == NULL)
        *currentSolution = NULL;
    else{
        edgeT *temp = *currentSolution;
        while(temp->nextEdge->nextEdge != NULL)
            temp = temp->nextEdge;
        temp->nextEdge = NULL;
    }
}

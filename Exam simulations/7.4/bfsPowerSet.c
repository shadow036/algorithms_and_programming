#include <stdlib.h>
#include <stdio.h>
#include "bfsPowerSet.h"
#include "graphPublic.h"
#include "queuePublic.h"
void bfs(vertexT *graph){
    clearColors(graph);
    elementT *head = NULL;
    elementT *tail = NULL;
    graph->color = GRAY;
    enqueue(&head,&tail,graph->id);
    while(head != NULL){
        vertexT *currentVertex = findVertex(graph,dequeue(&head,&tail)->id);
        currentVertex->color = GRAY;
        edgeT *temp = currentVertex->edgesList;
        while(temp != NULL){
            if(temp->destination->color == WHITE && temp->connected == TRUE){
                temp->destination->color = GRAY;
                enqueue(&head,&tail,temp->destination->id);
            }
            temp = temp->nextEdge;
        }
        currentVertex->color = BLACK;
    }
}
int powerSetWrapper(vertexT *graph,int numberOfEdges){
    int flag = 0;
    for(int i=0;i<numberOfEdges;i++){
        clearDisconnections(graph);
        powerSet(graph,0,i,numberOfEdges,&flag);
        if(flag == 1)
            return i;
    }
    return numberOfEdges;
}
void powerSet(vertexT *graph,int n,int k,int numberOfEdges,int *flag){
    if(n >= k){
        bfs(graph);
        if(checkDisconnections(graph) == 1)
            *flag = 1;
        return;
    }
    vertexT *temp = graph;
    while(temp != NULL){
        edgeT *temp2 = temp->edgesList;
        while(temp2 != NULL){
            if(temp2->connected == TRUE){
                //temp2->connected = FALSE;   //DISCONNECT EDGE IN ONE DIRECTION
                disconnectEdge(temp,temp2->destination);    //DISCONNECT EDGE IN BOTH DIRECTIONS
                powerSet(graph,n+1,k,numberOfEdges,flag);
                connectEdge(temp,temp2->destination);
                //temp2->connected = TRUE;
            }
            temp2 = temp2->nextEdge;
        }
        temp = temp->nextVertex;
    }
    return;
}
int checkDisconnections(vertexT *graph){
    vertexT *temp = graph;
    while(temp != NULL){
        if(temp->color == WHITE)
            return 1;
        temp = temp->nextVertex;
    }
    return 0;
}
void clearColors(vertexT *graph){
    vertexT *temp = graph;
    while(temp != NULL){
        temp->color = WHITE;
        temp = temp->nextVertex;
    }
}
void clearDisconnections(vertexT *graph){   //USELESS
    vertexT *temp = graph;
    while(temp != NULL){
        edgeT *temp2 = temp->edgesList;
        while(temp2 != NULL){
            if(temp2->connected == FALSE)
                temp2->connected = TRUE;
            temp2 = temp2->nextEdge;
        }
        temp = temp->nextVertex;
    }
}
void disconnectEdge(vertexT *firstVertex,vertexT *secondVertex){
    edgeT *edgesList = firstVertex->edgesList;
    while(edgesList != NULL){
        if(edgesList->destination->id == secondVertex->id){
            edgesList->connected = FALSE;
            break;
        }
        edgesList = edgesList->nextEdge;
    }
    edgesList = secondVertex->edgesList;
    while(edgesList != NULL){
        if(edgesList->destination->id == firstVertex->id){
            edgesList->connected = FALSE;
            break;
        }
        edgesList = edgesList->nextEdge;
    }
}
void connectEdge(vertexT *firstVertex,vertexT *secondVertex){
    edgeT *edgesList = firstVertex->edgesList;
    while(edgesList != NULL){
        if(edgesList->destination->id == secondVertex->id){
            edgesList->connected = TRUE;
            break;
        }
        edgesList = edgesList->nextEdge;
    }
    edgesList = secondVertex->edgesList;
    while(edgesList != NULL){
        if(edgesList->destination->id == firstVertex->id){
            edgesList->connected = TRUE;
            break;
        }
        edgesList = edgesList->nextEdge;
    }
}

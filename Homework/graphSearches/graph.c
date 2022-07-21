#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "graphPublic.h"
#include "queuePublic.h"
vertexT *createVertex(char id){
    vertexT *newVertex = (vertexT *) malloc(sizeof(vertexT));
    newVertex->id = id;
    newVertex->distance = 0;
    newVertex->color = WHITE;
    newVertex->predecessor = NULL;
    newVertex->edgesList = NULL;
    newVertex->nextVertex = NULL;
    return newVertex;
}
edgeT *createEdge(vertexT *destination){
    edgeT *newEdge = (edgeT *) malloc(sizeof(edgeT));
    newEdge->destination = destination;
    newEdge->nextEdge = NULL;
    return newEdge;
}
vertexT *findVertex(vertexT *graph,char id){
    vertexT *temp = graph;
    while(temp != NULL){
        if(temp->id == id)
            return temp;
        temp = temp->nextVertex;
    }
    return NULL;
}
vertexT *createGraph(FILE *f){
    vertexT *graph = NULL;
    char sourceId,destinationId;
    while(fscanf(f,"%c%*c%c\n",&sourceId,&destinationId) != EOF){
        vertexT *sourceVertex = findVertex(graph,sourceId);
        vertexT *destinationVertex = findVertex(graph,destinationId);
        if(sourceVertex == NULL){
            sourceVertex = createVertex(sourceId);
            sourceVertex->nextVertex = graph;
            graph = sourceVertex;
        }
        if(destinationVertex == NULL){
            destinationVertex = createVertex(destinationId);
            destinationVertex->nextVertex = graph;
            graph = destinationVertex;
        }
        edgeT *newEdge = createEdge(destinationVertex);
        newEdge->nextEdge = sourceVertex->edgesList;
        sourceVertex->edgesList = newEdge;
        /*edgeT *newEdge2 = createEdge(sourceVertex);
        newEdge2->nextEdge = destinationVertex->edgesList;
        destinationVertex->edgesList = newEdge2;*/
    }
    fclose(f);
    return graph;
}
void printGraph(vertexT *graph){
    vertexT *temp = graph;
    while(temp != NULL){
        fprintf(stdout,"\n%c => ",temp->id);
        edgeT *temp2 = temp->edgesList;
        while(temp2 != NULL){
            fprintf(stdout,"%c -> ",temp2->destination->id);
            temp2 = temp2->nextEdge;
        }
        fprintf(stdout,"NULL");
        temp = temp->nextVertex;
    }
}
void generateGraph(){
    srand(time(0));
    FILE *f = fopen("graph.txt","w");
    for(int i=0;i<100;i++)
        fprintf(f,"%c %c\n",97+rand()%26,97+rand()%26);
    fclose(f);
}
void bfs(vertexT *graph,vertexT *sourceVertex){
    clear(graph);
    sourceVertex->color = GRAY;
    sourceVertex->distance = 0;
    elementT *head = NULL;
    elementT *tail = NULL;
    enqueue(&head,&tail,createElement(sourceVertex));
    while(head != NULL){
        vertexT *dequeuedNode = dequeue(&head,&tail)->vertex;
        if(dequeuedNode->predecessor == NULL)
            fprintf(stdout,"\n%c (distance from %c: %d, predecessor: NULL)",dequeuedNode->id,sourceVertex->id,dequeuedNode->distance);
        else
            fprintf(stdout,"\n%c (distance from %c: %d, predecessor: %c)",dequeuedNode->id,sourceVertex->id,dequeuedNode->distance,dequeuedNode->predecessor->id);
        edgeT *temp = dequeuedNode->edgesList;
        while(temp != NULL){
            if(temp->destination->color == WHITE){
                temp->destination->color = GRAY;
                temp->destination->distance = dequeuedNode->distance+1;
                temp->destination->predecessor = dequeuedNode;
                enqueue(&head,&tail,createElement(temp->destination));
            }
            temp = temp->nextEdge;
        }
        dequeuedNode->color = BLACK;
    }
    vertexT *temp2 = graph;
    while(temp2 != NULL){
        if(temp2->color == WHITE)
            fprintf(stdout,"\n%c (distance from %c: INFINITY, predecessor: NULL)",temp2->id,sourceVertex->id);
        temp2 = temp2->nextVertex;
    }
}
int dfs(vertexT *currentVertex,int time){
    time = time+1;
    currentVertex->discoveryTime = time;
    currentVertex->color = GRAY;
    edgeT *temp = currentVertex->edgesList;
    while(temp != NULL){
        if(temp->destination->color == WHITE){
            temp->destination->predecessor = currentVertex;
            time = dfs(temp->destination,time);
        }
        temp = temp->nextEdge;
    }
    currentVertex->color = BLACK;
    time = time+1;
    currentVertex->endprocessingTime = time;
    fprintf(stdout,"\n%c (discovery time: %d, endprocessing time: %d)",currentVertex->id,currentVertex->discoveryTime,currentVertex->endprocessingTime);
    return time;
}
void clear(vertexT *graph){
    vertexT *temp = graph;
    while(temp != NULL){
        temp->color = WHITE;
        temp->distance = INT_MAX;
        temp->predecessor = NULL;
        temp = temp->nextVertex;
    }
}

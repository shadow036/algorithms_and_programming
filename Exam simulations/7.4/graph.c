#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphPublic.h"
void generateGraph(int *numberOfEdges){
    srand(time(0));
    FILE *f = fopen("graph.txt","w");
    *numberOfEdges = 75;
    for(int i=0;i<*numberOfEdges;i++)
        fprintf(f,"%c %c\n",97+rand()%26,97+rand()%26);
    fclose(f);
}
vertexT *createVertex(char id){
    vertexT *newVertex = (vertexT *) malloc(sizeof(vertexT));
    newVertex->id = id;
    newVertex->color = WHITE;
    newVertex->edgesList = NULL;
    newVertex->nextVertex = NULL;
    return newVertex;
}
edgeT *createEdge(vertexT *destination){
    edgeT *newEdge = (edgeT *) malloc(sizeof(edgeT));
    newEdge->destination = destination;
    newEdge->connected = TRUE;
    newEdge->nextEdge = NULL;
    return newEdge;
}
vertexT *createGraph(FILE *f){
    vertexT *graph = NULL;
    char sourceId,destinationId;
    while(fscanf(f,"%c%*c%c\n",&sourceId,&destinationId) != EOF){
        vertexT *sourceVertex = findVertex(graph,sourceId);
        if(sourceVertex == NULL){
            sourceVertex = createVertex(sourceId);
            sourceVertex->nextVertex = graph;
            graph = sourceVertex;
        }
        vertexT *destinationVertex = findVertex(graph,destinationId);
        if(destinationVertex == NULL){
            destinationVertex = createVertex(destinationId);
            destinationVertex->nextVertex = graph;
            graph = destinationVertex;
        }
        edgeT *newEdge = createEdge(destinationVertex);
        newEdge->nextEdge = sourceVertex->edgesList;
        sourceVertex->edgesList = newEdge;
        edgeT *newEdge2 = createEdge(sourceVertex);
        newEdge2->nextEdge = destinationVertex->edgesList;
        destinationVertex->edgesList = newEdge2;
    }
    return graph;
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

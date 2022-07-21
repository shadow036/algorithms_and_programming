#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphPublic.h"
#include "queuePublic.h"
void graphGenerator(){
    srand(time(0));
    FILE *f = fopen("graph.txt","w");
    int numberOfEdges = 10 + rand()%11;
    for(int i=0;i<numberOfEdges;i++)
        fprintf(f,"%c %c\n",97 + rand()%26,97 + rand()%26);
    fclose(f);
}
vertexT *createGraph(FILE *f){
    vertexT *graph = NULL;
    int sourceId,destinationId;
    while(fscanf(f,"%d %d",&sourceId,&destinationId) != EOF){
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
vertexT *createVertex(int id){
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
    newEdge->nextEdge = NULL;
    return newEdge;
}
vertexT *findVertex(vertexT *graph,int id){
    for(vertexT *temp = graph;temp != NULL;temp = temp->nextVertex){
        if(temp->id == id)
            return temp;
    }
    return NULL;
}
void printGraph(vertexT *graph){
    for(vertexT *temp = graph;temp != NULL;temp = temp->nextVertex){
        fprintf(stdout,"\n%d => ",temp->id);
        for(edgeT *temp2 = temp->edgesList;temp2 != NULL;temp2 = temp2->nextEdge)
            fprintf(stdout,"%d ",temp2->destination->id);
    }
}
int countVertices(vertexT *graph){
    int counter = 0;
    for(vertexT *temp = graph;temp != NULL;temp = temp->nextVertex)
        counter++;
    return counter;
}
void findHamiltonianCycleWrapper(vertexT *destination,int numberOfVertices){
    queueT *head = NULL;
    queueT *tail = NULL;
    if(findHamiltonianCycle(destination,destination,numberOfVertices,&head,&tail) == 1)
        printQueue(head);
    else
        fprintf(stdout,"\nNo hamiltonian cycle found!\n");
}
int findHamiltonianCycle(vertexT *currentVertex,vertexT *destination,int verticesRemaining,queueT **head,queueT **tail){
    if(currentVertex == destination && verticesRemaining == 0)
        return 1;
    for(edgeT *temp = currentVertex->edgesList;temp != NULL;temp = temp->nextEdge){
        if(temp->destination->color == WHITE){
            temp->destination->color = GREY;
            if(findHamiltonianCycle(temp->destination,destination,verticesRemaining-1,head,tail) == 1){
                enqueue(head,tail,temp->destination->id);
                return 1;
            }
            temp->destination->color = WHITE;
        }
    }
    return 0;
}

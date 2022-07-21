#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphPublic.h"
#include "queuePublic.h"
void graphGenerator(int *numberOfEdges){
    srand(time(0));
    *numberOfEdges = 10 + rand()%11;
    FILE *f = fopen("graph.txt","w");
    for(int i=0;i<*numberOfEdges;i++)
        fprintf(f,"%d %d\n",rand()%10,rand()%10);
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
vertexT *createVertex(int vertexId){
    vertexT *newVertex = (vertexT *) malloc(sizeof(vertexT));
    newVertex->id = vertexId;
    newVertex->edgesList = NULL;
    newVertex->nextVertex = NULL;
    return newVertex;
}
edgeT *createEdge(vertexT *destination){
    edgeT *newEdge = (edgeT *) malloc(sizeof(edgeT));
    newEdge->destination = destination;
    newEdge->color = WHITE;
    newEdge->nextEdge = NULL;
    return newEdge;
}
vertexT *findVertex(vertexT *graph,int vertexId){
    for(vertexT *temp = graph;temp != NULL;temp = temp->nextVertex){
        if(temp->id == vertexId)
            return temp;
    }
    return NULL;
}
edgeT *findEdge(vertexT *graph,int sourceId,int destinationId){
    for(vertexT *temp = graph;temp != NULL;temp = temp->nextVertex){
        for(edgeT *temp2 = temp->edgesList;temp2 != NULL;temp2 = temp2->nextEdge){
            if(temp->id == sourceId && temp2->destination->id == destinationId)
                return temp2;
        }
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
void colorEdge(vertexT *graph,int sourceId,int destinationId,int color){
    for(vertexT *temp = graph;temp != NULL;temp = temp->nextVertex){
        if(temp->id == sourceId){
            for(edgeT *temp2 = temp->edgesList;temp2 != NULL;temp2 = temp2->nextEdge){
                if(temp2->destination->id == destinationId){
                    /*if(color == GREY)
                        fprintf(stdout,"\nEdge [%d %d] colored!",sourceId,destinationId);
                    else
                        fprintf(stdout,"\nEdge [%d %d] blanked!",sourceId,destinationId);
                    */temp2->color = color;
                }
            }
        }
    }
    for(vertexT *temp = graph;temp != NULL;temp = temp->nextVertex){
        if(temp->id == destinationId){
            for(edgeT *temp2 = temp->edgesList;temp2 != NULL;temp2 = temp2->nextEdge){
                if(temp2->destination->id == sourceId){
                    /*if(color == GREY)
                        fprintf(stdout,"\nEdge [%d %d] colored!\n------------------",destinationId,sourceId);
                    else
                        fprintf(stdout,"\nEdge [%d %d] blanked!\n------------------",destinationId,sourceId);
                    */temp2->color = color;
                }
            }
        }
    }
}
void findEurelianCycleWrapper(vertexT *graph,char id1,char id2,int numberOfEdges){
    edgeT *destinationEdge = findEdge(graph,id1,id2);
    colorEdge(graph,id1,id2,GREY);
    queueT *head = NULL;
    queueT *tail = head;
    if(findEurelianCycle(graph,destinationEdge,id1,id2,numberOfEdges-1,&head,&tail) == 1){
        enqueue(&head,&tail,id1,id2);
        printQueue(head);
    }else
        fprintf(stdout,"\nThere is no eulerian path!");
}
int findEurelianCycle(vertexT *graph,edgeT *currentEdge,char id1,char id2,int remainingEdges,queueT **head,queueT **tail){
    if(remainingEdges == 0){
        if((currentEdge->destination->id == id1 || currentEdge->destination->id == id2))
            return 1;
        return 0;
    }
    for(edgeT *temp = currentEdge->destination->edgesList;temp != NULL;temp = temp->nextEdge){
        if(temp->color == WHITE){
            colorEdge(graph,currentEdge->destination->id,temp->destination->id,GREY);
            if(findEurelianCycle(graph,temp,id1,id2,remainingEdges-1,head,tail) == 1){
                enqueue(head,tail,currentEdge->destination->id,temp->destination->id);
                return 1;
            }
            colorEdge(graph,currentEdge->destination->id,temp->destination->id,WHITE);
        }
    }
    return 0;
}

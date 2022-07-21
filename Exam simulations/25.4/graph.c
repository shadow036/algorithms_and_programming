#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphPublic.h"
vertexT *createVertex(char *id){
    vertexT *newVertex = (vertexT *) malloc(sizeof(vertexT));
    strcpy(newVertex->id,id);
    newVertex->status = FREE;
    newVertex->edges = NULL;
    newVertex->nextVertex = NULL;
    return newVertex;
}
edgeT *createEdge(vertexT *destination){
    edgeT *newEdge = (edgeT *) malloc(sizeof(edgeT));
    newEdge->destination = destination;
    newEdge->nextEdge = NULL;
    return newEdge;
}
vertexT *createGraph(FILE *f){
    vertexT *graph = NULL;
    char sourceId[ID];
    char destinationId[ID];
    while(fscanf(f,"%s %s",sourceId,destinationId) != EOF){
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
        newEdge->nextEdge = sourceVertex->edges;
        sourceVertex->edges = newEdge;
        edgeT *newEdge2 = createEdge(sourceVertex);
        newEdge2->nextEdge = destinationVertex->edges;
        destinationVertex->edges = newEdge2;
    }
    return graph;
}
vertexT *findVertex(vertexT *graph,char *id){
    vertexT *temp = graph;
    while(temp != NULL){
        if(!strcmp(temp->id,id))
            return temp;
        temp = temp->nextVertex;
    }
    return NULL;
}
void printGraph(vertexT *graph){
    vertexT *temp = graph;
    while(temp != NULL){
        fprintf(stdout,"\n%s => ",temp->id);
        edgeT *temp2 = temp->edges;
        while(temp2 != NULL){
            fprintf(stdout,"%s -> ",temp2->destination->id);
            temp2 = temp2->nextEdge;
        }
        fprintf(stdout,"NULL");
        temp = temp->nextVertex;
    }
}
edgeT *createSet(vertexT *graph,FILE *f){
    edgeT *set = NULL;
    char vertexId[ID];
    while(fscanf(f,"%s",vertexId) != EOF){
        edgeT *vertex = createEdge(findVertex(graph,vertexId));
        vertex->nextEdge = set;
        set = vertex;
    }
    return set;
}

int verifyIndipendence(edgeT *set){
    for(edgeT *temp = set;temp != NULL;temp = temp->nextEdge){
        for(edgeT *temp2 = temp->destination->edges;temp2 != NULL;temp2 = temp2->nextEdge){
            for(edgeT *temp3 = set;temp3 != NULL;temp3 = temp3->nextEdge){
                if(temp != temp3 && !strcmp(temp2->destination->id,temp3->destination->id))
                    return 0;
            }
        }
    }
    return 1;
}
void findMaximumIndipendentSetWrapper(vertexT *graph){
    for(int i=countVertices(graph);i>=0;i--){
        edgeT *list = NULL;
        if(findMaximumIndipendentSet(graph,0,i,&list) == 1){
            int counter = 0;
            FILE *f = fopen("output.txt","w");
            for(edgeT *temp = list;temp != NULL;temp = temp->nextEdge){
                fprintf(f,"%s\n",temp->destination->id);
                counter++;
            }
            fclose(f);
            fprintf(stdout,"%d\n",counter);
            return;
        }
    }
}
int findMaximumIndipendentSet(vertexT *graph,int k,int n,edgeT **list){
    if(k >= n){
        if(verifyIndipendence(*list) == 1)
            return 1;
        return 0;
    }
    for(vertexT *temp = graph;temp != NULL;temp = temp->nextVertex){
        if(temp->status == FREE){
            temp->status = TAKEN;
            edgeT *newEdge = createEdge(temp);
            newEdge->nextEdge = *list;
            *list = newEdge;
            if(findMaximumIndipendentSet(graph,k+1,n,list) == 1)
                return 1;
            edgeT *temp2 = *list;
            *list = (*list)->nextEdge;
            free(temp2);
            temp->status = FREE;
        }
    }
    return 0;
}
int countVertices(vertexT *graph){
    int counter = 0;
    for(vertexT *temp = graph;temp != NULL;temp = temp->nextVertex)
        counter++;
    return counter;
}

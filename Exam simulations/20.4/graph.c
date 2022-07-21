#include "graph.h"
#include "queue.h"
vertexT *loadGraph(FILE *f){
    vertexT *verticesList = NULL;
    char sourceId[LENGTH];
    char destinationId[LENGTH];
    int adjacentVertices;
    while(fscanf(f,"%s %d",sourceId,&adjacentVertices) != EOF){
        vertexT *sourceVertex = vertexIsAlreadyPresent(verticesList,sourceId);
        if(sourceVertex == NULL){
            sourceVertex = createVertex(sourceId);
            sourceVertex->nextVertex = verticesList;
            verticesList = sourceVertex;
        }
        for(int i=0;i<adjacentVertices;i++){
            fscanf(f,"%s",destinationId);
            vertexT *destinationVertex = vertexIsAlreadyPresent(verticesList,destinationId);
            if(destinationVertex == NULL){
                destinationVertex = createVertex(destinationId);
                destinationVertex->nextVertex = verticesList;
                verticesList = destinationVertex;
            }
            edgeT *newEdge = createEdge(destinationVertex);
            newEdge->nextEdge = sourceVertex->edgesList;
            sourceVertex->edgesList = newEdge;
        }
    }
    return verticesList;
}
vertexT *createVertex(char *id){
    vertexT *newVertex = (vertexT *) malloc(sizeof(vertexT));
    strcpy(newVertex->id,id);
    newVertex->color = WHITE;
    newVertex->edgesList = NULL;
    newVertex->nextVertex = NULL;
    return newVertex;
}
edgeT *createEdge(vertexT *destinationVertex){
    edgeT *newEdge = (edgeT *) malloc(sizeof(edgeT));
    newEdge->destinationVertex = destinationVertex;
    newEdge->nextEdge = NULL;
    return newEdge;
}
vertexT *vertexIsAlreadyPresent(vertexT *verticesList,char *id){
    vertexT *temp = verticesList;
    while(temp != NULL){
        if(!strcmp(temp->id,id))
            return temp;
        temp = temp->nextVertex;
    }
    return NULL;
}
edgeT *edgeIsAlreadyPresent(edgeT *edgesList,char *id){ //CAN ALSO RETURN 0 IF NOT FOUND AND 1 IF FOUND
    edgeT *temp = edgesList;
    while(temp != NULL){
        if(!strcmp(temp->destinationVertex->id,id))
            return temp;
        temp = temp->nextEdge;
    }
    return NULL;
}
void printGraph(vertexT *verticesList){
    vertexT *temp = verticesList;
    while(temp != NULL){
        fprintf(stdout,"\n%s => ",temp->id);
        edgeT *temp2 = temp->edgesList;
        while(temp2 != NULL){
            fprintf(stdout,"%s -> ",temp2->destinationVertex->id);
            temp2 = temp2->nextEdge;
        }
        fprintf(stdout,"NULL");
        temp = temp->nextVertex;
    }
}
void bfsWrapper(vertexT *verticesList){
    vertexT *temp = verticesList;
    while(temp != NULL){
        bfs(temp);
        clearColors(verticesList);
        temp = temp->nextVertex;
    }
}
void bfs(vertexT *source){
    elementT *head = NULL;
    elementT *tail = NULL;
    source->color = GREY;
    enqueue(&head,&tail,source);
    while(head != NULL){
        vertexT *temp = dequeue(&head,&tail);
        edgeT *temp2 = temp->edgesList;
        while(temp2 != NULL){
            if(temp2->destinationVertex->color == WHITE){
                enqueue(&head,&tail,temp2->destinationVertex);
                temp2->destinationVertex->color = GREY;
            }
            temp2 = temp2->nextEdge;
        }
        temp->color = BLACK;
        if(temp != source && edgeIsAlreadyPresent(source->edgesList,temp->id) == NULL){
            edgeT *newEdge = createEdge(temp);
            newEdge->nextEdge = source->edgesList;
            source->edgesList = newEdge;
        }
    }
}
void clearColors(vertexT *verticesList){
    vertexT *temp = verticesList;
    while(temp != NULL){
        temp->color = WHITE;
        temp = temp->nextVertex;
    }
}
void printVertex(vertexT *target){
    edgeT *edges = target->edgesList;
    while(edges != NULL){
        fprintf(stdout,"%s ",edges->destinationVertex->id);
        edges = edges->nextEdge;
    }
}

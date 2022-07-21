#include "graphPublic.h"
#include "stackPublic.h"
#define COLOR 5+1
vertexT *createVertex(char *id,int color){
    vertexT *newVertex = (vertexT *) malloc(sizeof(vertexT));
    strcpy(newVertex->id,id);
    newVertex->color = color;
    newVertex->visited = 0;
    newVertex->edges = NULL;
    newVertex->nextVertex = NULL;
    return newVertex;
}
edgeT *createEdge(vertexT *destination,int weight){
    edgeT *newEdge = (edgeT *) malloc(sizeof(edgeT));
    newEdge->destination = destination;
    newEdge->weight = weight;
    newEdge->nextEdge = NULL;
    return newEdge;
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
vertexT *createGraph(FILE *f){
    vertexT *graph = NULL;
    char sourceId[ID];
    char sourceColor[COLOR];
    int weight;
    char destinationId[ID];
    char destinationColor[COLOR];
    while(fscanf(f,"%s %s %d %s %s",sourceId,sourceColor,&weight,destinationId,destinationColor) != EOF){
        vertexT *sourceVertex = findVertex(graph,sourceId);
        vertexT *destinationVertex = findVertex(graph,destinationId);
        if(sourceVertex == NULL){
            if(!strcmp(sourceColor,"RED"))
                sourceVertex = createVertex(sourceId,RED);
            else
                sourceVertex = createVertex(sourceId,BLACK);
            sourceVertex->nextVertex = graph;
            graph = sourceVertex;
        }
        if(destinationVertex == NULL){
            if(!strcmp(destinationColor,"RED"))
                destinationVertex = createVertex(destinationId,RED);
            else
                destinationVertex = createVertex(destinationId,BLACK);
            destinationVertex->nextVertex = graph;
            graph = destinationVertex;
        }
        edgeT *newEdge = createEdge(destinationVertex,weight);
        newEdge->nextEdge = sourceVertex->edges;
        sourceVertex->edges = newEdge;
        edgeT *newEdge2 = createEdge(sourceVertex,weight);
        newEdge2->nextEdge = destinationVertex->edges;
        destinationVertex->edges = newEdge2;
    }
    return graph;
}
void findPathWrapper(vertexT *graph){
    vertexT *temp = graph;
    int maxLength = 0;
    nodeT *bestPath = NULL;
    while(temp != NULL){
        nodeT *currentPath = NULL;
        int currentLength = 0;
        push(&currentPath,temp->id);
        findPath(graph,temp,currentPath,currentLength,&bestPath,&maxLength);
        temp = temp->nextVertex;
        clearVertices(graph);
    }
    printStack(bestPath);
}
void findPath(vertexT *graph,vertexT *currentVertex,nodeT *currentPath,int currentLength,nodeT **bestPath,int *maxLength){
    currentVertex->visited = 1;
    edgeT *temp = currentVertex->edges;
    while(temp != NULL){
        if(temp->destination->visited == 0 && currentVertex->color == RED && temp->destination->color == BLACK){
            push(&currentPath,temp->destination->id);
            findPath(graph,temp->destination,currentPath,currentLength+temp->weight,bestPath,maxLength);
            temp->destination->visited = 0;
            pop(&currentPath);
        }else if(temp->destination->visited == 0 && currentVertex->color == BLACK){
            push(&currentPath,temp->destination->id);
            findPath(graph,temp->destination,currentPath,currentLength+temp->weight,bestPath,maxLength);
            temp->destination->visited = 0;
            pop(&currentPath);
        }
        temp = temp->nextEdge;
    }
    if(currentLength > *maxLength){
        *maxLength = currentLength;
        *bestPath = copyStack(currentPath);
    }
}
void findPathWrapper2(vertexT *graph){
    vertexT *temp = graph;
    int maxLength = 0;
    nodeT *bestPath = NULL;
    while(temp != NULL){
        nodeT *currentPath = NULL;
        int currentLength = 0;
        push(&currentPath,temp->id);
        if(temp->color == RED)
            findPath2(graph,temp,currentPath,currentLength,&bestPath,&maxLength,1,0);
        else
            findPath2(graph,temp,currentPath,currentLength,&bestPath,&maxLength,0,1);
        temp = temp->nextVertex;
        clearVertices(graph);
    }
    printStack(bestPath);
}
void findPath2(vertexT *graph,vertexT *currentVertex,nodeT *currentPath,int currentLength,nodeT **bestPath,int *maxLength,int redCounter,int blackCounter){
    currentVertex->visited = 1;
    edgeT *temp = currentVertex->edges;
    while(temp != NULL){
        if(temp->destination->visited == 0){
            push(&currentPath,temp->destination->id);
            if(temp->destination->color == RED)
                findPath2(graph,temp->destination,currentPath,currentLength+temp->weight,bestPath,maxLength,redCounter+1,blackCounter);
            else
                findPath2(graph,temp->destination,currentPath,currentLength+temp->weight,bestPath,maxLength,redCounter,blackCounter+1);
            temp->destination->visited = 0;
            pop(&currentPath);
        }
        temp = temp->nextEdge;
    }
    if(currentLength > *maxLength && abs(blackCounter-redCounter) >= 2){
        *maxLength = currentLength;
        *bestPath = copyStack(currentPath);
    }
}
void printGraph(vertexT *graph){
    vertexT *temp = graph;
    while(temp != NULL){
        if(temp->color == 0)
            fprintf(stdout,"\n%s (color: RED) => ",temp->id);
        else
            fprintf(stdout,"\n%s (color: BLACK) => ",temp->id);
        edgeT *temp2 = temp->edges;
        while(temp2 != NULL){
            if(temp2->destination->color == 0)
                fprintf(stdout,"%s (color: RED, weight: %d) -> ",temp2->destination->id,temp2->weight);
            else
                fprintf(stdout,"%s (color: BLACK, weight: %d) -> ",temp2->destination->id,temp2->weight);
            temp2 = temp2->nextEdge;
        }
        fprintf(stdout,"NULL");
        temp = temp->nextVertex;
    }
}
void clearVertices(vertexT *graph){
    vertexT *temp = graph;
    while(temp != NULL){
        temp->visited = 0;
        temp = temp->nextVertex;
    }
}
nodeT *copyStack(nodeT *stack){
    nodeT *newStack = NULL;
    nodeT *temp = stack;
    while(temp != NULL){
        push(&newStack,temp->id);
        temp = temp->nextNode;
    }
    return newStack;
}

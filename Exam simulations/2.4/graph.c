#include "graphPublic.h"
#include "stack.h"
vertexT *createGraph(FILE *f){
    vertexT *graph = NULL;
    char sourceId[ID];
    int weight;
    char destinationId[ID];
    while(fscanf(f,"%s %d %s",sourceId,&weight,destinationId) != EOF){
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
        edgeT *newEdge = createEdge(destinationVertex,weight);
        newEdge->nextEdge = sourceVertex->edges;
        sourceVertex->edges = newEdge;
        sourceVertex->outDegree++;
        destinationVertex->inDegree++;
    }
    return graph;
}
vertexT *createVertex(char *id){
    vertexT *newVertex = (vertexT *) malloc(sizeof(vertexT));
    strcpy(newVertex->id,id);
    newVertex->inDegree = 0;
    newVertex->outDegree = 0;
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
void printGraph(vertexT *graph){
    vertexT *temp = graph;
    while(temp != NULL){
        fprintf(stdout,"\n%s (in-degree: %d, out-degree: %d) => ",temp->id,temp->inDegree,temp->outDegree);
        edgeT *temp2 = temp->edges;
        while(temp2 != NULL){
            fprintf(stdout,"%s (weight: %d) -> ",temp2->destination->id,temp2->weight);
            temp2 = temp2->nextEdge;
        }
        fprintf(stdout,"NULL");
        temp = temp->nextVertex;
    }
}
void regularityCheck(vertexT *graph){
    int n = -1;
    vertexT *temp = graph;
    while(temp != NULL){
        if(n == -1){
            n = temp->inDegree;
        }else if(temp->inDegree != n){
            fprintf(stdout,"\n\nThe graph IS NOT regular!\n");
            return;
        }
        if(temp->outDegree != n){
            fprintf(stdout,"\n\nThe graph IS NOT regular!\n");
            return;
        }
        temp = temp->nextVertex;
    }
    fprintf(stdout,"\n\nThe graph IS regular!\n");
    return;
}
void findPathWrapper(vertexT *graph){
    char initialVertexId[ID];
    while(strcmp(initialVertexId,"end")){
        fprintf(stdout,"\nChoose initial vertex => ");
        fscanf(stdin,"%s",initialVertexId);
        vertexT *initialVertex = findVertex(graph,initialVertexId);
        edgeT *bestSolution = NULL;
        edgeT *currentSolution = NULL;
        int maxLength = 0;
        int currentLength = 0;
        if(initialVertex != NULL){
            findPath(graph,initialVertex,&currentSolution,currentLength,&bestSolution,&maxLength);
            edgeT *temp = bestSolution;
            fprintf(stdout,"%s -> ",initialVertexId);
            while(temp != NULL){
                fprintf(stdout,"%s -> ",temp->destination->id);
                temp = temp->nextEdge;
            }
            fprintf(stdout,"NULL\n");
            temp = bestSolution;
            while(temp != NULL){
                fprintf(stdout,"%d -> ",temp->weight);
                temp = temp->nextEdge;
            }
            fprintf(stdout,"NULL\n");
            fprintf(stdout,"Total weight: %d\n",maxLength);
            clear(graph);
        }
    }
}
void findPath(vertexT *graph,vertexT *currentVertex,edgeT **currentSolution,int currentLength,edgeT **bestSolution,int *maxLength){
    currentVertex->visited = 1;
    edgeT *temp = currentVertex->edges;
    while(temp != NULL){
        if(temp->destination->visited == 0){
            push(currentSolution,createEdge(temp->destination,temp->weight));   //CAN ALSO CREATE ANOTHER STRUCTURE FOR SOLUTION NODES "WRAPPING" THE EDGE STRUCTURE
            findPath(graph,temp->destination,currentSolution,currentLength+temp->weight,bestSolution,maxLength);
            temp->destination->visited = 0;
            pop(currentSolution);
        }
        temp = temp->nextEdge;
    }
    if(currentLength > *maxLength){
        *maxLength = currentLength;
        *bestSolution = copyStack(*currentSolution);
    }
}
edgeT *copyStack(edgeT *currentSolution){
    edgeT *bestSolution = NULL;
    edgeT *temp = currentSolution;
    while(temp != NULL){
        push(&bestSolution,createEdge(temp->destination,temp->weight));
        temp = temp->nextEdge;
    }
    return bestSolution;
}
void clear(vertexT *graph){
    vertexT *temp = graph;
    while(temp != NULL){
        temp->visited = 0;
        temp = temp->nextVertex;
    }
}

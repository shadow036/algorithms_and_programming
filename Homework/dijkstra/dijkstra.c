#include "dijkstra.h"
void generateGraph(){
    FILE *f = fopen("graph.txt","w");
    for(int i=0;i<100;i++)
        fprintf(f,"%c %d %c",65+rand()%26,rand()%10,65+rand()%26);
    fclose(f);
}
vertexT *loadGraph(dataT *priorityQueue){
    vertexT *graph = NULL;
    FILE *f = fopen("graph.txt","r");
    char id,id2;
    int weight;
    while(fscanf(f,"%c %d %c",&id,&weight,&id2) != EOF){
        vertexT *sourceVertex;
        vertexT *destinationVertex;
        if(isPresent(graph,id) == NULL){
            sourceVertex = createVertex(id);
            sourceVertex->next = graph;
            graph = sourceVertex;
        }else{
            sourceVertex = isPresent(graph,id);
        }
        if(isPresent(graph,id2) == NULL){
            destinationVertex = createVertex(id2);
            destinationVertex->next = graph;
            graph = destinationVertex;
        }else{
            destinationVertex = isPresent(graph,id2);
        }
        edgeT *newEdge = createEdge(weight,destinationVertex);
        newEdge->next = sourceVertex->edges;
        sourceVertex->edges = newEdge;
    }
    vertexT *temp = graph;
    while(temp != NULL){

        temp = temp->next;
    }
    return graph;
}
vertexT *isPresent(vertexT *graph,char id){
    vertexT *temp = graph;
    while(temp != NULL){
        if(temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
vertexT *createVertex(char id){
    vertexT *newVertex = (vertexT *) malloc(sizeof(vertexT));
    newVertex->id = id;
    newVertex->color = WHITE;
    newVertex->dist = MAX;
    newVertex->pred = NULL;
    newVertex->edges = NULL;
    newVertex->next = NULL;
    return newVertex;
}
edgeT *createEdge(int weight,vertexT *destination){
    edgeT *newEdge = (edgeT *) malloc(sizeof(edgeT));
    newEdge->weight = weight;
    newEdge->destination = destination;
    return newEdge;
}

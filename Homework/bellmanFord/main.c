#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#define ID 10
#define MAX 1000
typedef struct vertexS vertexT;
typedef struct edgeS edgeT;
typedef struct nodeS nodeT;
//VERTEX STRUCTURE
struct vertexS{
    char *id;
    edgeT *edges;
    vertexT *predecessor;
    int distance;
    vertexT *next;
};
//EDGE STRUCTURE
struct edgeS{
    int weight;
    vertexT *destination;
    edgeT *next;
};
void randomGraphGenerator();
vertexT *loadGraph();
vertexT *search(vertexT *,char *);
vertexT *createVertex(vertexT **,char *);
void createEdge(vertexT *,vertexT *,int);
void printGraph(vertexT *);
int bellmanFord(vertexT *);
int main(){
    randomGraphGenerator();
    vertexT *graph = loadGraph();
    printGraph(graph);
    if(bellmanFord(graph) == 1){
        fprintf(stdout,"\nSHORTEST PATHS FROM NODE %s",graph->id);
        while(graph != NULL){
            if(graph->distance != MAX){
                fprintf(stdout,"\nnode %s, distance %d, predecessor ",graph->id,graph->distance);
                if(graph->predecessor != NULL)
                    fprintf(stdout,"%s",graph->predecessor->id);
                else
                    fprintf(stdout,"NULL",graph->id,graph->distance);
            }else{
                fprintf(stdout,"\nnode %s, distance INFINITY, predecessor NULL",graph->id);
            }
            graph = graph->next;
        }
        fprintf(stdout,"\n");
    }else{
        fprintf(stdout,"\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
    }
    return 0;
}
void randomGraphGenerator(){
    srand(time(0));
    FILE *f = fopen("graph.txt","w");
    for(int i=0;i<100;i++)
        fprintf(f,"%c %d %c\n",65+rand()%26,rand()%10,65+rand()%26);
    fclose(f);
}
vertexT *loadGraph(){
    vertexT *graph = NULL;
    FILE *f = fopen("graph.txt","r");
    char sourceId[ID];
    int weight;
    char destinationId[ID];
    while(fscanf(f,"%s %d %s",sourceId,&weight,destinationId) != EOF){
        vertexT *sourceVertex = NULL;
        vertexT *destinationVertex = NULL;
        if(search(graph,sourceId) == NULL){
            sourceVertex = createVertex(&graph,sourceId);
        }else{
            sourceVertex = search(graph,sourceId);
        }
        if(search(graph,destinationId) == NULL){
            destinationVertex = createVertex(&graph,destinationId);
        }else{
            destinationVertex = search(graph,destinationId);
        }
       createEdge(sourceVertex,destinationVertex,weight);
    }
    fclose(f);
    return graph;
}
vertexT *createVertex(vertexT **graph,char *id){
    vertexT *newVertex = (vertexT *) malloc(sizeof(vertexT));
    newVertex->id = (char *) malloc((strlen(id)+1) * sizeof(char));
    strcpy(newVertex->id,id);
    newVertex->edges = NULL;
    newVertex->next = *graph;
    *graph = newVertex;
    return newVertex;
}
void createEdge(vertexT *sourceVertex,vertexT *destinationVertex,int weight){
    edgeT *newEdge = (edgeT *) malloc(sizeof(edgeT));
    newEdge->destination = destinationVertex;
    newEdge->weight = weight;
    newEdge->next = sourceVertex->edges;
    sourceVertex->edges = newEdge;
}
vertexT *search(vertexT *vertices,char *id){
    vertexT *temp = vertices;
    while(temp != NULL){
        if(strcmp(temp->id,id) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
void printGraph(vertexT *graph){
    vertexT *temp = graph;
    while(temp != NULL){
        fprintf(stdout,"%s",temp->id);
        edgeT *temp2 = temp->edges;
        while(temp2 != NULL){
            fprintf(stdout,"\n  weight: %d, destination: %s",temp2->weight,temp2->destination->id);
            temp2 = temp2->next;
        }
        fprintf(stdout,"\n");
        temp = temp->next;
    }
}
int bellmanFord(vertexT *graph){
    int counter = 0;
    //INITIALIZATION PHASE
    vertexT *temp = graph;
    while(temp != NULL){
        counter++;
        temp->distance = MAX;
        temp->predecessor = NULL;
        temp = temp->next;
    }
    graph->distance = 0;
    for(int i=0;i<counter-1;i++){
        temp = graph;
        while(temp != NULL){
            edgeT *temp2 = temp->edges;
            while(temp2 != NULL){
                //RELAX PHASE
                if(temp2->destination->distance > temp->distance+temp2->weight){
                    temp2->destination->distance = temp->distance+temp2->weight;
                    temp2->destination->predecessor = temp;
                }
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
    }
    temp = graph;
    while(temp != NULL){
        edgeT *temp2 = temp->edges;
        while(temp2 != NULL){
            if(temp2->destination->distance > temp->distance+temp2->weight)
                return 0;
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    return 1;
}

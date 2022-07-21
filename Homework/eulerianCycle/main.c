#include <stdio.h>
#include <stdlib.h>
#include "graphPublic.h"
int main(){
    int numberOfEdges = 8;
    //graphGenerator(&numberOfEdges);
    graphT *graph = (graphT *) malloc(sizeof(graphT));
    graph->graph = createGraph(fopen("graph.txt","r"));
    graph->numberOfEdges = numberOfEdges;
    printGraph(graph->graph);
    int sourceId,destinationId;
    fprintf(stdout,"\n\nInsert starting edge (sourceId destinationId) => ");
    fscanf(stdin,"%d %d",&sourceId,&destinationId);
    findEurelianCycleWrapper(graph->graph,sourceId,destinationId,numberOfEdges);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "graphPublic.h"
int main()
{
    //graphGenerator();
    graphT *graph = (graphT *) malloc(sizeof(graphT));
    graph->graph = createGraph(fopen("graph.txt","r"));
    graph->numberOfVertices = countVertices(graph->graph);
    printGraph(graph->graph);
    int initialVertexId;
    fprintf(stdout,"\nSelect initial vertex => ");
    fscanf(stdin,"%d",&initialVertexId);
    vertexT *initialVertex = findVertex(graph->graph,initialVertexId);
    if(initialVertex != NULL)
        findHamiltonianCycleWrapper(initialVertex,graph->numberOfVertices);
    return 0;
}

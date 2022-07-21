#include <stdio.h>
#include <stdlib.h>
#include "graphPublic.h"
#include "bfsPowerSet.h"
int main()
{
    int numberOfEdges;
    generateGraph(&numberOfEdges);
    vertexT *graph = createGraph(fopen("graph.txt","r"));
    printGraph(graph);
    fprintf(stdout,"\n");
    int minNumberOfEdgesToBeRemoved = powerSetWrapper(graph,numberOfEdges);
    fprintf(stdout,"\nMinimum number of edges to be removed in order to make the graph disconnected: %d",minNumberOfEdgesToBeRemoved);
    return 0;
}

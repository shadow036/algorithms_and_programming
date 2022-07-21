#include <stdio.h>
#include <stdlib.h>
#include "graphPublic.h"
int main()
{
    generateGraph();
    vertexT *graph = createGraph(fopen("graph.txt","r"));
    printGraph(graph);
    char startingVertexId;
    fprintf(stdout,"\n\nInsert initial vertex => ");
    fscanf(stdin,"%c",&startingVertexId);
    bfs(graph,findVertex(graph,startingVertexId));
    fprintf(stdout,"\n\n");
    clear(graph);
    dfs(findVertex(graph,startingVertexId),-1);
    fprintf(stdout,"\n");
    return 0;
}

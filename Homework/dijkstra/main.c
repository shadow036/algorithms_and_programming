#include <stdio.h>
#include <stdlib.h>
#include "priorityQueue.h"
#include "dijkstra.h"
int main()
{
    dataT *priorityQueue = NULL;
    generateGraph();
    vertexT *graph = loadGraph(priorityQueue);

    return 0;
}

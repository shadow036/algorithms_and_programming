#include "graphPublic.h"
int main()
{
    vertexT *graph = createGraph(fopen("graph.txt","r"));
    printGraph(graph);
    regularityCheck(graph);
    findPathWrapper(graph);
    return 0;
}

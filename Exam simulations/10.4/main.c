#include "graphPublic.h"
int main()
{
    vertexT *graph = createGraph(fopen("graph.txt","r"));
    printGraph(graph);
    findPathWrapper(graph);
    findPathWrapper2(graph);
}

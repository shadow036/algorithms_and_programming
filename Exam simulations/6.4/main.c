#include "graphPublic.h"
#include "stackPublic.h"
int main()
{
    FILE *f = fopen("graph.txt","r");
    vertexT *graph = createGraph(f);
    char sourceId[ID];
    char destinationId[ID];
    fprintf(stdout,"sourceId destinationId => ");
    fscanf(stdin,"%s %s",sourceId,destinationId);
    vertexT *sourceVertex = findVertex(graph,sourceId);
    vertexT *destinationVertex = findVertex(graph,destinationId);
    sourceVertex->numberOfTimesVisited = 1;
    nodeT *bos = NULL;
    nodeT *tos = NULL;
    nodeT *bestPath = NULL;
    int maxLength = -1;
    int maxNumberVisited,maxRepetitions;
    push(&bos,&tos,sourceVertex->id);
    fprintf(stdout,"maxNumberVisited maxNodesVisitedMoreThanOnce => ");
    fscanf(stdin,"%d %d",&maxNumberVisited,&maxRepetitions);
    findPath(graph,sourceVertex,destinationVertex,&bos,&tos,0,&bestPath,&maxLength,maxNumberVisited,0,maxRepetitions);
    printPath(bestPath);
    fprintf(stdout,"\nLength: %d\n",maxLength);
    return 0;
}

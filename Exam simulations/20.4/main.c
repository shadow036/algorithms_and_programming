#include "graph.h"
int main()
{
    vertexT *verticesList = loadGraph(fopen("graph.txt","r"));
    printGraph(verticesList);
    char vertexId[LENGTH];
    do{
        fprintf(stdout,"\n\nVertex: ");
        fscanf(stdin,"%s",vertexId);
        vertexT *target = vertexIsAlreadyPresent(verticesList,vertexId);
        if(target != NULL){
            bfs(target);
            fprintf(stdout,"Reachable nodes: ");
            printVertex(target);
            clearColors(verticesList);
        }
    }while(strcmp(vertexId,"end"));
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "graphPublic.h"
int main()
{
    FILE *f = fopen("graph.txt","r");
    FILE *f2 = fopen("set.txt","r");
    vertexT *graph = createGraph(f);
    printGraph(graph);
    edgeT *set = createSet(graph,f2);
    if(verifyIndipendence(set))
        fprintf(stdout,"\n\nThe set IS indipendent!\n");
    else
        fprintf(stdout,"\n\nThe set IS NOT indipendent!\n");
    findMaximumIndipendentSetWrapper(graph);
    fclose(f);
    fclose(f2);
    return 0;
}

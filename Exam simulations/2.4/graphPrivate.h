#ifndef GRAPHPRIVATE_H_INCLUDED
#define GRAPHPRIVATE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ID 20+1
typedef struct vertexS vertexT;
typedef struct edgeS edgeT;
struct vertexS{
    char id[ID];
    int inDegree;
    int outDegree;
    int visited;
    edgeT *edges;
    vertexT *nextVertex;
};
struct edgeS{
    vertexT *destination;
    int weight;
    edgeT *nextEdge;
};
#endif // GRAPHPRIVATE_H_INCLUDED

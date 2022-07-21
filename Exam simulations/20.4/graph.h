#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#define LENGTH 100+1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum{WHITE,GREY,BLACK};
typedef struct vertexS vertexT;
typedef struct edgeS edgeT;
struct vertexS{
    char id[LENGTH];
    int color;
    edgeT *edgesList;
    vertexT *nextVertex;
};
struct edgeS{
    vertexT *destinationVertex;
    edgeT *nextEdge;
};
vertexT *loadGraph(FILE *);
vertexT *vertexIsAlreadyPresent(vertexT *,char *);
edgeT *edgeIsAlreadyPresent(edgeT *,char *);
vertexT *createVertex(char *);
edgeT *createEdge(vertexT *);
void bfsWrapper(vertexT *);
void bfs(vertexT *);
void clearColors(vertexT *);
void printGraph(vertexT *);
void printVertex(vertexT *);
#endif // GRAPH_H_INCLUDED

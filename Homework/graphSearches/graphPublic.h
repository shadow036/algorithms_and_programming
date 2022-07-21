#ifndef GRAPHPUBLIC_H_INCLUDED
#define GRAPHPUBLIC_H_INCLUDED
#include "graphPrivate.h"
vertexT *createVertex(char);
edgeT *createEdge(vertexT *);
vertexT *findVertex(vertexT *,char);
vertexT *createGraph(FILE *);
void printGraph(vertexT *);
void generateGraph();
void bfs(vertexT *,vertexT *);
int dfs(vertexT *,int);
void clear(vertexT *);
#endif // GRAPHPUBLIC_H_INCLUDED

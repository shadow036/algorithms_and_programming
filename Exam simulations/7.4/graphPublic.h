#ifndef GRAPHPUBLIC_H_INCLUDED
#define GRAPHPUBLIC_H_INCLUDED
#include "graphPrivate.h"
void generateGraph(int *);
vertexT *createVertex(char);
edgeT *createEdge(vertexT *);
vertexT *createGraph(FILE *);
vertexT *findVertex(vertexT *,char);
void printGraph(vertexT *);
#endif // GRAPHPUBLIC_H_INCLUDED

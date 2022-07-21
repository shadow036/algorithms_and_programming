#ifndef BFSPOWERSET_H_INCLUDED
#define BFSPOWERSET_H_INCLUDED
#include "graphPrivate.h"
void bfs(vertexT *);
int powerSetWrapper(vertexT *,int);
void powerSet(vertexT *,int,int,int,int *);
int checkDisconnections(vertexT *);
void clearColors(vertexT *);
void clearDisconnections(vertexT *);
void disconnectEdge(vertexT *,vertexT *);
void connectEdge(vertexT *,vertexT *);
#endif // BFSPOWERSET_H_INCLUDED

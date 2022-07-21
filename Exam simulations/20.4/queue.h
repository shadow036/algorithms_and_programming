#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "graph.h"
typedef struct elementS elementT;
struct elementS{
    vertexT *vertex;
    elementT *nextElement;
};
void enqueue(elementT **,elementT **,vertexT *);
vertexT *dequeue(elementT **,elementT **);
elementT *createElement(vertexT *);
#endif // QUEUE_H_INCLUDED

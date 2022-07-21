#ifndef QUEUEPUBLIC_H_INCLUDED
#define QUEUEPUBLIC_H_INCLUDED
#include "queuePrivate.h"
void enqueue(elementT **,elementT **,elementT *);
elementT *dequeue(elementT **,elementT **);
elementT *createElement(vertexT *);

#endif // QUEUEPUBLIC_H_INCLUDED

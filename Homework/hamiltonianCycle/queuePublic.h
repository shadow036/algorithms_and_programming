#ifndef QUEUEPUBLIC_H_INCLUDED
#define QUEUEPUBLIC_H_INCLUDED
#include "queuePrivate.h"
queueT *createQueueElement(int);
void enqueue(queueT **,queueT **,int);
queueT *dequeue(queueT **,queueT **);
void printQueue(queueT *);
#endif // QUEUEPUBLIC_H_INCLUDED

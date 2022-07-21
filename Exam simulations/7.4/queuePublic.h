#ifndef QUEUEPUBLIC_H_INCLUDED
#define QUEUEPUBLIC_H_INCLUDED
#include "queuePrivate.h"
void enqueue(elementT **,elementT **,char);
elementT *dequeue(elementT **,elementT **);
elementT *createElement(char);
#endif // QUEUEPUBLIC_H_INCLUDED

#ifndef QUEUEPRIVATE_H_INCLUDED
#define QUEUEPRIVATE_H_INCLUDED
#include "graphPrivate.h"
typedef struct elementS elementT;
struct elementS{
    vertexT *vertex;
    elementT *nextElement;
};


#endif // QUEUEPRIVATE_H_INCLUDED

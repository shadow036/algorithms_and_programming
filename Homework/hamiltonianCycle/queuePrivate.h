#ifndef QUEUEPRIVATE_H_INCLUDED
#define QUEUEPRIVATE_H_INCLUDED
typedef struct queueS queueT;
struct queueS{
    int vertexId;
    queueT *nextQueue;
};


#endif // QUEUEPRIVATE_H_INCLUDED

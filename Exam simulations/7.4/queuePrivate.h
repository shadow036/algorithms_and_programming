#ifndef QUEUEPRIVATE_H_INCLUDED
#define QUEUEPRIVATE_H_INCLUDED
typedef struct elementS elementT;
struct elementS{
    char id;
    elementT *nextElement;
};


#endif // QUEUEPRIVATE_H_INCLUDED

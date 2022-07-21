#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
typedef struct nodeS nodeT;
struct nodeS{
    int key;
    nodeT *left;
    nodeT *right;
};


#endif // TREE_H_INCLUDED

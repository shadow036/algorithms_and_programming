#include "implementation.h"
void levelByLevelVisit(nodeT *root,int lowerBound,int upperBound){
    for(int i=lowerBound;i<=upperBound;i++){
        preOrderVisit(root,0,i);
        fprintf(stdout,"\n");
    }
}
void preOrderVisit(nodeT *root,int currentLevel,int targetLevel){
    if(currentLevel == targetLevel){
        fprintf(stdout,"%d ",root->key);
        return;
    }
    for(int i=0;i<N;i++)
        preOrderVisit(root->child[i],currentLevel+1,targetLevel);
}

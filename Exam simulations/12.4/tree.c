#include "tree.h"
nodeT *loadTree(FILE *f){
    char parentId[ID];
    char childId[ID];
    int numberOfChildren;
    nodeT *root = NULL;
    while(fscanf(f,"%s %d",parentId,&numberOfChildren) != EOF){
        nodeT *parentNode = searchNode(parentId,root);
        if(parentNode == NULL)
            root = parentNode = createNode(parentId);
        parentNode->numberOfChildren = numberOfChildren;
        parentNode->children = (nodeT **) malloc(numberOfChildren * sizeof(nodeT *));
        for(int i=0;i<numberOfChildren;i++){
            fscanf(f,"%s ",childId);
            nodeT *childNode = createNode(childId);
            parentNode->children[i] = childNode;
            childNode->parent = parentNode;
        }
    }
    return root;
}
nodeT *createNode(char *id){
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    strcpy(newNode->id,id);
    newNode->parent = NULL;
    newNode->children = NULL;
    newNode->numberOfChildren = 0;
    return newNode;
}
nodeT *searchNode(char *id,nodeT *root){
    if(root == NULL)
        return NULL;
    if(!strcmp(id,root->id))
        return root;
    for(int i=0;i<root->numberOfChildren;i++){
        nodeT *result = searchNode(id,root->children[i]);
        if(result != NULL)
            return result;
    }
    return NULL;
}
void findMaxDepth(nodeT *root,int *maxDepth,int currentDepth){
    for(int i=0;i<root->numberOfChildren;i++)
        findMaxDepth(root->children[i],maxDepth,currentDepth+1);
    if(currentDepth > *maxDepth)
        *maxDepth = currentDepth;
    return;
}
void visitWrapper(nodeT *root,int maxDepth){
    for(int i=maxDepth;i>=0;i--){
        fprintf(stdout,"Depth %d: ",i);
        visit(root,i,0);
        fprintf(stdout,"\n");
    }
}
void visit(nodeT *root,int targetDepth,int currentDepth){
    if(currentDepth == targetDepth){
        fprintf(stdout,"%s ",root->id);
        return;
    }
    for(int i=0;i<root->numberOfChildren;i++)
        visit(root->children[i],targetDepth,currentDepth+1);
    return;
}
void findLongestID(nodeT *root,elementT *head,elementT **bestPath,int *maxLength){
    if(root->numberOfChildren == 0){
        int currentLength = 0;
        elementT *temp = head;
        while(temp != NULL){
            currentLength += strlen(temp->id);
            temp = temp->next;
        }
        if(currentLength > *maxLength){
            *maxLength = currentLength;
            elementT *temp = head;
            *bestPath = NULL;
            while(temp != NULL){
                addElement(bestPath,temp->id);
                temp = temp->next;
            }
        }
    }else{
        for(int i=0;i<root->numberOfChildren;i++){
            addElement(&head,root->children[i]->id);
            findLongestID(root->children[i],head,bestPath,maxLength);
            removeElement(&head);
        }
    }
}

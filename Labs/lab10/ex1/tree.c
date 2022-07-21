#include "treePublic.h"
nodeT *loadFile(char *filename){
    FILE *f = fopen(filename,"r");
    nodeT *root = NULL;
    int registerNumber;
    char lastName[NAME];
    char firstName[NAME];
    char birthDate[DATE];
    char program[PROGRAM];
    int enrollmentYear;
    while(fscanf(f,"%d %s %s %s %s %d",&registerNumber,lastName,firstName,birthDate,program,&enrollmentYear) != EOF){
        nodeT *newNode = createStudent(registerNumber,lastName,firstName,birthDate,program,enrollmentYear);
        root = insertStudentName(root,newNode);
        insertStudentNumber(root,newNode);
    }
    fclose(f);
    return root;
}
nodeT *createStudent(int registerNumber,char *lastName,char *firstName,char *birthDate,char *program,int enrollmentYear){
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    newNode->registerNumber = registerNumber;
    newNode->lastName = (char *) malloc((strlen(lastName)+1) * sizeof(char));
    strcpy(newNode->lastName,lastName);
    newNode->firstName = (char *) malloc((strlen(firstName)+1) * sizeof(char));
    strcpy(newNode->firstName,firstName);
    strcpy(newNode->birthDate,birthDate);
    strcpy(newNode->program,program);
    newNode->enrollmentYear = enrollmentYear;
    newNode->leftName = NULL;
    newNode->leftNumber = NULL;
    newNode->rightName = NULL;
    newNode->rightNumber = NULL;
    return newNode;
}
nodeT *insertStudentName(nodeT *root,nodeT *newNode){
    if(root == NULL)
        return newNode;
    if(strcmp(newNode->lastName,root->lastName) < 0 || (!strcmp(newNode->lastName,root->lastName) && strcmp(newNode->firstName,root->firstName) < 0))
        root->leftName = insertStudentName(root->leftName,newNode);
    if(strcmp(newNode->lastName,root->lastName) > 0 || (!strcmp(newNode->lastName,root->lastName) && strcmp(newNode->firstName,root->firstName) > 0))
        root->rightName = insertStudentName(root->rightName,newNode);
    return root;
}
nodeT *insertStudentNumber(nodeT *root,nodeT *newNode){
    if(root == NULL)
        return newNode;
    if(newNode->registerNumber < root->registerNumber)
        root->leftNumber = insertStudentNumber(root->leftNumber,newNode);
    if(newNode->registerNumber > root->registerNumber)
        root->rightNumber = insertStudentNumber(root->rightNumber,newNode);
    return root;
}
nodeT *searchName(nodeT *root,char *lastName,char *firstName){
    if(root == NULL || (!strcmp(root->lastName,lastName) && !strcmp(root->firstName,firstName)))
        return root;
    if(strcmp(lastName,root->lastName) < 0 || (!strcmp(lastName,root->lastName) && strcmp(firstName,root->firstName) < 0))
        return searchName(root->leftName,lastName,firstName);
    else
        return searchName(root->rightName,lastName,firstName);
}
nodeT *searchNumber(nodeT *root,int registerNumber){
    if(root == NULL || root->registerNumber == registerNumber)
        return root;
    if(registerNumber < root->registerNumber)
        return searchNumber(root->leftNumber,registerNumber);
    else
        return searchNumber(root->rightNumber,registerNumber);
}
void save(nodeT *root,char *filename){ //WRAPPER
    FILE *f = fopen(filename,"w");
    saveInOrderName(root,f);
    fclose(f);
}
void saveInOrderName(nodeT *root,FILE *f){
    if(root == NULL)
        return;
    saveInOrderName(root->leftNumber,f);
    fprintf(f,"%d %s %s %s %s %d\n",root->registerNumber,root->lastName,root->firstName,root->birthDate,root->program,root->enrollmentYear);
    saveInOrderName(root->rightNumber,f);
}

#include "treePublic.h"
int main()
{
    char command[COMMAND];
    char filename[FILENAME];
    char lastName[NAME];
    char firstName[NAME];
    int registerNumber;
    nodeT *target;
    nodeT *root = NULL;
    do{
        fprintf(stdout,"command => ");
        fscanf(stdin,"%s",command);
        if(!strcmp(command,"load")){
            fscanf(stdin,"%s",filename);
            root = loadFile(filename);
        }else if(!strcmp(command,"searchS")){
            fscanf(stdin,"%s %s",lastName,firstName);
            target = searchName(root,lastName,firstName);
            if(target != NULL)
                fprintf(stdout,"%d %s %s %s %s %d\n",target->registerNumber,target->lastName,target->firstName,target->birthDate,target->program,target->enrollmentYear);
            else
                fprintf(stdout,"Student not found!\n");
        }else if(!strcmp(command,"searchN")){
            fscanf(stdin,"%d",&registerNumber);
            target = searchNumber(root,registerNumber);
            if(target != NULL)
                fprintf(stdout,"%d %s %s %s %s %d\n",target->registerNumber,target->lastName,target->firstName,target->birthDate,target->program,target->enrollmentYear);
            else
                fprintf(stdout,"Student not found!\n");
        }else if(!strcmp(command,"save")){
            fscanf(stdin,"%s",filename);
            save(root,filename);
        }
    }while(strcmp(command,"quit"));
    return 0;
}

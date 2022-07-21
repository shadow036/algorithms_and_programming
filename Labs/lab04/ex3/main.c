#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME 20+1
#define NAME 30+1
#define ANSWER 100+1
typedef struct cyclistS cyclistT;
struct cyclistS{
    char *name;
    int id;
    int numberOfLapsPerformed;
    float *laps;
    float average;
};
cyclistT *loadCyclistsFile(int *);
void list(cyclistT *,int);
void detail(cyclistT *,int);
void best(cyclistT *,int);
int main()
{
    int numberOfCyclists;
    char answer[ANSWER];
    cyclistT *cyclists = loadCyclistsFile(&numberOfCyclists);
    do{
        fprintf(stdout,"\n1.list\n2.detail (name)\n3.best\n4.stop\n=> ");
        fscanf(stdin,"%s",answer);
        if(strcmp(answer,"list") == 0){
            list(cyclists,numberOfCyclists);
        }else if(strcmp(answer,"detail") == 0){
            detail(cyclists,numberOfCyclists);
        }else if(strcmp(answer,"best") == 0){
            best(cyclists,numberOfCyclists);
        }
    }while(strcmp(answer,"stop") != 0);
    return 0;
}
cyclistT *loadCyclistsFile(int *numberOfCyclists){
    char filename[FILENAME];
    fprintf(stdout,"cyclists filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    fscanf(f,"%d",numberOfCyclists);
    cyclistT *cyclists = (cyclistT *) malloc(*numberOfCyclists * sizeof(cyclistT));
    char name[NAME];
    int id;
    int numberOfLapsPerformed;
    for(int i=0;i<*numberOfCyclists;i++){
        fscanf(f,"%s %d %d",name,&id,&numberOfLapsPerformed);
        cyclists[i].name = strdup(name);
        cyclists[i].id = id;
        cyclists[i].numberOfLapsPerformed = numberOfLapsPerformed;
        cyclists[i].average = 0;
        cyclists[i].laps = (float *) malloc(numberOfLapsPerformed * sizeof(float));
        for(int j=0;j<numberOfLapsPerformed;j++){
            fscanf(f,"%f",&cyclists[i].laps[j]);
            cyclists[i].average += cyclists[i].laps[j];
        }
        cyclists[i].average /= numberOfLapsPerformed;
    }
    return cyclists;
}
void list(cyclistT *cyclists,int numberOfCyclists){
    fprintf(stdout,"\nNumber of cyclists: %d\n",numberOfCyclists);
    for(int i=0;i<numberOfCyclists;i++){
        fprintf(stdout,"\nName: %s\nId: %d\nNumber of laps performed: %d\n",cyclists[i].name,cyclists[i].id,cyclists[i].numberOfLapsPerformed);
    }
}
void detail(cyclistT *cyclists,int numberOfCyclists){
    char targetName[NAME];
    fscanf(stdin,"%s",targetName);
    int flag = 0;
    for(int i=0;i<numberOfCyclists;i++){
        if(strcmp(cyclists[i].name,targetName) == 0){
            flag = 1;
            fprintf(stdout,"\nId: %d\nNumber of laps performed: %d\nLap times: ",cyclists[i].id,cyclists[i].numberOfLapsPerformed);
            for(int j=0;j<cyclists[i].numberOfLapsPerformed;j++){
                fprintf(stdout,"%.2f ",cyclists[i].laps[j]);
            }
            fprintf(stdout,"(average: %.2f)\n",cyclists[i].average);
            break;
        }
    }
    if(flag == 0){
        fprintf(stdout,"\nThere is no athlete with such a name!\n");
    }
}
void best(cyclistT *cyclists,int numberOfCyclists){
    int min = 0;
    for(int i=1;i<numberOfCyclists;i++){
        if(cyclists[i].average < cyclists[min].average){
            min = i;
        }
    }
    fprintf(stdout,"\nName: %s\nId: %d\nNumber of laps performed: %d\nLap times: ",cyclists[min].name,cyclists[min].id,cyclists[min].numberOfLapsPerformed);
    for(int j=0;j<cyclists[min].numberOfLapsPerformed;j++){
        fprintf(stdout,"%.2f ",cyclists[min].laps[j]);
    }
    fprintf(stdout,"(average: %.2f)\n",cyclists[min].average);
}

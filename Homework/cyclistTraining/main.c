#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 50+1
#define FILENAME 20+1
#define NAME 30+1
typedef struct cyclistS cyclistT;
struct cyclistS{
    char name[NAME];
    int identifier;
    int lapsPerformed;
    float *lapTimes;
    float average;
};
cyclistT *loadCyclistsFile(int *);
void list(cyclistT *,int);
void detail(cyclistT *,int);
void best(cyclistT *,int);
int main()
{
    int numberOfCyclists;
    cyclistT *cyclists = loadCyclistsFile(&numberOfCyclists);
    char answer[DIM];
    do{
        fprintf(stdout,"\n->list\n->detail name\n->best\n->stop\n=> ");
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
    int identifier,i = 0;
    int lapsPerformed;
    while(fscanf(f,"%s %d %d",name,&identifier,&lapsPerformed) != EOF){
        strcpy(cyclists[i].name,name);
        cyclists[i].identifier = identifier;
        cyclists[i].lapsPerformed = lapsPerformed;
        cyclists[i].lapTimes = (float *) malloc(lapsPerformed * sizeof(float));
        int j = 0;
        cyclists[i].average = 0;
        while(j < lapsPerformed){
            fscanf(f,"%f",&cyclists[i].lapTimes[j]);
            cyclists[i].average += cyclists[i].lapTimes[j];
            j++;
        }
        cyclists[i].average /= lapsPerformed;
        i++;
    }
    return cyclists;
}
void list(cyclistT *cyclists,int numberOfCyclists){
    fprintf(stdout,"\nNumber of athletes: %d\n",numberOfCyclists);
    for(int i=0;i<numberOfCyclists;i++)
        fprintf(stdout,"\nName: %s\n#Id: %d\n#Laps: %d\n",cyclists[i].name,cyclists[i].identifier,cyclists[i].lapsPerformed);
}
void detail(cyclistT *cyclist,int numberOfCyclists){
    char targetName[NAME];
    fscanf(stdin,"%s",targetName);
    for(int i=0;i<numberOfCyclists;i++){
        if(strcmp(targetName,cyclist[i].name) == 0){
            fprintf(stdout,"\n#Id: %d\n#Laps: %d\nTimes: ",cyclist[i].identifier,cyclist[i].lapsPerformed);
            for(int j=0;j<cyclist[i].lapsPerformed;j++){
                fprintf(stdout,"%f ",cyclist[i].lapTimes[j]);
            }
            fprintf(stdout,"\n");
            break;
        }
    }
}
void best(cyclistT *cyclists,int numberOfCyclists){
    int min = 0;
    for(int i=1;i<numberOfCyclists;i++){
        if(cyclists[i].average < cyclists[min].average)
            min = i;
    }
    fprintf(stdout,"\nName: %s\n#Id number: %d\nTimes: ",cyclists[min].name,cyclists[min].identifier);
    for(int j=0;j<cyclists[min].lapsPerformed;j++){
        fprintf(stdout,"%f ",cyclists[min].lapTimes[j]);
    }
    fprintf(stdout,"\n(Average: %f)\n",cyclists[min].average);
}

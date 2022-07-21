#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 20+1
typedef struct fileS fileT;
typedef struct driverS driverT;
struct fileS{
    int lapNumber;
    char *name;
    fileT *next;
};
struct driverS{
    int driverNumber;
    char *driverName;
    char *teamName;
    int totalLap;
    int bestLap;
    int numberBestLap;
    int flag;
    driverT *next;
};
fileT *createFile(int,char *);  //files functions
fileT *loadFiles();
void printFilesList(fileT *);
void printFiles(fileT *);
driverT *createDriver(int,char *,char *,int);    //drivers functions
driverT *isAlreadyPresent(driverT *,int);
driverT *loadDrivers(fileT *);
void printDrivers(driverT *);
void printPodium(driverT *);
driverT *findBestLap(driverT *);
int main()
{
    fileT *filesHead = loadFiles();
    printFilesList(filesHead);
    printFiles(filesHead);
    driverT *driversHead = loadDrivers(filesHead);
    printDrivers(driversHead);
    printPodium(driversHead);
    driverT *d = findBestLap(driversHead);
    fprintf(stdout,"\n\nFASTEST LAP: %s, %s, %d seconds,lap %d\n",d->driverName,d->teamName,d->bestLap,d->numberBestLap);
    return 0;
}
fileT *createFile(int lapNumber,char *file){
    fileT *newFile = (fileT *) malloc(sizeof(fileT));
    newFile->lapNumber = lapNumber;
    newFile->name = (char *) malloc((strlen(file) + 1) * sizeof(char));
    strcpy(newFile->name,file);
    newFile->next = NULL;
    return newFile;
}
fileT *loadFiles(){
    fileT *filesHead = NULL;
    char filename[DIM];
    int lapNumber;
    char file[DIM];
    fprintf(stdout,"filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    while(fscanf(f,"%d %s",&lapNumber,file) != EOF){
        fileT *newFile = createFile(lapNumber,file);
        newFile->next = filesHead;
        filesHead = newFile;
    }
    return filesHead;
}
void printFilesList(fileT *filesHead){
    fileT *temp = filesHead;
    fprintf(stdout,"\nFILES");
    while(temp != NULL){
        fprintf(stdout,"\n%d %s",temp->lapNumber,temp->name);
        temp = temp->next;
    }
}
void printFiles(fileT *files){
    fileT *f = files;
    while(f != NULL){
        char filename[DIM];
        int driverNumber,lapTime;
        char driverName[DIM];
        char teamName[DIM];
        strcpy(filename,f->name);
        FILE *file = fopen(filename,"r");
        fprintf(stdout,"\n\nFILE \"%s\"",filename);
        while(fscanf(file,"%d %s %s %d",&driverNumber,driverName,teamName,&lapTime) != EOF){
            fprintf(stdout,"\n%d %s %s %d",driverNumber,driverName,teamName,lapTime);
        }
        f = f->next;
    }
}
driverT *createDriver(int driverNumber,char *driverName,char *teamName,int lapTime){
    driverT *newDriver = (driverT *) malloc(sizeof(driverT));
    newDriver->driverNumber = driverNumber;
    newDriver->totalLap = lapTime;
    newDriver->bestLap = lapTime;
    newDriver->numberBestLap = 0;
    newDriver->driverName = (char *) malloc((strlen(driverName)+1) * sizeof(char));
    newDriver->teamName = (char *) malloc((strlen(teamName)+1) * sizeof(char));
    strcpy(newDriver->driverName,driverName);
    strcpy(newDriver->teamName,teamName);
    newDriver->flag = 0;
    return newDriver;
}
driverT *isAlreadyPresent(driverT *driversHead,int driverNumber){
    driverT *d = driversHead;
    while(d != NULL){
        if(d->driverNumber == driverNumber)
            return d;
        d = d->next;
    }
    return NULL;
}
driverT *loadDrivers(fileT *filesHead){
    driverT *driversHead = NULL;
    while(filesHead != NULL){
        char filename[DIM];
        int driverNumber,lapTime;
        char driverName[DIM];
        char teamName[DIM];
        strcpy(filename,filesHead->name);
        FILE *f = fopen(filename,"r");
        while(fscanf(f,"%d %s %s %d",&driverNumber,driverName,teamName,&lapTime) != EOF){
            driverT *d = isAlreadyPresent(driversHead,driverNumber);
            if(d == NULL){
                driverT *newDriver = createDriver(driverNumber,driverName,teamName,lapTime);
                newDriver->numberBestLap = filesHead->lapNumber;
                newDriver->next = driversHead;
                driversHead = newDriver;
            }else{
                d->totalLap += lapTime;
                if(d->bestLap > lapTime){
                    d->bestLap = lapTime;
                    d->numberBestLap = filesHead->lapNumber;
                }
            }
        }
        filesHead = filesHead->next;
    }
    return driversHead;
}
void printDrivers(driverT *driversHead){
    driverT *d = driversHead;
    fprintf(stdout,"\n\nDRIVERS:");
    while(d != NULL){
        fprintf(stdout,"\n%d %s %s (best lap: %ds seconds during lap %d, total lap time: %d seconds)",d->driverNumber,d->driverName,d->teamName,d->bestLap,d->numberBestLap,d->totalLap);
        d = d->next;
    }
}
void printPodium(driverT *driversHead){
    fprintf(stdout,"\n\nPODIUM:");
    for(int i=0;i<3;i++){
        driverT *currentBest = NULL;
        driverT *d = driversHead;
        while(d != NULL){
            if(currentBest == NULL && d->flag == 0)
                currentBest = d;
            else if(d->totalLap < currentBest->totalLap && d->flag == 0)
                currentBest = d;
            d = d->next;
        }
        fprintf(stdout,"\n%d.%s, %s, %d seconds",i+1,currentBest->driverName,currentBest->teamName,currentBest->totalLap);
        currentBest->flag = 1;
    }
}
driverT *findBestLap(driverT *driversHead){
    driverT *d = driversHead->next;
    driverT *bestDriver = driversHead;
    while(d != NULL){
        if(d->bestLap < bestDriver->bestLap){
            bestDriver = d;
        }
        d = d->next;
    }
    return bestDriver;
}

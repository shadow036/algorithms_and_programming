#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 25+1
#define YEAR 100
#define FILENAME 20+1
#define COMMAND 50+1
typedef struct hospitalS hospitalT;
typedef struct bedS bedT;
struct hospitalS{
    char hospitalName[DIM];
    char unitName[DIM];
    int numberOfBeds;
    char **bedsCalendar;
};
hospitalT *loadHospitals(int *);
void reserve(hospitalT *,int);
int checkAvailability(hospitalT *,int,int,int,int,int);
void removeReservation(hospitalT *,int);
int checkRemovability(hospitalT *,int,int,int);
//UTILITY FUNCTION
void printHospitals(hospitalT *,int);
int main()
{
    int numberOfHospitals;
    hospitalT *hospitals = loadHospitals(&numberOfHospitals);
    char command[COMMAND];
    fprintf(stdout,"\n");
    do{
        fprintf(stdout,"->reserve unitName n\n->remove hospitalName unitName from to\n->print\n->end\nCommand: ");
        fscanf(stdin,"%s",command);
        if(strcmp(command,"reserve") == 0){
            reserve(hospitals,numberOfHospitals);
        }else if(strcmp(command,"remove") == 0){
            removeReservation(hospitals,numberOfHospitals);
        }else if(strcmp(command,"print") == 0){
            printHospitals(hospitals,numberOfHospitals);
        }
        fprintf(stdout,"\n");
    }while(strcmp(command,"end") != 0);
    return 0;
}
hospitalT *loadHospitals(int *numberOfHospitals){
    char filename[FILENAME];
    fprintf(stdout,"hospitals filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    fscanf(f,"%d",numberOfHospitals);
    hospitalT *hospitals = (hospitalT *) malloc(*numberOfHospitals * sizeof(hospitalT));
    char hospitalName[DIM];
    char unitName[DIM];
    int numberOfBeds;
    int i=0;
    while(fscanf(f,"%s %s %d",hospitalName,unitName,&numberOfBeds) != EOF){
        strcpy(hospitals[i].hospitalName,hospitalName);
        strcpy(hospitals[i].unitName,unitName);
        hospitals[i].numberOfBeds = numberOfBeds;
        hospitals[i].bedsCalendar = (char **) malloc(numberOfBeds * sizeof(char *));
        for(int j=0;j<numberOfBeds;j++){
            hospitals[i].bedsCalendar[j] = (char *) malloc(YEAR * sizeof(char));
            for(int k=0;k<YEAR;k++){
                hospitals[i].bedsCalendar[j][k] = 'O';
            }
        }
        i++;
    }
    return hospitals;
}
void reserve(hospitalT *hospitals,int numberOfHospitals){
    char unitName[DIM];
    int period;
    fscanf(stdin,"%s %d",unitName,&period);
    int min = YEAR-1;
    int targetHospital = -1;
    int targetBed = -1;
    for(int i=0;i<numberOfHospitals;i++){
        if(strcmp(hospitals[i].unitName,unitName) == 0){
            for(int j=0;j<hospitals[i].numberOfBeds;j++){
                for(int k=0;k<=YEAR-period;k++){
                    if(checkAvailability(hospitals,i,j,k,period,min) == 1){
                        min = k;
                        targetHospital = i;
                        targetBed = j;
                    }
                }
            }
        }
    }
    if(targetHospital == -1){
        fprintf(stdout,"\nReservation impossible!\n");
        return;
    }
    for(int i=min;i<min+period;i++){
        hospitals[targetHospital].bedsCalendar[targetBed][i] = 'X';
    }
    fprintf(stdout,"\nReservation done!\nHospital: %s\nFrom: %d\nTo: %d\nBed number: %d\n",hospitals[targetHospital].hospitalName,min+1,min+period,targetBed+1);
}
int checkAvailability(hospitalT *hospitals,int hospitalNumber,int bedNumber,int startingDay,int period,int min){
    if(startingDay > min)
        return 0;
    for(int i=startingDay;i<startingDay+period;i++){
        if(hospitals[hospitalNumber].bedsCalendar[bedNumber][i] == 'X')
            return 0;
    }
    return 1;
}
void removeReservation(hospitalT *hospitals,int numberOfHospitals){
    char hospitalName[DIM];
    char unitName[DIM];
    int startingDay;
    int endingDay;
    fscanf(stdin,"%s %s %d %d",hospitalName,unitName,&startingDay,&endingDay);
    for(int i=0;i<numberOfHospitals;i++){
        if(strcmp(hospitals[i].hospitalName,hospitalName) == 0 && strcmp(hospitals[i].unitName,unitName) == 0){
            if(checkRemovability(hospitals,i,startingDay,endingDay) == 1){
                fprintf(stdout,"\nReservation removed.\n");
                return;
            }
        }
    }
    fprintf(stdout,"\nReservation NOT removed!\n");
}
int checkRemovability(hospitalT *hospitals,int hospitalNumber,int startingDay,int endingDay){
    for(int i=0;i<hospitals[hospitalNumber].numberOfBeds;i++){
        int flag = 1;
        for(int j=startingDay-1;j<endingDay;j++){
            if(hospitals[hospitalNumber].bedsCalendar[i][j] == 'O')
                flag = 0;
        }
        if(flag == 1){
            for(int j=startingDay-1;j<endingDay;j++){
                hospitals[hospitalNumber].bedsCalendar[i][j] = 'O';
            }
            return 1;
        }
    }
    return 0;
}
//UTILITY FUNCTION
void printHospitals(hospitalT *hospitals,int numberOfHospitals){
    fprintf(stdout,"\n");
    for(int i=0;i<numberOfHospitals;i++){
        fprintf(stdout,"%s %s %d\n",hospitals[i].hospitalName,hospitals[i].unitName,hospitals[i].numberOfBeds);
        for(int j=0;j<hospitals[i].numberOfBeds;j++){
            fprintf(stdout,"Bed %d -> ",j+1);
            for(int k=0;k<YEAR;k++){
                fprintf(stdout,"%c",hospitals[i].bedsCalendar[j][k]);
            }
            fprintf(stdout,"\n");
        }
        fprintf(stdout,"\n");
    }
}

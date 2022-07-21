#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CODE 5+1
#define CITY 20+1
#define FILENAME 20+1
typedef struct flightS flightT;
struct flightS{
    char *code;
    char *originCity;
    char *destinationCity;
    float departureTime;
    float arrivalTime;
    flightT *next;
};
flightT *loadFile();
flightT *createFlight(char *,char *,char *,float,float);
void findFlights(flightT *);
int main()
{
    flightT *flights = loadFile();
    findFlights(flights);
    return 0;
}
flightT *loadFile(){
    char filename[FILENAME];
    fprintf(stdout,"flights filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    flightT *flights = NULL;
    char code[CODE];
    char originCity[CITY];
    char destinationCity[CITY];
    float departureTime;
    float arrivalTime;
    while(fscanf(f,"%s %s %s %f %f",code,originCity,destinationCity,&departureTime,&arrivalTime) != EOF){
        flightT *newFlight = createFlight(code,originCity,destinationCity,departureTime,arrivalTime);
        newFlight->next = flights;
        flights = newFlight;
    }
    fclose(f);
    return flights;
}
flightT *createFlight(char *code,char *originCity,char *destinationCity,float departureTime,float arrivalTime){
    flightT *newFlight = (flightT *) malloc(sizeof(flightT));
    newFlight->code = (char *) malloc((strlen(code)+1) * sizeof(char));
    strcpy(newFlight->code,code);
    newFlight->originCity = (char *) malloc((strlen(originCity)+1) * sizeof(char));
    strcpy(newFlight->originCity,originCity);
    newFlight->destinationCity = (char *) malloc((strlen(destinationCity)+1) * sizeof(char));
    strcpy(newFlight->destinationCity,destinationCity);
    newFlight->departureTime = departureTime;
    newFlight->arrivalTime = arrivalTime;
    newFlight->next = NULL;
    return newFlight;
}
void findFlights(flightT *flights){
    char originCity[CITY];
    char destinationCity[CITY];
    float departureTime;
    fprintf(stdout,"origin city destination city departure time=> ");
    fscanf(stdin,"%s %s %f",originCity,destinationCity,&departureTime);
    //fprintf(stdout,"\n");
    flightT *f = flights;
    while(f != NULL){
        if(strcmp(f->originCity,originCity) == 0 && f->departureTime >= departureTime){
            if(strcmp(f->destinationCity,destinationCity) == 0){
                fprintf(stdout,"\nNo stop:\n%s %s %s %.2f %.2f\n",f->code,f->originCity,f->destinationCity,f->departureTime,f->arrivalTime);
            }else{
                flightT *f2 = flights;
                while(f2 != NULL){
                    if(strcmp(f2->destinationCity,destinationCity) == 0 && f2->departureTime >= f->arrivalTime && strcmp(f2->originCity,f->destinationCity) == 0){
                        fprintf(stdout,"\n1 stop:\n%s %s %s %.2f %.2f\n%s %s %s %.2f %.2f\n",f->code,f->originCity,f->destinationCity,f->departureTime,f->arrivalTime,f2->code,f2->originCity,f2->destinationCity,f2->departureTime,f2->arrivalTime);
                    }
                    f2 = f2->next;
                }
            }
        }
        f = f->next;
    }
    //fprintf(stdout,"\n");
}

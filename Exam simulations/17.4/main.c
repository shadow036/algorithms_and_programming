#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
int main()
{
    carT *cars = createBST(fopen("cars.txt","r"));
    char command[LENGTH];
    while(strcmp(command,"exit")){
        fprintf(stdout,"\naddCar modelName availabilityData price\ncancelCar modelName\naddOptional modelName optionalName availabilityData price\ncancelOptional modelName optionalName\nfind accessory1 accessory2 accessory3 ...\nprint\nexit\n=> ");
        fscanf(stdin,"%s",command);
        if(!strcmp(command,"addCar")){
            char modelName[LENGTH];
            char availabilityData[DATE];
            int price;
            fscanf(stdin,"%s %s %d",modelName,availabilityData,&price);
            carT *newCar = createCar(modelName,availabilityData,price,"");
            cars = insertCar(cars,newCar);
        }else if(!strcmp(command,"cancelCar")){
            char modelName[LENGTH];
            fscanf(stdin,"%s",modelName);
            cars = deleteCar(cars,modelName);
        }else if(!strcmp(command,"addOptional")){
            char modelName[LENGTH];
            char optionalName[LENGTH];
            char availabilityData[DATE];
            int price;
            fscanf(stdin,"%s %s %s %d",modelName,optionalName,availabilityData,&price);
            carT *targetCar = searchCar(cars,modelName);
            optionalT *newOptional = createOptional(optionalName,availabilityData,price);
            newOptional->next = targetCar->optionalsList;
            targetCar->optionalsList= newOptional;
        }else if(!strcmp(command,"cancelOptional")){
            char modelName[LENGTH];
            char optionalName[LENGTH];
            fscanf(stdin,"%s %s",modelName,optionalName);
            carT *targetCar = searchCar(cars,modelName);
            targetCar->optionalsList = deleteOptional(targetCar->optionalsList,optionalName);
        }else if(!strcmp(command,"find")){
            optionalT *optionals = NULL;
            char *command2 = (char *) malloc(LENGTH * LENGTH * sizeof(char));
            char optionalName[LENGTH];
            gets(command2);
            while(sscanf(command2,"%s",optionalName) != EOF){
                optionalT *newOptional = createOptional(optionalName,"",-1);
                newOptional->next = optionals;
                optionals = newOptional;
                command2 += (strlen(optionalName)+1);   //+1 because of the space
            }
            carT *bestCar = NULL;
            int bestMatches = -1;
            findBestMatch(cars,optionals,&bestCar,&bestMatches);
            fprintf(stdout,"\nThe car that matches the most characteristics is %s (%d characteristics met)\n",bestCar->modelName,bestMatches);
        }else if(!strcmp(command,"print")){
            inOrderTraversal(cars);
            fprintf(stdout,"\n");
        }
    }
    return 0;
}

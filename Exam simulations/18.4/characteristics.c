#include "characteristics.h"
characteristicT *createSecondaryList(FILE *f){
    characteristicT *characteristicsList = NULL;
    char name[LENGTH];
    char value[LENGTH];
    while(fscanf(f,"%s %s",name,value) != EOF){
        characteristicT *newCharacteristic = createCharacteristic(name,value);
        newCharacteristic->nextCharacteristic = characteristicsList;
        characteristicsList = newCharacteristic;
    }
    return characteristicsList;
}
characteristicT *createCharacteristic(char *name,char *value){
    characteristicT *newCharacteristic = (characteristicT *) malloc(sizeof(characteristicT));
    strcpy(newCharacteristic->name,name);
    strcpy(newCharacteristic->value,value);
    newCharacteristic->nextCharacteristic = NULL;
    return newCharacteristic;
}

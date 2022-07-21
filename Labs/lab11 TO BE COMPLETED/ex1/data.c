#include "data.h"

int readData (FILE *fp,data_t *data){
  int retValue;

  retValue = fscanf (fp, "%s %s %d %d", data->registerNumber,data->lastName,&data->numberCreditLoaded,&data->numberCreditPassed);

  return (retValue);
}


void writeData(FILE *fp,data_t data){
  fprintf(fp, "%s %s %d %d\n", data.registerNumber,data.lastName,data.numberCreditLoaded,data.numberCreditPassed);

  return;
}


int compare(data_t d1,data_t d2){
  if (strcmp(d1.registerNumber,d2.registerNumber) < 0) {
    return (-1);
  } else {
    if (!strcmp(d1.registerNumber,d2.registerNumber)) {
      return (0);
    } else {
      return (1);
    }
  }
}

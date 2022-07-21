#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "item.h"
#include "data.h"

Item ITEMscan() {
  char registerNumber[REGISTER_NUMBER];
  char lastName[LAST_NAME];
  int creditsLoaded;
  int creditsPassed;

  printf("register number = ");
  scanf("%s",registerNumber);
  printf("lastName = ");
  scanf("%s", lastName);
  printf("credits loaded = ");
  scanf("%d",&creditsLoaded);
  printf("credits passed = ");
  scanf("%d", &creditsPassed);

  Item tmp = (Item) malloc(sizeof(struct data));
  if (tmp == NULL)
    return ITEMsetvoid();

  else {
    strcpy(tmp->registerNumber,registerNumber);
    strcpy(tmp->lastName,lastName);
    tmp->numberCreditLoaded = creditsLoaded;
    tmp->numberCreditPassed = creditsPassed;
  }
  return tmp;
}

void ITEMshow(Item data) {
  printf("register number = %s\nlast name = %s\ncreadits loaded = %d\ncredits passed = %d\n", data->registerNumber, data->lastName,data->numberCreditLoaded,data->numberCreditPassed);
}

int ITEMcheckvoid(Item data) {
  Key k1, k2="";
  k1 = KEYget(data);
  if (KEYcompare(k1,k2)==0)
    return 1;
  else
    return 0;
}

Item ITEMsetvoid() {
  Item tmp = (Item) malloc(sizeof(struct data));
  if (tmp != NULL) {
    strcpy(tmp->registerNumber,"");
    strcpy(tmp->lastName,"");
    tmp->numberCreditLoaded = -1;
    tmp->numberCreditPassed = -1;
  }
  return tmp;
}

Key KEYscan() {
  char registerNumber[REGISTER_NUMBER];
  Key k;
  scanf("%s", registerNumber);
  k = strdup(registerNumber);
  return k;
}

int  KEYcompare(Key k1, Key k2) {
  return strcmp(k1,k2);
}

Key KEYget(Item data) {
  return data->registerNumber;
}

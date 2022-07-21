#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 50+1
#define ID 16+1
#define DATE 10+1
typedef struct employeeS employeeT;
struct employeeS{
    char *surnameName;
    char id[ID];
    char dateOfHiring[DATE];
    int salary;
    employeeT *prev;
    employeeT *next;
};
employeeT *loadFile(char *);
employeeT *createEmployee(char *,char *,char *,int);
employeeT *findInitialEmployee(employeeT *,char *);
void move(employeeT *,char *);
int main(int argc,char *argv[])
{
    if(argc != 4){
        fprintf(stdout,"Wrong number of parameters!\n");
        return EXIT_FAILURE;
    }
    employeeT *employees = loadFile(argv[1]);
    employeeT *initialEmployee = findInitialEmployee(employees,argv[2]);
    if(initialEmployee == NULL){
        fprintf(stdout,"Can't find initial employee!\n");
        return EXIT_FAILURE;
    }
    move(initialEmployee,argv[3]);
    return 0;
}
employeeT *loadFile(char *filename){
    FILE *f = fopen(filename,"r");
    employeeT *employees = NULL;
    char surnameName[DIM];
    char id[ID];
    char dateOfHiring[DATE];
    int salary;
    while(fscanf(f,"%s %s %s %d\n",surnameName,id,dateOfHiring,&salary) != EOF){
        employeeT *newEmployee = createEmployee(surnameName,id,dateOfHiring,salary);
        if(employees == NULL){
            employees = newEmployee;
        }else{
            employees->prev = newEmployee;
            newEmployee->next = employees;
            employees = newEmployee;
        }
    }
    return employees;
}
employeeT *createEmployee(char *surnameName,char *id,char *dateOfHiring,int salary){
    employeeT *newEmployee = (employeeT *) malloc(sizeof(employeeT));
    newEmployee->surnameName = (char *) malloc((strlen(surnameName)+1) * sizeof(char));
    strcpy(newEmployee->surnameName,surnameName);
    strcpy(newEmployee->id,id);
    strcpy(newEmployee->dateOfHiring,dateOfHiring);
    newEmployee->salary = salary;
    newEmployee->prev = NULL;
    newEmployee->next = NULL;
    return newEmployee;
}
employeeT *findInitialEmployee(employeeT *employees,char *initialEmployeeName){
    employeeT *temp = employees;
    while(temp != NULL){
        if(strcmp(temp->surnameName,initialEmployeeName) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
void move(employeeT *initialEmployee,char *string){
    fprintf(stdout,"%s %s %s %d\n",initialEmployee->surnameName,initialEmployee->id,initialEmployee->dateOfHiring,initialEmployee->salary);
    while(*string != '\0'){
        if(*string == '+'){
            if(initialEmployee->next != NULL)
                initialEmployee = initialEmployee->next;
            fprintf(stdout,"%s %s %s %d\n",initialEmployee->surnameName,initialEmployee->id,initialEmployee->dateOfHiring,initialEmployee->salary);
        }else if(*string == '-'){
            if(initialEmployee->prev != NULL)
                initialEmployee = initialEmployee->prev;
            fprintf(stdout,"%s %s %s %d\n",initialEmployee->surnameName,initialEmployee->id,initialEmployee->dateOfHiring,initialEmployee->salary);
        }
        string++;
    }
}

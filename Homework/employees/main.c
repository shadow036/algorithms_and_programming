#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 50+1
typedef struct employeeS employeeT;
struct employeeS{
    char *lastName;
    char *firstName;
    char *id;
    int numberOfWorkingWeeks;
    int *workingWeeks;
    int *workingDays;
    int **workingHours;
    int totalWorkingHours;
    employeeT *next;
};
employeeT *loadFile();
employeeT *createEmployee(char *,char *,char *,int);
void sort(employeeT **,employeeT *,int);
void show(employeeT *);
int main()
{
    int numberOfEmployees;
    employeeT *employees = loadFile(&numberOfEmployees);
    employeeT **employeesArray = (employeeT **) malloc(numberOfEmployees * sizeof(employeeT *));
    sort(employeesArray,employees,numberOfEmployees);
    return 0;
}
employeeT *loadFile(int *numberOfEmployees){
    *numberOfEmployees = 0;
    employeeT *employees = NULL;
    char filename[DIM];
    fprintf(stdout,"employees filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    char lastName[DIM];
    char firstName[DIM];
    char id[DIM];
    int numberOfWorkingWeeks;
    while(fscanf(f,"%s %s %s %d",lastName,firstName,id,&numberOfWorkingWeeks) != EOF){
        (*numberOfEmployees)++;
        employeeT *employee = createEmployee(lastName,firstName,id,numberOfWorkingWeeks);
        employee->workingWeeks = (int *) malloc(numberOfWorkingWeeks * sizeof(int));
        employee->workingDays = (int *) malloc(numberOfWorkingWeeks * sizeof(int));
        employee->workingHours = (int **) malloc(numberOfWorkingWeeks * sizeof(int *));
        int weekNumber,numberOfWorkingDays;
        for(int i=0;i<numberOfWorkingWeeks;i++){
            fscanf(f,"%d %d",&weekNumber,&numberOfWorkingDays);
            employee->workingWeeks[i] = weekNumber;
            employee->workingDays[i] = numberOfWorkingDays;
            employee->workingHours[i] = (int *) malloc(numberOfWorkingDays * sizeof(int));
            int hours;
            for(int j=0;j<numberOfWorkingDays;j++){
                fscanf(f,"%d",&hours);
                employee->workingHours[i][j] = hours;
                employee->totalWorkingHours += hours;
            }
        }
        employee->next = employees;
        employees = employee;
    }
    return employees;
}
employeeT *createEmployee(char *lastName,char *firstName,char *id,int numberOfWorkingWeeks){
    employeeT *employee = (employeeT *) malloc(sizeof(employeeT));
    employee->lastName = (char *) malloc((strlen(lastName)+1) * sizeof(char));
    strcpy(employee->lastName,lastName);
    employee->firstName = (char *) malloc((strlen(firstName)+1) * sizeof(char));
    strcpy(employee->firstName,firstName);
    employee->id = (char *) malloc((strlen(id)+1) * sizeof(char));
    strcpy(employee->id,id);
    employee->numberOfWorkingWeeks = numberOfWorkingWeeks;
    employee->workingWeeks = employee->workingDays = NULL;
    employee->workingHours = NULL;
    employee->totalWorkingHours = 0;
    employee->next = NULL;
    return employee;
}
void sort(employeeT **employeesArray,employeeT *employees,int numberOfEmployees){
    int i=0;
    while(employees != NULL){
        employeesArray[i] = employees;
        employees = employees->next;
        i++;
    }
    for(int i2=0;i2<numberOfEmployees-1;i2++){
        int min = i2;
        for(int j=i2+1;j<numberOfEmployees;j++){
            if(employeesArray[j]->totalWorkingHours < employeesArray[min]->totalWorkingHours){
                min = j;
            }
        }
        employeeT *temp = employeesArray[i2];
        employeesArray[i2] = employeesArray[min];
        employeesArray[min] = temp;
    }
    for(int i3=0;i3<numberOfEmployees;i3++)
        show(employeesArray[i3]);
}
void show(employeeT *employee){
    fprintf(stdout,"\n%s %s %s %d\n",employee->lastName,employee->firstName,employee->id,employee->numberOfWorkingWeeks);
    for(int i=0;i<employee->numberOfWorkingWeeks;i++){
        fprintf(stdout,"%d %d ",employee->workingWeeks[i],employee->workingDays[i]);
        for(int j=0;j<employee->workingDays[i];j++){
            fprintf(stdout,"%d ",employee->workingHours[i][j]);
        }
        fprintf(stdout,"\n");
    }
}

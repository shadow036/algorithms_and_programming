#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME 20+1
#define NAME 50+1
#define ID 16+1
#define DATE 10+1
#define STRING 20+1
typedef struct employeeS employeeT;
struct employeeS{
    char surnameName[NAME];
    char id[ID];
    char dateOfHiring[DATE];
    int salary;
    employeeT *right;
    employeeT *left;
};
employeeT *loadFile();
employeeT *createEmployee(char *,char *,char *,int);
employeeT *findInitialEmployee(employeeT *);
void printEmployees(employeeT *);
int main()
{
    employeeT *employees = loadFile();
    employeeT *initialEmployee = findInitialEmployee(employees);
    printEmployees(initialEmployee);
    return 0;
}
employeeT *loadFile(){
    char filename[FILENAME];
    fprintf(stdout,"employees filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    char surnameName[NAME];
    char id[ID];
    char dateOfHiring[DATE];
    int salary;
    employeeT *employees = NULL;
    while(fscanf(f,"%s %s %s %d",surnameName,id,dateOfHiring,&salary) != EOF){
        employeeT *employee = createEmployee(surnameName,id,dateOfHiring,salary);
        employee->right = employees;
        if(employees != NULL)
            employees->left = employee;
        employees = employee;
    }
    return employees;
}
employeeT *createEmployee(char *surnameName,char *id,char *dateOfHiring,int salary){
    employeeT *employee = (employeeT *) malloc(sizeof(employeeT));
    strcpy(employee->surnameName,surnameName);
    strcpy(employee->id,id);
    strcpy(employee->dateOfHiring,dateOfHiring);
    employee->salary = salary;
    employee->right = NULL;
    employee->left = NULL;
    return employee;
}
employeeT *findInitialEmployee(employeeT *employees){
    char initialEmployeeName[NAME];
    fprintf(stdout,"initial employee name => ");
    fscanf(stdin,"%s",initialEmployeeName);
    employeeT *temp = employees;
    while(strcmp(temp->surnameName,initialEmployeeName) != 0){
        temp = temp->right;
    }
    return temp;
}
void printEmployees(employeeT *initialEmployee){
    char string[STRING];
    fprintf(stdout,"string => ");
    fscanf(stdin,"%s",string);
    fprintf(stdout,"\n");
    for(int i=0;i<=strlen(string);i++){
        fprintf(stdout,"%s %s %s %d\n",initialEmployee->surnameName,initialEmployee->id,initialEmployee->dateOfHiring,initialEmployee->salary);
        if(string[i] == '-'){
            if(initialEmployee->left != NULL)
                initialEmployee = initialEmployee->left;
        }else if(string[i] == '+'){
            if(initialEmployee->right != NULL)
                initialEmployee = initialEmployee->right;
        }
    }
}

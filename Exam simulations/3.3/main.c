#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 50+1
char ***createCoursesArray(int *);
char **createDishesArray(int *,int);
void printCompositions(char ***,char **,int *,int,int);
int main()
{
    int n,n2;
    char ***courses = createCoursesArray(&n);
    int *dimensionArray = (int *) malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        courses[i] = createDishesArray(&n2,i);
        dimensionArray[i] = n2;
    }
    char **composition = (char **) malloc(n * sizeof(char *));
    printCompositions(courses,composition,dimensionArray,0,n);
    return 0;
}
char ***createCoursesArray(int *n){
    fprintf(stdout,"Number of courses => ");
    fscanf(stdin,"%d",n);
    char ***courses = (char ***) malloc(*n * sizeof(char **));
    for(int i=0;i<*n;i++)
        courses[i] = NULL;
    return courses;
}
char **createDishesArray(int *n2,int courseNumber){
    fprintf(stdout,"Number of dishes course %d: ",courseNumber);
    fscanf(stdin,"%d",n2);
    char **dishes = (char **) malloc(*n2 * sizeof(char *));
    char dish[DIM];
    for(int i=0;i<*n2;i++){
        fprintf(stdout,"Course %d dish %d: ",courseNumber,i);
        fscanf(stdin,"%s",dish);
        dishes[i] = (char *) malloc((strlen(dish)+1) * sizeof(char));
        strcpy(dishes[i],dish);
    }
    return dishes;
}
void printCompositions(char ***courses,char **composition,int *dimensionArray,int pos,int n){
    if(pos == n){
        for(int i=0;i<n;i++)
            fprintf(stdout,"%s ",composition[i]);
        fprintf(stdout,"\n");
        return;
    }
    for(int i=0;i<dimensionArray[pos];i++){
        composition[pos] = courses[pos][i];
        printCompositions(courses,composition,dimensionArray,pos+1,n);
    }
    return;
}

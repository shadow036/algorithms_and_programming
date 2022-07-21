#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 100+1
typedef struct stringS stringT;
struct stringS{
    char *string;
};
//FIRST VERSION
stringT *loadFileA(FILE *,int *);
void sortStringsA(stringT *,int);
void printFileA(FILE *,stringT *,int);
//SECOND VERSION
char **loadFileB(FILE *,int *);
void sortStringsB(char **,int);
void printFileB(FILE *,char **,int);
int main(int argc,char *argv[])
{
    if(argc != 3){
        fprintf(stdout,"Wrong number of arguments!\n");
        return EXIT_FAILURE;
    }
    FILE *f = fopen(argv[1],"r");
    FILE *f2 = fopen(argv[2],"w");
    int numberOfStrings;
    /*
    FIRST VERSION
    stringT *strings = loadFileA(f,&numberOfStrings);
    sortStringsA(strings,numberOfStrings);
    printFileA(f2,strings,numberOfStrings);
    */
    //SECOND VERSION
    char **matrix = loadFileB(f,&numberOfStrings);
    sortStringsB(matrix,numberOfStrings);
    printFileB(f2,matrix,numberOfStrings);
    fclose(f);
    fclose(f2);
    return 0;
}
//FIRST VERSION
stringT *loadFileA(FILE *f,int *numberOfStrings){
    fscanf(f,"%d%*c",numberOfStrings);
    stringT *strings = (stringT *) malloc(*numberOfStrings * sizeof(stringT));
    char string[DIM];
    for(int i=0;i<*numberOfStrings;i++){
        fscanf(f,"%s",string);
        strings[i].string = strdup(string);
    }
    return strings;
}
void sortStringsA(stringT *strings,int numberOfStrings){
    char temp[DIM];
    for(int i=0;i<numberOfStrings-1;i++){
        int min = i;
        for(int j=i+1;j<numberOfStrings;j++){
            if(strcmp(strings[j].string,strings[min].string) < 0)
              min = j;
        }
        if(min != i){
            strcpy(temp,strings[i].string);
            strcpy(strings[i].string,strings[min].string);
            strcpy(strings[min].string,temp);
        }
    }
}
void printFileA(FILE *f,stringT *strings,int numberOfStrings){
    fprintf(f,"%d",numberOfStrings);
    for(int i=0;i<numberOfStrings;i++){
        fprintf(f,"\n%s",strings[i].string);
    }
}
//SECOND VERSION
char **loadFileB(FILE *f,int *numberOfStrings){
    fscanf(f,"%d%*c",numberOfStrings);
    char **matrix = (char **) malloc(*numberOfStrings * sizeof(char *));
    char string[DIM];
    for(int i=0;i<*numberOfStrings;i++){
        fscanf(f,"%s",string);
	matrix[i] = strdup(string);
    }
    return matrix;
}
void sortStringsB(char **matrix,int numberOfStrings){
    for(int i=0;i<numberOfStrings-1;i++){
        int min = i;
        for(int j=i+1;j<numberOfStrings;j++){
            if(strcmp(matrix[j],matrix[min]) < 0)
              min = j;
        }
        if(min != i){
            char *temp = matrix[i];
            matrix[i] = matrix[min];
            matrix[min] = temp;
        }
    }
}
void printFileB(FILE *f,char **strings,int numberOfStrings){
    fprintf(f,"%d",numberOfStrings);
    for(int i=0;i<numberOfStrings;i++){
        fprintf(f,"\n%s",strings[i]);
    }
}

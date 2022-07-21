#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 20+1
char **loadFile(FILE *,int *);
int *createDimensionsArray(char **,int);
void generateAcronyms(FILE *,char **,char *,int *,int,int);
int main(int argc,char *argv[])
{
    if(argc != 3){
        fprintf(stdout,"Wrong number of arguments!\n");
        return EXIT_FAILURE;
    }
    int n;
    FILE *f = fopen(argv[1],"r");
    char **strings = loadFile(f,&n);
    char *result = (char *) malloc(n * sizeof(char));
    int *dimensionArray = createDimensionsArray(strings,n);
    FILE *f2 = fopen(argv[2],"w");
    generateAcronyms(f2,strings,result,dimensionArray,0,n);
    fclose(f);
    fclose(f2);
    return 0;
}
char **loadFile(FILE *f,int *n){
    fscanf(f,"%d",n);
    char **strings = (char **) malloc(*n * sizeof(char *));
    char string[DIM];
    for(int i=0;i<*n;i++){
        fscanf(f,"%s",string);
        strings[i] = (char *) malloc((strlen(string)+1) * sizeof(char));
        strcpy(strings[i],string);
    }
    return strings;
}
int *createDimensionsArray(char **strings,int n){
    int *dimensionArray = (int *) malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        dimensionArray[i] = strlen(strings[i]);
    }
    return dimensionArray;
}
void generateAcronyms(FILE *f,char **strings,char *result,int *dimensionArray,int pos,int n){
    if(pos == n){
        fprintf(f,"%s\n",result);
        return;
    }
    for(int i=0;i<dimensionArray[pos];i++){
        result[pos] = strings[pos][i];
        generateAcronyms(f,strings,result,dimensionArray,pos+1,n);
    }
}

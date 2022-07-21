#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 20+1
char ***loadFile(int *,int *);
char **mergeMatrix(char ***,int,int);
void printFile(char **,int);
int main()
{
    int rows,columns;
    char ***matrix = loadFile(&rows,&columns);
    char **array = mergeMatrix(matrix,rows,columns);
    printFile(array,rows*columns);
    return 0;
}
char ***loadFile(int *rows,int *columns){
    FILE *f = fopen("input.txt","r");
    fscanf(f,"%d %d%*c",rows,columns);
    char string[DIM];
    char ***matrix = (char ***) malloc(*rows * sizeof(char **));
    for(int i=0;i<*rows;i++){
        matrix[i] = (char **) malloc(*columns * sizeof(char *));
        for(int j=0;j<*columns;j++){
            fscanf(f,"%s",string);
            matrix[i][j] = strdup(string);
            /*
	    matrix[i][j] = (char *) malloc((strlen(string)+1) * sizeof(char));
            strcpy(matrix[i][j],string);
            */
	}
    }
    fclose(f);
    return matrix;
}
char **mergeMatrix(char ***matrix,int rows,int columns){
    char **array = (char **) malloc(rows * columns * sizeof(char *));
    int *indeces = (int *) calloc(rows,sizeof(int));
    int index = 0;
    while(index < rows*columns){
    	int min = 0;
	    for(int i=1;i<rows;i++){
            if(indeces[i] < columns){
                if(strcmp(matrix[i][indeces[i]],matrix[min][indeces[min]]) < 0){
                    min = i;
                }
            }
	    }
	    array[index++] = strdup(matrix[min][indeces[min]]);
	    /*
	    array[index] = (char *) malloc((strlen(matrix[min][indeces[min]])+1) * sizeof(char));
	    strcpy(array[index],matrix[min][indeces[min]]);
	    index++;
	    */
	    indeces[min]++;
    }
    return array;
}
void printFile(char **array,int numberOfStrings){
    FILE *f = fopen("output.txt","w");
    fprintf(f,"%d",numberOfStrings);
    for(int i=0;i<numberOfStrings;i++){
        fprintf(f,"\n%s",array[i]);
    }
    fclose(f);
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define FILENAME 20+1
#define OFFSET 8
typedef struct tileS tileT;
struct tileS{
    char symbol;
    int flag;
};
tileT **loadSnakes(int *,int *);
void processInformations(tileT **,int,int,int *,int *,int *);
int find(tileT **,int,int,int,int);
int isValid(tileT **,int,int,int,int);
//UTILITY FUNCTION
void printSnakes(tileT **,int,int);
int main()
{
    int rows,columns,numberOfSnakes,minLength,maxLength;
    tileT **snakes = loadSnakes(&rows,&columns);
    processInformations(snakes,rows,columns,&numberOfSnakes,&minLength,&maxLength);
    fprintf(stdout,"\nSnake number = %d\nMin length = %d\nMax length = %d\n",numberOfSnakes,minLength,maxLength);
    //printSnakes(snakes,rows,columns);
    return 0;
}
tileT **loadSnakes(int *rows,int *columns){
    char filename[FILENAME];
    fprintf(stdout,"snakes file => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    fscanf(f,"%d %d\n",rows,columns);
    tileT **snakes = (tileT **) malloc(*rows * sizeof(tileT *));
    for(int i=0;i<*rows;i++){
        snakes[i] = (tileT *) malloc(*columns * sizeof(tileT));
        for(int j=0;j<*columns;j++){
            if(j == *columns-1){
                fscanf(f,"%c%*c",&snakes[i][j].symbol);
            }else{
                fscanf(f,"%c",&snakes[i][j].symbol);
            }
            snakes[i][j].flag = 0;
        }
    }
    return snakes;
}
void printSnakes(tileT **snakes,int rows,int columns){
    fprintf(stdout,"\n");
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            fprintf(stdout,"%c",snakes[i][j].symbol);
        }
        fprintf(stdout,"\n");
    }
    fprintf(stdout,"\n");
}
void processInformations(tileT **snakes,int rows,int columns,int *numberOfSnakes,int *minLength,int *maxLength){
    *minLength = INT_MAX;
    *maxLength = 0;
    *numberOfSnakes = 0;
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(snakes[i][j].symbol == '+'){
                (*numberOfSnakes)++;
                int currentLength = find(snakes,rows,columns,i,j);
                if(currentLength > *maxLength){
                    *maxLength = currentLength;
                }
                if(currentLength < *minLength){
                    *minLength = currentLength;
                }
            }
        }
    }
}
int find(tileT **snakes,int rows,int columns,int i,int j){
    int xOffset[OFFSET] = {0,1,0,-1,1,1,-1,-1};
    int yOffset[OFFSET] = {-1,0,1,0,-1,1,1,-1};
    int currentLength = 1;
    int flag = 1;
    while(flag == 1){
        flag = 0;
        for(int k=0;k<OFFSET;k++){
            if(isValid(snakes,i+xOffset[k],j+yOffset[k],rows,columns) == 1){
                currentLength++;
                i+=xOffset[k];
                j+=yOffset[k];
                snakes[i][j].flag = 1;
                flag = 1;
                break;
            }
        }
    }
    return currentLength;
}
int isValid(tileT **snakes,int i,int j,int rows,int columns){
    if(i < 0 || j < 0 || i >= rows || j >= columns)
        return 0;
    if(snakes[i][j].flag == 1)
        return 0;
    if(snakes[i][j].symbol != '*')
        return 0;
    return 1;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define FILENAME 20+1
#define ANSWER 3+1
char **generateMap(int *,int *,int);
void scanMap(char **,int,int,int);
void findRegion(char **,int,int,int,int,char,int);
int isValid(char **,int,int,int,int);
//UTILITY FUNCTION
void printMap(char **,int,int);
int main()
{
    srand(time(0));
    int rows,columns,mode,mode2;
    char answer[ANSWER];
    do{
        fprintf(stdout,"\n1.Random mode\n2.File mode\n=> ");
        fscanf(stdin,"%d",&mode);
        fprintf(stdout,"\n1.Normal mode\n2.Strict mode\n=> ");
        fscanf(stdin,"%d",&mode2);
        fprintf(stdout,"\n");
        char **map = generateMap(&rows,&columns,mode);
        printMap(map,rows,columns);
        scanMap(map,rows,columns,mode2);
        printMap(map,rows,columns);
        fprintf(stdout,"\nContinue? ");
        fscanf(stdin,"%s",answer);
    }while(strcmp(answer,"YES") == 0 || strcmp(answer,"Yes") == 0 || strcmp(answer,"yes") == 0);
    return 0;
}
char **generateMap(int *rows,int *columns,int mode){
    FILE *f;
    if(mode == 1){
        *rows = 5 + rand()%16;
        *columns = 5 + rand()%16;
    }else{
        char filename[FILENAME];
        fprintf(stdout,"map filename => ");
        fscanf(stdin,"%s",filename);
        fprintf(stdout,"\n");
        f = fopen(filename,"r");
        fscanf(f,"%d %d%*c",rows,columns);
    }
    char **map = (char **) malloc(*rows * sizeof(char *));
    for(int i=0;i<*rows;i++){
        map[i] = (char *) malloc(*columns * sizeof(char));
        for(int j=0;j<*columns;j++){
            if(mode == 1){
                if(rand()%3 == 0)
                    map[i][j] = 'X';
                else
                    map[i][j] = 'O';
            }else{
                fscanf(f,"%c",&map[i][j]);
            }
        }
        if(mode == 2)
            fscanf(f,"%*c");
    }
    if(mode == 2)
        fclose(f);
    return map;
}
void scanMap(char **map,int rows,int columns,int mode){
    char counter = '1';
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(map[i][j] == 'O'){
                findRegion(map,rows,columns,i,j,counter,mode);
                counter++;
            }
        }
    }
}
void findRegion(char **map,int rows,int columns,int i,int j,char counter,int mode){
    if(isValid(map,rows,columns,i,j) == 0)
        return;
    map[i][j] = counter;
    if(mode == 2){
        findRegion(map,rows,columns,i-1,j-1,counter,mode);
        findRegion(map,rows,columns,i-1,j+1,counter,mode);
        findRegion(map,rows,columns,i+1,j-1,counter,mode);
        findRegion(map,rows,columns,i+1,j+1,counter,mode);
    }
    findRegion(map,rows,columns,i-1,j,counter,mode);
    findRegion(map,rows,columns,i,j-1,counter,mode);
    findRegion(map,rows,columns,i,j+1,counter,mode);
    findRegion(map,rows,columns,i+1,j,counter,mode);
    return;
}
int isValid(char **map,int rows,int columns,int i,int j){
    if(i < 0 || i >= rows || j < 0 || j >= columns || map[i][j] != 'O')
        return 0;
    return 1;
}
//UTILITY FUNCTION
void printMap(char **map,int rows,int columns){
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            fprintf(stdout,"%c",map[i][j]);
        }
        fprintf(stdout,"\n");
    }
    fprintf(stdout,"\n");
}

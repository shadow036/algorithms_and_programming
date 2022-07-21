#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define OFFSET 4
char **loadMatrix(char *,int *,int *);
void findStartingPosition(char **,int,int,int *,int *);
void findMaze(char **,int,int,int,int,char);
void findMaze2(char **,int,int,int,int,char);
void findBestMaze(char **,char **,int,int,int,int,char,int *,int);
int isValid(char **,int,int,int,int);
void printMatrix(char **,int,int);
int main(int argc,char *argv[])
{
    /*
    if(argc != 2){
        fprintf(stderr,"Wrong number of parameters!\n");
        return EXIT_FAILURE;
    }*/
    int rows,columns,startingRow,startingColumn;
    //char **matrix = loadMatrix(argv[1],&rows,&columns);
    char **matrix = loadMatrix("maze.txt",&rows,&columns);
    printMatrix(matrix,rows,columns);
    fprintf(stdout,"\n");
    findStartingPosition(matrix,rows,columns,&startingRow,&startingColumn);
    /*FIND ALL POSSIBLE MAZES*/
    //findMaze(matrix,rows,columns,startingRow,startingColumn,'A');
    //findMaze2(matrix,rows,columns,startingRow,startingColumn,'A');
    /*FIND BEST MAZE*/
    char **best = (char **) malloc(rows * sizeof(char *));
    for(int i=0;i<rows;i++){
        best[i] = (char *) malloc(columns * sizeof(char));
        for(int j=0;j<columns;j++){
            best[i][j] = matrix[i][j];
        }
    }
    int min = INT_MAX;
    int count = 0;
    findBestMaze(matrix,best,rows,columns,startingRow,startingColumn,'A',&min,count);
    fprintf(stdout,"\nBEST PATH:\n");
    printMatrix(best,rows,columns);
    return 0;
}
char **loadMatrix(char *filename,int *rows,int *columns){
    FILE *f = fopen(filename,"r");
    if(f == NULL)
        return EXIT_FAILURE;
    fscanf(f,"%d %d%*c",rows,columns);
    char **matrix = (char **) malloc(*rows * sizeof(char *));
    for(int i=0;i<*rows;i++)
        matrix[i] = (char *) malloc(*columns * sizeof(char));
    for(int i=0;i<*rows;i++){
        for(int j=0;j<*columns;j++){
            fscanf(f,"%c",&matrix[i][j]);
        }
        fscanf(f,"%*c");
    }
    fclose(f);
    return matrix;
}
void findStartingPosition(char **matrix,int rows,int columns,int *startingRow,int *startingColumn){
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(matrix[i][j] == '@'){
                *startingRow = i;
                *startingColumn = j;
                return;
            }
        }
    }
}
void findMaze(char **matrix,int rows,int columns,int x,int y,char counter){
    if(matrix[x][y] == '#'){
            printMatrix(matrix,rows,columns);
            fprintf(stdout,"\n");
            return;
    }
    if(matrix[x][y] != '@')
        matrix[x][y] = counter++;
    int xOffset[OFFSET] = {-1,0,1,0};
    int yOffset[OFFSET] = {0,-1,0,1};
    for(int k=0;k<OFFSET;k++){
        if(isValid(matrix,rows,columns,x+xOffset[k],y+yOffset[k]) == 1)
            findMaze(matrix,rows,columns,x+xOffset[k],y+yOffset[k],counter);
    }
    matrix[x][y] = ' ';
    return;
}
void findMaze2(char **matrix,int rows,int columns,int x,int y,char counter){
    if(matrix[x][y] != '@')
        matrix[x][y] = counter++;
    int xOffset[OFFSET] = {-1,0,1,0};
    int yOffset[OFFSET] = {0,-1,0,1};
    for(int k=0;k<OFFSET;k++){
        if(isValid(matrix,rows,columns,x+xOffset[k],y+yOffset[k]) == 1){
            if(matrix[x+xOffset[k]][y+yOffset[k]] == '#'){
                printMatrix(matrix,rows,columns);
                matrix[x][y] = ' ';
                fprintf(stdout,"\n");
                return;
            }
            findMaze2(matrix,rows,columns,x+xOffset[k],y+yOffset[k],counter);
        }
    }
    matrix[x][y] = ' ';
    return;
}
void findBestMaze(char **matrix,char **best,int rows,int columns,int x,int y,char counter,int *min,int count){
    if(matrix[x][y] == '#'){
            printMatrix(matrix,rows,columns);
            if(count < *min){
                *min = count;
                for(int i=0;i<rows;i++){
                    for(int j=0;j<columns;j++){
                        best[i][j] = matrix[i][j];
                    }
                }
            }
            fprintf(stdout,"Length: %d\n\n",count);
            return;
    }
    if(matrix[x][y] != '@')
        matrix[x][y] = counter++;
    int xOffset[OFFSET] = {-1,0,1,0};
    int yOffset[OFFSET] = {0,-1,0,1};
    for(int k=0;k<OFFSET;k++){
        if(isValid(matrix,rows,columns,x+xOffset[k],y+yOffset[k]) == 1)
            findBestMaze(matrix,best,rows,columns,x+xOffset[k],y+yOffset[k],counter,min,count+1);
    }
    matrix[x][y] = ' ';
    return;
}
int isValid(char **matrix,int rows,int columns,int x,int y){
    if(x < 0 || x >= rows || y < 0 || y >= columns)
        return 0;
    if(matrix[x][y] != ' ' && matrix[x][y] != '#')
        return 0;
    return 1;
}
void printMatrix(char **matrix,int rows,int columns){
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            fprintf(stdout,"%c",matrix[i][j]);
        }
        fprintf(stdout,"\n");
    }
}

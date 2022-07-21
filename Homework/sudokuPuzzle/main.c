#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int **loadSudoku();
void printSudoku(int **,int);
int solve(int **,int,int,int);
int validate(int **,int);
int main()
{
    int size;
    int **sudoku = loadSudoku(&size);
    printSudoku(sudoku,size);
    fprintf(stdout,"\n");
    solve(sudoku,size,0,0);
    printSudoku(sudoku,size);
    return 0;
}
int **loadSudoku(int *size){
    FILE *f = fopen("sudoku.txt","r");
    int s = 0;
    while(fscanf(f,"%*d") != EOF)
        s++;
    int *sudokuArray = (int *) malloc(s * sizeof(int));
    *size = sqrt(s);
    int **sudoku = (int **) malloc(*size * sizeof(int *));
    for(int i=0;i<*size;i++)
        sudoku[i] = (int *) malloc(*size * sizeof(int));
    fclose(f);
    f = fopen("sudoku.txt","r");
    int index=0;
    while(fscanf(f,"%d",sudokuArray+index) != EOF)
        index++;
    int k=0;
    for(int i=0;i<*size;i++){
        for(int j=0;j<*size;j++){
            sudoku[i][j] = sudokuArray[k++];
        }
    }
    return sudoku;
}
void printSudoku(int **sudoku,int size){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            fprintf(stdout,"%d ",sudoku[i][j]);
        }
        fprintf(stdout,"\n");
    }
}
int solve(int **sudoku,int size,int x,int y){
    if(x == size){
        if(validate(sudoku,size) == 1)
            return 1;
        else
            return 0;
    }
    if(sudoku[x][y] != 0){
        if(y != size-1){
            if(solve(sudoku,size,x,y+1) == 1)
                return 1;
            else
                return 0;
        }else{
            if(solve(sudoku,size,x+1,0) == 1)
                return 1;
            else
                return 0;
        }
    }else{
        for(int i=1;i<=size;i++){
            sudoku[x][y] = i;
            if(y != size-1){
                if(solve(sudoku,size,x,y+1) == 1)
                    return 1;
            }else{
                if(solve(sudoku,size,x+1,0) == 1)
                    return 1;
            }
        }
        sudoku[x][y] = 0;
        return 0;
    }
}
int validate(int **sudoku,int size){
    for(int x=0;x<size;x++){    //CHECK ROWS
        int *used = (int *) calloc(size,sizeof(int));
        for(int j=0;j<size;j++)
            used[sudoku[x][j]-1]++;
        for(int k=0;k<size;k++){
            if(used[k] == 0)
                return 0;
        }
    }
    for(int y=0;y<size;y++){    //CHECK COLUMNS
        int *used = (int *) calloc(size,sizeof(int));
        for(int i=0;i<size;i++)
            used[sudoku[i][y]-1]++;
        for(int k=0;k<size;k++){
            if(used[k] == 0)
                return 0;
        }
    }
    int subGridSize = sqrt(size);   //CHECK SUB-GRIDS
    for(int i=0;i<=size-subGridSize;i+=subGridSize){
        for(int j=0;j<=size-subGridSize;j+=subGridSize){
            int *used = (int *) calloc(size,sizeof(int));
            for(int i2=i;i2<i+subGridSize;i2++){
                for(int j2=j;j2<j+subGridSize;j2++){
                    used[sudoku[i2][j2]-1]++;
                }
            }
            for(int k=0;k<size;k++){
                if(used[k] == 0)
                    return 0;
            }
        }
    }
    return 1;
}

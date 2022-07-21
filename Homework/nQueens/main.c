#include <stdio.h>
#include <stdlib.h>
int **generateChessboard(int *);
void printChessboard(int **,int);
int solve(int **,int,int);
int isValid(int **,int,int,int);
int main()
{
    int n;
    int **chessboard = generateChessboard(&n);
    printChessboard(chessboard,n);
    if(solve(chessboard,n,0) == 1)
        printChessboard(chessboard,n);
    else
        fprintf(stdout,"There is no solution!\n");
    return 0;
}
int **generateChessboard(int *n){
    fprintf(stdout,"chessboard size => ");
    fscanf(stdin,"%d",n);
    int **chessboard = (int **) malloc(*n * sizeof(int *));
    for(int i=0;i<*n;i++){
        chessboard[i] = (int *) malloc(*n * sizeof(int));
        for(int j=0;j<*n;j++)
            chessboard[i][j] = 0;
    }
    return chessboard;
}
void printChessboard(int **chessboard,int n){
    fprintf(stdout,"\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            fprintf(stdout,"%d ",chessboard[i][j]);
        fprintf(stdout,"\n");
    }
}
int solve(int **chessboard,int n,int column){
    if(column == n)
        return 1;
    for(int i=0;i<n;i++){
        if(isValid(chessboard,n,i,column) == 1){
            chessboard[i][column] = 1;
            if(solve(chessboard,n,column+1) == 1)
                return 1;
            chessboard[i][column] = 0;
        }
    }
    return 0;
}
int isValid(int **chessboard,int n,int x,int y){
    //CHECK ROW
    for(int j=0;j<n;j++){
        if(chessboard[x][j] == 1)
            return 0;
    }
    //CHECK COLUMN
    for(int i=0;i<n;i++){
        if(chessboard[i][y] == 1)
            return 0;
    }
    //CHECK DIAGONAL
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i+j == x+y && chessboard[i][j] == 1)
                return 0;
        }
    }
    //CHECK ANTI-DIAGONAL
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i-j == x-y && chessboard[i][j] == 1)
                return 0;
        }
    }
    return 1;
}

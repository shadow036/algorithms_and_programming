#include <stdio.h>
#include <stdlib.h>
#define DIM 8
int **generateChessboard(int *);
void printChessboard(int **,int);
int solve(int **,int,int,int,int);
int isValid(int **,int,int,int);
int main()
{
    int n;
    int **chessboard = generateChessboard(&n);
    printChessboard(chessboard,n);
    int xStartingPosition,yStartingPosition;
    fprintf(stdout,"\nxStartingPosition yStartingPosition => ");
    fscanf(stdin,"%d %d",&xStartingPosition,&yStartingPosition);
    chessboard[xStartingPosition][yStartingPosition] = 1;
    if(solve(chessboard,n,xStartingPosition,yStartingPosition,2) == 1)
        printChessboard(chessboard,n);
    else
        fprintf(stdout,"\nThere is no solution!\n");
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
            fprintf(stdout,"%2d ",chessboard[i][j]);
        fprintf(stdout,"\n");
    }
}
int solve(int **chessboard,int n,int x,int y,int move){
    if(move == (n*n)+1)
        return 1;
    int xOffset[DIM] = {-2,-1,1,2,2,1,-1,-2};
    int yOffset[DIM] = {-1,-2,-2,-1,1,2,2,1};
    for(int i=0;i<DIM;i++){
        if(isValid(chessboard,n,x+xOffset[i],y+yOffset[i]) == 1){
            chessboard[x+xOffset[i]][y+yOffset[i]] = move;
            if(solve(chessboard,n,x+xOffset[i],y+yOffset[i],move+1) == 1)
                return 1;
            chessboard[x+xOffset[i]][y+yOffset[i]] = 0;
        }
    }
    return 0;
}
int isValid(int **chessboard,int n,int x,int y){
    if(x < 0 || x >= n || y < 0 || y >= n)
        return 0;
    if(chessboard[x][y] != 0)
        return 0;
    return 1;
}

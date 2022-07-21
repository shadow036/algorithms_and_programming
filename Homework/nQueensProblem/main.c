#include <stdio.h>
#include <stdlib.h>
int **generateChessboard(int *);
void printChessboard(int **,int);
int solve(int **,int,int);
int isValid(int **,int,int,int);
int main(int argc,char *argv[])
{
    int n;
    int **chessboard = generateChessboard(&n);
    printChessboard(chessboard,n);
    if(solve(chessboard,n,0) == 1)
        printChessboard(chessboard,n);
    else
        fprintf(stdout,"\nThere is no solution!\n");
    return 0;
}
int **generateChessboard(int *n){
    fprintf(stdout,"Chessboard size => ");
    fscanf(stdin,"%d",n);
    int **chessboard = (int **) malloc(*n * sizeof(int *));
    for(int i=0;i<*n;i++)
        chessboard[i] = (int *) calloc(*n,sizeof(int));
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
int solve(int **chessboard,int n,int pos){
    if(pos == n)
        return 1;
    for(int i=0;i<n;i++){
        if(isValid(chessboard,i,pos,n) == 1){
            chessboard[i][pos] = 1;
            if(solve(chessboard,n,pos+1) == 1)
                return 1;
            chessboard[i][pos] = 0;
        }
    }
    return 0;
}
int isValid(int **chessboard,int x,int y,int n){
    for(int i=0;i<n;i++){   //CHECK COLUMN
        if(chessboard[i][y] == 1)
            return 0;
    }
    for(int j=0;j<n;j++){   //CHECK ROW
        if(chessboard[x][j] == 1)
            return 0;
    }
    for(int i=0;i<n;i++){   //CHECK ANTI-DIAGONAL
        for(int j=0;j<n;j++){
            if((i+j) == (x+y) && chessboard[i][j] == 1)
                return 0;
        }
    }
    for(int i=0;i<n;i++){   //CHECK DIAGONAL
        for(int j=0;j<n;j++){
            if((i-j) == (x-y) && chessboard[i][j] == 1)
                return 0;
        }
    }
    return 1;
}

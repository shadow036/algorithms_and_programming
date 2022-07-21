#include <stdio.h>
#include <stdlib.h>
#define N 10
int **generateChessboard(int,int);
void solve(int **,int,int,int,int);
int isValid(int,int);
int evaluateChessboard(int **);
void printChessboard(int **);
int main(){
	int x,y,n;
	int moves = 0;
	fscanf(stdin,"%d %d %d",&x,&y,&n);
	fprintf(stdout,"\n");
	int **chessboard = generateChessboard(x-1,y-1);
	printChessboard(chessboard);
	solve(chessboard,x-1,y-1,n,moves);
	printChessboard(chessboard);
    fprintf(stdout,"%d\n",evaluateChessboard(chessboard));
}
int **generateChessboard(int x,int y){
    int **chessboard = (int **) malloc(N * sizeof(int *));
    for(int i=0;i<N;i++)
        chessboard[i] = (int *) malloc(N * sizeof(int));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(i == x && j == y)
                chessboard[i][j] = -1;
            else
                chessboard[i][j] = 0;
        }
    }
    return chessboard;
}
void solve(int **chessboard,int x,int y,int n,int moves){
    if(moves == n+1)
        return;
    int xPosition[] = {-2,-1,1,2,2,1,-1,-2};
    int yPosition[] = {-1,-2,-2,-1,1,2,2,1};
    if(isValid(x,y) == 1){
        chessboard[x][y]++;
        if(moves != n)
            chessboard[x][y] = 0;
        for(int k=0;k<8;k++){
            solve(chessboard,x+xPosition[k],y+yPosition[k],n,moves+1);
        }
    }
    return;
}
int isValid(int x,int y){
    if(x >= 0 && x < N && y >= 0 && y < N)
        return 1;
    return 0;
}
int evaluateChessboard(int **chessboard){
    int counter = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(chessboard[i][j] > 0)
                counter++;
        }
    }
    return counter;
}
void printChessboard(int **chessboard){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fprintf(stdout,"%3d ",chessboard[i][j]);
        }
        fprintf(stdout,"\n");
    }
    fprintf(stdout,"\n");
}

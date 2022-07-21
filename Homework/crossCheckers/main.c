#include <stdio.h>
#include <stdlib.h>
#define DIM 7
#define MOVES 31
#define OFFSET 4
typedef struct moveS moveT;
struct moveS{
    int initialX;
    int initialY;
    int finalX;
    int finalY;
};
char **generateChessboard();
void printChessboard(char **);
int findSolution(char **,moveT *,int);
int isValid(char **,int,int,int,int);
void printMoves(moveT *);
int main()
{
    char **chessboard = generateChessboard();
    printChessboard(chessboard);
    moveT *moves = (moveT *) malloc(MOVES * sizeof(moveT));
    if(findSolution(chessboard,moves,0) == 1)
        printMoves(moves);
    else
        fprintf(stdout,"There is no solution!\n");
    return 0;
}
char **generateChessboard(){
    char **chessboard = (char **) malloc(DIM * sizeof(char *));
    for(int i=0;i<DIM;i++)
        chessboard[i] = (char *) malloc(DIM * sizeof(char));
    for(int i=0;i<DIM;i++){
        for(int j=0;j<DIM;j++){
            if((i < 2 && j < 2) || (i < 2 && j > DIM - 1 - 2) || (i > DIM - 1 - 2 && j < 2) || (i > DIM - 1 - 2 && j > DIM - 1 - 2))
                chessboard[i][j] = ' ';
            else if(i == DIM/2 && j == DIM/2)
                chessboard[i][j] = 'X';
            else
                chessboard[i][j] = 'O';
        }
    }
    return chessboard;
}
void printChessboard(char **chessboard){
    for(int i=0;i<DIM;i++){
        for(int j=0;j<DIM;j++){
            fprintf(stdout,"%c",chessboard[i][j]);
        }
        fprintf(stdout,"\n");
    }
    fprintf(stdout,"\n");
}
int findSolution(char **chessboard,moveT *moves,int pos){
    if(pos == MOVES)
        return 1;
    int xOffset[] = {-1,0,1,0};
    int yOffset[] = {0,-1,0,1};
    for(int i=0;i<DIM;i++){
        for(int j=0;j<DIM;j++){
            if(chessboard[i][j] == 'O'){
                for(int k=0;k<OFFSET;k++){
                    if(isValid(chessboard,i,j,xOffset[k],yOffset[k]) == 1){
                        chessboard[i][j] = 'X';
                        chessboard[i+xOffset[k]][j+yOffset[k]] = 'X';
                        chessboard[i+2*xOffset[k]][j+2*yOffset[k]] = 'O';
                        moves[pos].initialX = i;
                        moves[pos].initialY = j;
                        moves[pos].finalX = i+2*xOffset[k];
                        moves[pos].finalY = j+2*yOffset[k];
                        if(findSolution(chessboard,moves,pos+1) == 1){
                            return 1;
                        }
                        chessboard[i][j] = 'O';
                        chessboard[i+xOffset[k]][j+yOffset[k]] = 'O';
                        chessboard[i+2*xOffset[k]][j+2*yOffset[k]] = 'X';
                        /*moves[pos].initialX = 0;
                        moves[pos].initialY = 0;
                        moves[pos].finalX = 0;
                        moves[pos].finalY = 0;*/
                    }
                }
            }
        }
    }
    return 0;
}
int isValid(char **chessboard,int x,int y,int xOffset,int yOffset){
    if(x+xOffset < 0 || x+xOffset >= DIM || y+yOffset < 0 || y+yOffset >= DIM)
        return 0;
    if(x+2*xOffset < 0 || x+2*xOffset >= DIM || y+2*yOffset < 0 || y+2*yOffset >= DIM)
        return 0;
    if(chessboard[x+xOffset][y+yOffset] != 'O' || chessboard[x+2*xOffset][y+2*yOffset] != 'X')
        return 0;
    return 1;
}
void printMoves(moveT *moves){
    for(int i=0;i<MOVES;i++)
        fprintf(stdout,"From (%d,%d) to (%d,%d)\n",moves[i].initialX,moves[i].initialY,moves[i].finalX,moves[i].finalY);
}

#include <stdio.h>
#include <stdlib.h>
int **generateSquare(int);
int *generateUsed(int);
int solve(int **,int *,int,int,int);
int validate(int **,int);
void writeFile(char *,int **,int);
int main(int argc,char *argv[])
{
    if(argc != 3){
        fprintf(stderr,"Wrong number of parameters!\n");
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    int **square = generateSquare(n);
    int *used = generateUsed(n);
    if(solve(square,used,n,0,0) == 0){
        fprintf(stdout,"There is no solution!\n");
    }else{
        fprintf(stdout,"Solution written in file \"%s\" !\n",argv[2]);
        writeFile(argv[2],square,n);
    }
    return 0;
}
int **generateSquare(int n){
    int **square = (int **) malloc(n * sizeof(int *));
    for(int i=0;i<n;i++)
        square[i] = (int *) calloc(n,sizeof(int));
    return square;
}
int *generateUsed(int n){
    int *used = (int *) calloc(n*n,sizeof(int));
    return used;
}
int solve(int **square,int *used,int n,int x,int y){
    if(x == n){
        if(validate(square,n) == 1)
            return 1;
        return 0;
    }
    for(int i=0;i<n*n;i++){
        if(used[i] == 0){
            used[i] = 1;
            square[x][y] = i+1;
            if(y == n-1){
                if(solve(square,used,n,x+1,0) == 1)
                    return 1;
            }else{
                if(solve(square,used,n,x,y+1) == 1)
                    return 1;
            }
            used[i] = 0;
        }
    }
    return 0;
}
int validate(int **square,int n){
    int expectedResult;
    for(int r=0;r<n;r++){   //CHECK ROWS
        int currentResult = 0;
        for(int j=0;j<n;j++)
            currentResult+=square[r][j];
        if(r == 0)
            expectedResult = currentResult;
        else if(currentResult != expectedResult)
            return 0;
    }
    for(int c=0;c<n;c++){   //CHECK COLUMNS
        int currentResult = 0;
        for(int i=0;i<n;i++)
            currentResult+=square[i][c];
        if(currentResult != expectedResult)
            return 0;
    }
    int currentResult = 0;
    for(int d=0;d<n;d++)   //CHECK DIAGONAL
        currentResult+=square[d][d];
    if(currentResult != expectedResult)
        return 0;
    currentResult = 0;
    for(int i=0;i<n;i++){   //CHECK ANTI-DIAGONAL
        for(int j=0;j<n;j++){
            if(i+j == n-1)
                currentResult+=square[i][j];
        }
    }
    if(currentResult != expectedResult)
        return 0;
    return 1;
}
void writeFile(char *filename,int **square,int n){
    FILE *f = fopen(filename,"w");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fprintf(f,"%d ",square[i][j]);
        }
        fprintf(f,"\n");
    }
}

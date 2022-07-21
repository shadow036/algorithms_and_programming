#include <stdio.h>
#include <stdlib.h>
char **loadMatrix(char *,int *);
void printMatrix(char **,int);
int check(char **,int);
int validateRowsAndColumns(char **,int);
int validate(char **,int);
int solve(char **,char **,int **,int **,int,int,int);
char **generateTemporaryMatrix(char **,int);
int **generateFlagMatrix(int,char **);
int **generateSecondFlagMatrix(int,char **);
int main(int argc,char *argv[])
{
    int size;
    char **matrix = loadMatrix("futoshiki.txt",&size);
    printMatrix(matrix,size);
    if(check(matrix,size) == 1){
        if(validate(matrix,size) == 0 || validateRowsAndColumns(matrix,size) == 0)
            fprintf(stdout,"Wrong Configuration.\n");
        else
            fprintf(stdout,"Correct Configuration.\n");
    }else{
        int **flagMatrix = generateFlagMatrix(size,matrix);
        int **secondFlagMatrix = generateSecondFlagMatrix(size,matrix);
        char **temporaryMatrix = generateTemporaryMatrix(matrix,size);
        if(solve(matrix,temporaryMatrix,flagMatrix,secondFlagMatrix,size,0,0) == 1)
            printMatrix(temporaryMatrix,size);
        else
            fprintf(stdout,"No solution found!\n");
    }
    return 0;
}
char **loadMatrix(char *filename,int *size){
    FILE *f = fopen(filename,"r");
    fscanf(f,"%d%*c",size);
    *size = ((*size)*2)-1;
    char **matrix = (char **) malloc(*size * sizeof(char *));
    for(int i=0;i<*size;i++)
        matrix[i] = (char *) malloc(*size * sizeof(char));
    for(int i=0;i<*size;i++){
        for(int j=0;j<*size;j++){
            fscanf(f,"%c%*c",&matrix[i][j]);
        }
    }
    return matrix;
}
void printMatrix(char **matrix,int size){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++)
            fprintf(stdout,"%c ",matrix[i][j]);
        fprintf(stdout,"\n");
    }
    fprintf(stdout,"\n");
}
int check(char **matrix,int size){
    for(int i=0;i<size;i+=2){
        for(int j=0;j<size;j+=2){
            if(matrix[i][j] == '0')
                return 2;
        }
    }
    return 1;
}
int validateRowsAndColumns(char **matrix,int size){
    for(int i=0;i<size;i+=2){   //CHECK ROWS
        int *used = (int *) calloc((size+1)/2,sizeof(int));
        for(int j=0;j<size;j+=2)
            used[matrix[i][j] - '0' - 1]++;
        for(int k=0;k<(size+1)/2;k++){
            if(used[k] != 1)
                return 0;
        }
    }
    for(int i=0;i<size;i+=2){   //CHECK COLUMNS
        int *used = (int *) calloc((size+1)/2,sizeof(int));
        for(int j=0;j<size;j+=2)
            used[matrix[j][i] - '0' - 1]++;
        for(int k=0;k<(size+1)/2;k++){
            if(used[k] != 1)
                return 0;
        }
    }
    return 1;
}
int validate(char **matrix,int size){
    for(int i=0;i<size;i++){   //CHECK CONSTRAINTS
        for(int j=0;j<size;j++){
            switch(matrix[i][j]){
                case '>':
                    if(matrix[i][j-1] <= matrix[i][j+1])    //even in ascii the comparison should give the same result
                        return 0;
                    break;
                case '<':
                    if(matrix[i][j-1] >= matrix[i][j+1])
                        return 0;
                    break;
                case '^':
                    if(matrix[i-1][j] >= matrix[i+1][j])
                        return 0;
                    break;
                case 'V':
                    if(matrix[i-1][j] <= matrix[i+1][j])
                        return 0;
                    break;
                default:
                    break;
            }
        }
    }
    return 1;
}
int solve(char **matrix,char **temporaryMatrix,int **flagMatrix,int **secondFlagMatrix,int size,int x,int y){
    if(x >= size){
        if(validate(temporaryMatrix,size) == 1)
            return 1;
        else
            return 0;
    }
    if(matrix[x][y] == '0'){
        for(char c='1';c<=(size+1)/2 + '0';c++){
            if(flagMatrix[x][c - '0' - 1] == 0 && secondFlagMatrix[c - '0' - 1][y] == 0){
                flagMatrix[x][c - '0' - 1] = 1;
                secondFlagMatrix[c - '0' - 1][y] = 1;
                temporaryMatrix[x][y] = c;
                if(y+2 >= size){
                    if(solve(matrix,temporaryMatrix,flagMatrix,secondFlagMatrix,size,x+2,0) == 1)
                        return 1;
                    flagMatrix[x][c - '0' - 1] = 0;
                    secondFlagMatrix[c - '0' - 1][y] = 0;
                }else{
                    if(solve(matrix,temporaryMatrix,flagMatrix,secondFlagMatrix,size,x,y+2) == 1)
                        return 1;
                    flagMatrix[x][c - '0' - 1] = 0;
                    secondFlagMatrix[c - '0' - 1][y] = 0;
                }
            }
        }
        return 0;
    }else{
        if(y+2 >= size){
            if(solve(matrix,temporaryMatrix,flagMatrix,secondFlagMatrix,size,x+2,0) == 1)
                return 1;
            else
                return 0;
        }else{
            if(solve(matrix,temporaryMatrix,flagMatrix,secondFlagMatrix,size,x,y+2) == 1)
                return 1;
            else
                return 0;
        }
    }
}
char **generateTemporaryMatrix(char **matrix,int size){
    char **temporaryMatrix = (char **) malloc(size * sizeof(char *));
    for(int i=0;i<size;i++)
        temporaryMatrix[i] = (char *) malloc(size * sizeof(char));
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            temporaryMatrix[i][j] = matrix[i][j];
        }
    }
    return temporaryMatrix;
}
int **generateFlagMatrix(int size,char **matrix){
    int **flagMatrix = (int **) malloc(size * sizeof(int *));
    for(int i=0;i<size;i++)
        flagMatrix[i] = (int *) calloc((size+1)/2,sizeof(int));
    for(int i=0;i<size;i+=2){
        for(int j=0;j<size;j+=2){
            if(matrix[i][j] != '0')
                flagMatrix[i][matrix[i][j] - '0' - 1] = 1;
        }
    }
    return flagMatrix;
}
int **generateSecondFlagMatrix(int size,char **matrix){
    int **secondFlagMatrix = (int **) malloc((size+1)/2 * sizeof(int *));
    for(int i=0;i<(size+1)/2;i++)
        secondFlagMatrix[i] = (int *) calloc(size,sizeof(int));
    for(int i=0;i<size;i+=2){
        for(int j=0;j<size;j+=2){
            if(matrix[i][j] != '0')
                secondFlagMatrix[matrix[i][j] - '0' - 1][j] = 1;
        }
    }
    return secondFlagMatrix;
}

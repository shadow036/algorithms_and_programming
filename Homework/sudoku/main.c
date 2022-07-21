#include <stdio.h>
#include <stdlib.h>
#define FILENAME 20+1
#define BLOCK 3
int **loadSudoku(int *);
int checkSudoku(int **,int);
int main()
{
    int numberOfRowsAndColumns;
    int **sudoku = loadSudoku(&numberOfRowsAndColumns);
    if(checkSudoku(sudoku,numberOfRowsAndColumns) == 1)
        fprintf(stdout,"\nThe sudoku configuration is correct!\n");
    return 0;
}
int **loadSudoku(int *numberOfRowsAndColumns){
    char filename[FILENAME];
    fprintf(stdout,"sudoku filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    fscanf(f,"%d",numberOfRowsAndColumns);
    int **sudoku = (int **) malloc(*numberOfRowsAndColumns * sizeof(int *));
    for(int i=0;i<*numberOfRowsAndColumns;i++){
        sudoku[i] = (int *) malloc(*numberOfRowsAndColumns * sizeof(int));
        for(int j=0;j<*numberOfRowsAndColumns;j++){
            fscanf(f,"%d",&sudoku[i][j]);
        }
    }
    return sudoku;
}
int checkSudoku(int **sudoku,int numberOfRowsAndColumns){
    int flag = 1;
    //check rows
    for(int i=0;i<numberOfRowsAndColumns;i++){
        for(int j=0;j<numberOfRowsAndColumns;j++){
            for(int k=j;k<numberOfRowsAndColumns;k++){
                if(sudoku[i][j] == sudoku[i][k] && j != k){
                    fprintf(stderr,"\nError detected!\nSame value in same row (%d)\n(%d,%d) (%d,%d)\n",i+1,i+1,j+1,i+1,k+1);
                    flag = 0;
                }
                if(sudoku[i][j] < 1 || sudoku[i][j] > 9){
                    fprintf(stderr,"\nError detected!\nWrong value in (%d,%d)!\n",i+1,j+1);
                    flag = 0;
                }
            }
        }
    }
    //check columns
    for(int j=0;j<numberOfRowsAndColumns;j++){
        for(int i=0;i<numberOfRowsAndColumns;i++){
            for(int k=i;k<numberOfRowsAndColumns;k++){
                if(sudoku[i][j] == sudoku[k][j] && i != k){
                    fprintf(stderr,"\nError detected!\nSame value in same column (%d)\n(%d,%d) (%d,%d)\n",j+1,i+1,j+1,k+1,j+1);
                    flag = 0;
                }
            }
        }
    }
    //check block
    for(int i=0;i<numberOfRowsAndColumns;i+=BLOCK){
        for(int j=0;j<numberOfRowsAndColumns;j+=BLOCK){
            for(int i2=i;i2<i+BLOCK;i2++){
                for(int j2=j;j2<j+BLOCK;j2++){
                    for(int i3=i2;i3<i+BLOCK;i3++){
                        for(int j3=j2;j3<j+BLOCK;j3++){
                            if(sudoku[i2][j2] == sudoku[i3][j3] && (i2 != i3 || j2 != j3)){
                                fprintf(stderr,"\nError detected!\nSame value in same block\n(%d,%d) (%d,%d)\n",i2+1,j2+1,i3+1,j3+1);
                                flag = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return flag;
}

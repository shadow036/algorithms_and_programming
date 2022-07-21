#include <stdio.h>
#include <stdlib.h>
#define N 10
typedef struct valueS valueT;
struct valueS{
    int num;
    char element[N];
};
int multiplicationPrinciple(valueT *,char *,int,int,int);
int main()
{
    valueT value[3];
    char solution[3];
    int n=3;
    int pos=0;
    int count=0;
    value[0].num = 4;
    value[0].element[0] = 'A';
    value[0].element[1] = 'B';
    value[0].element[2] = 'C';
    value[0].element[3] = 'D';
    value[1].num = 3;
    value[1].element[0] = 'E';
    value[1].element[1] = 'F';
    value[1].element[2] = 'G';
    value[2].num = 2;
    value[2].element[0] = 'H';
    value[2].element[1] = 'I';
    fprintf(stdout,"Total: %d",multiplicationPrinciple(value,solution,n,pos,count));
    return 0;
}
int multiplicationPrinciple(valueT *value,char *solution,int n,int pos,int count){
    if(pos >= n){
        fprintf(stdout,"{");
        for(int i=0;i<n;i++){
            fprintf(stdout,"%c",solution[i]);
        }
        fprintf(stdout,"}\n");
        return count+1;
    }
    for(int i=0;i<value[pos].num;i++){
        solution[pos] = value[pos].element[i];
        count = multiplicationPrinciple(value,solution,n,pos+1,count);
    }
    return count;
}

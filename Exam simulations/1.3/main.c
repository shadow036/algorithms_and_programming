#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int *loadCashArray(int *);
void showCashes(int *,int *,int *,int *,int *,int,int);
int evaluate(int *,int);
int main()
{
    int numberOfTransactions;
    int difference = INT_MIN;
    int *cash = loadCashArray(&numberOfTransactions);
    int *result = (int *) malloc(numberOfTransactions * sizeof(int));
    int *used = (int *) calloc(numberOfTransactions,sizeof(int));
    int *best = (int *) calloc(numberOfTransactions,sizeof(int));
    fprintf(stdout,"\n");
    showCashes(cash,result,used,&difference,best,0,numberOfTransactions);
    fprintf(stdout,"\nBEST COMBINATION: ");
    for(int i=0;i<numberOfTransactions;i++)
        fprintf(stdout,"%d ",best[i]);
    fprintf(stdout,"\n");
    return 0;
}
int *loadCashArray(int *numberOfTransactions){
    fprintf(stdout,"Number of transactions => ");
    fscanf(stdin,"%d",numberOfTransactions);
    int *cash = (int *) malloc(*numberOfTransactions * sizeof(int));
    fprintf(stdout,"\n");
    for(int i=0;i<*numberOfTransactions;i++){
        fprintf(stdout,"cash #%d: ",i);
        fscanf(stdin,"%d",cash+i);
    }
    return cash;
}
void showCashes(int *cash,int *result,int *used,int *difference,int *best,int pos,int numberOfTransactions){
    if(pos == numberOfTransactions){
        if(evaluate(result,numberOfTransactions) > *difference){
            *difference = evaluate(result,numberOfTransactions);
            for(int i=0;i<numberOfTransactions;i++)
                best[i] = result[i];
        }
        for(int i=0;i<numberOfTransactions;i++){
            fprintf(stdout,"%d ",result[i]);
        }
        fprintf(stdout," DIFFERENCE: %d\n",evaluate(result,numberOfTransactions));
        return;
    }
    for(int i=0;i<numberOfTransactions;i++){
        if(used[i] == 0){
            used[i] = 1;
            result[pos] = cash[i];
            showCashes(cash,result,used,difference,best,pos+1,numberOfTransactions);
            used[i] = 0;
        }
    }
    return;
}
int evaluate(int *result,int numberOfTransactions){
    int min = result[0];
    int max = result[0];
    int temp = result[0];
    for(int i=1;i<numberOfTransactions;i++){
        temp += result[i];
        if(temp > max)
            max = temp;
        if(temp < min)
            min = temp;
    }
    return (max-min);
}

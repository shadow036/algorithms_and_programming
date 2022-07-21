#include "combinatorics.h"
#include <stdio.h>
#include <stdlib.h>

void simpleArrangements(char *input,char *solution,int *used,int n,int k,int pos){
    if(pos >= k){
        fprintf(stdout,"\n{");
        for(int i=0;i<pos;i++){
            if(i < pos-1)
                fprintf(stdout,"%c,",solution[i]);
            else
                fprintf(stdout,"%c",solution[i]);
        }
        fprintf(stdout,"}");
        return;
    }
    for(int i=0;i<n;i++){
        if(used[i] == 0){
            used[i] = 1;
            solution[pos] = input[i];
            simpleArrangements(input,solution,used,n,k,pos+1);
            used[i] = 0;
        }
    }
}
void arrangementsWithRepetitions(char *input,char *solution,int n,int k,int pos){
    if(pos >= k){
        fprintf(stdout,"\n{");
        for(int i=0;i<pos;i++){
            if(i < pos-1)
                fprintf(stdout,"%c,",solution[i]);
            else
                fprintf(stdout,"%c",solution[i]);
        }
        fprintf(stdout,"}");
        return;
    }
    for(int i=0;i<n;i++){
        solution[pos] = input[i];
        arrangementsWithRepetitions(input,solution,n,k,pos+1);
    }
}
void simplePermutations(char *input,char *solution,int *used,int n,int pos){
    simpleArrangements(input,solution,used,n,n,0);
}
void permutationsWithRepetitions(char *input,char *solution,int *repetitions,int n,int pos,int dist){
    if(pos >= n){
        fprintf(stdout,"\n{");
        for(int i=0;i<pos;i++){
            if(i < pos-1)
                fprintf(stdout,"%c,",solution[i]);
            else
                fprintf(stdout,"%c",solution[i]);
        }
        fprintf(stdout,"}");
        return;
    }
    for(int i=0;i<dist;i++){
        if(repetitions[i] > 0){
            repetitions[i]--;
            solution[pos] = input[i];
            permutationsWithRepetitions(input,solution,repetitions,n,pos+1,dist);
            repetitions[i]++;
        }
    }
}
void simpleCombinations(char *input,char *solution,int n,int k,int pos,int start){
    if(pos >= k){
        fprintf(stdout,"\n{");
        for(int i=0;i<pos;i++){
            if(i < pos-1)
                fprintf(stdout,"%c,",solution[i]);
            else
                fprintf(stdout,"%c",solution[i]);
        }
        fprintf(stdout,"}");
        return;
    }
    for(int i=start;i<n;i++){
        solution[pos] = input[i];
        simpleCombinations(input,solution,n,k,pos+1,i+1);
    }
}
void combinationsWithRepetitions(char *input,char *solution,int n,int k,int pos,int start){
    if(pos >= k){
        fprintf(stdout,"\n{");
        for(int i=0;i<pos;i++){
            if(i < pos-1)
                fprintf(stdout,"%c,",solution[i]);
            else
                fprintf(stdout,"%c",solution[i]);
        }
        fprintf(stdout,"}");
        return;
    }
    for(int i=start;i<n;i++){
        solution[pos] = input[i];
        combinationsWithRepetitions(input,solution,n,k,pos+1,i);
    }
}
void powerSet(char *input,char *solution,int n){
    for(int i=0;i<=n;i++)
        simpleCombinations(input,solution,n,i,0,0);
}
void partition(char *input,char *solution,int n,int k,int pos){
    if(pos == n){
        fprintf(stdout,"\n");
        for(int i=0;i<k;i++){
            fprintf(stdout,"{");
            for(int j=0;j<pos;j++){
                if(solution[j] == i){
                    if(j < pos-1)
                        fprintf(stdout,"%c,",input[j]);
                    else
                        fprintf(stdout,"%c",input[j]);
                }
            }
            fprintf(stdout,"} ");
        }
        return;
    }
    for(int i=0;i<k;i++){
        solution[pos] = i;
        partition(input,solution,n,k,pos+1);
    }
}

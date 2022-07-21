#include <stdio.h>
#include <stdlib.h>
void simpleArrangements(char *,char *,int *,int,int,int);
void arrangementsWithRepetitions(char *,char *,int,int,int);
void simplePermutations(char *,char *,int *,int,int);
void permutationsWithRepetitions(char *,char *,int *,int,int,int);
void simpleCombinations(char *,char *,int,int,int,int);
void combinationsWithRepetitions(char *,char *,int,int,int,int);
void powerSet(char *,char *,int);
void powerSetRecursive(char *,char *,int,int,int,int);
void myPartition(char *,int *,int,int);
int main()
{
    int n,k;
    fprintf(stdout,"total # of elements => ");
    fscanf(stdin,"%d%*c",&n);
    fprintf(stdout,"# of elements in each group => ");
    fscanf(stdin,"%d%*c",&k);
    char *values = (char *) malloc(n * sizeof(char));
    char *solution = (char *) malloc(k * sizeof(char));
    for(int i=0;i<n;i++){
        fprintf(stdout,"values[%d] => ",i);
        fscanf(stdin,"%c%*c",values+i);
    }
    //SIMPLE ARRANGEMENTS
    fprintf(stdout,"\nSIMPLE ARRANGEMENTS\n");
    simpleArrangements(values,solution,used,0,k,n);
    //ARRANGEMENTS WITH REPETITIONS
    fprintf(stdout,"\nARRANGEMENTS WITH REPETITIONS\n");
    arrangementsWithRepetitions(values,solution,0,k,n);
    //SIMPLE PERMUTATIONS
    int *used = (int *) calloc(n,sizeof(int));
    fprintf(stdout,"\nSIMPLE PERMUTATIONS\n");
    simplePermutations(values,solution,used,0,n);
    //PERMUTATIONS WITH REPETITIONS
    int *used2 = (int *) calloc(n,sizeof(int));
    for(int i=0;i<n;i++){
        fprintf(stdout,"# repetitions of %c => ",values[i]);
        fscanf(stdin,"%d",used2+i);
    }
    fprintf(stdout,"\nPERMUTATIONS WITH REPETITIONS\n");
    permutationsWithRepetitions(values,solution,used2,0,k,n);
    //SIMPLE COMBINATIONS
    fprintf(stdout,"\nSIMPLE COMBINATIONS\n");
    simpleCombinations(values,solution,0,0,k,n);
    //COMBINATIONS WITH REPETITIONS
    fprintf(stdout,"\nCOMBINATIONS WITH REPETITIONS\n");
    combinationsWithRepetitions(values,solution,0,0,k,n);
    //POWER SET
    fprintf(stdout,"\nPOWER SET\n");
    powerSet(values,solution,n);
    //PARTITION
    int *solution2 = (int *) malloc(n * sizeof(int));
    fprintf(stdout,"\nPARTITION\n");
    myPartition(values,solution2,0,n);
    return 0;
}
void simpleArrangements(char *values,char *solution,int *used,int pos,int k,int n){
    if(pos == k){
        for(int i=0;i<k;i++)
            fprintf(stdout,"%c",solution[i]);
        fprintf(stdout,"\n");
        return;
    }
    for(int i=0;i<n;i++){
        if(used[i] == 0){
            used[i] = 1;
            solution[pos] = values[i];
            simpleArrangements(values,solution,used,pos+1,k,n);
            used[i] = 0;
        }
    }
    return;
}
void arrangementsWithRepetitions(char *values,char *solution,int pos,int k,int n){
    if(pos == k){
        for(int i=0;i<k;i++){
            fprintf(stdout,"%c",solution[i]);
        }
        fprintf(stdout,"\n");
        return;
    }
    for(int i=0;i<n;i++){
        solution[pos] = values[i];
        arrangementsWithRepetitions(values,solution,pos+1,k,n);
    }
    return;
}
void simplePermutations(char *values,char *solution,int *used,int pos,int n){
    if(pos == n){
        for(int i=0;i<n;i++){
            fprintf(stdout,"%c",solution[i]);
        }
        fprintf(stdout,"\n");
        return;
    }
    for(int i=0;i<n;i++){
        if(used[i] == 0){
            used[i] = 1;
            solution[pos] = values[i];
            simplePermutations(values,solution,used,pos+1,n);
            used[i] = 0;
        }
    }
    return;
}
void permutationsWithRepetitions(char *values,char *solution,int *used,int pos,int k,int n){ //?????????????????????????????????
    if(pos == k){
        for(int i=0;i<k;i++){
            fprintf(stdout,"%c",solution[i]);
        }
        fprintf(stdout,"\n");
        return;
    }
    for(int i=0;i<n;i++){
        if(used[i] > 0){
            used[i]--;
            solution[pos] = values[i];
            permutationsWithRepetitions(values,solution,used,pos+1,k,n);
            used[i]++;
        }
    }
    return;
}
void simpleCombinations(char *values,char *solution,int start,int pos,int k,int n){
    if(pos == k){
        for(int i=0;i<k;i++)
            fprintf(stdout,"%c",solution[i]);
        fprintf(stdout,"\n");
        return;
    }
    for(int i=start;i<n;i++){
        solution[pos] = values[i];
        simpleCombinations(values,solution,i+1,pos+1,k,n);
    }
    return;
}
void combinationsWithRepetitions(char *values,char *solution,int start,int pos,int k,int n){
    if(pos == k){
        for(int i=0;i<k;i++)
            fprintf(stdout,"%c",solution[i]);
        fprintf(stdout,"\n");
        return;
    }
    for(int i=start;i<n;i++){
        solution[pos] = values[i];
        combinationsWithRepetitions(values,solution,i,pos+1,k,n);
    }
    return;
}
void powerSet(char *values,char *solution,int k){   //WRAPPER
    for(int i=0;i<=k;i++)
        powerSetRecursive(values,solution,0,0,k,i);
}
void powerSetRecursive(char *values,char *solution,int start,int pos,int k,int n){  //SIMPLE COMBINATIONS
    if(pos == n){
        for(int i=0;i<n;i++)
            fprintf(stdout,"%c",solution[i]);
        fprintf(stdout,"\n");
        return;
    }
    for(int i=start;i<k;i++){
        solution[pos] = values[i];
        powerSetRecursive(values,solution,i+1,pos+1,k,n);
    }
    return;
}
void myPartition(char *values,int *solution,int pos,int n){
    if(pos == n){
        fprintf(stdout,"{");
        for(int i=0;i<n;i++){
            if(solution[i] == 0)
                fprintf(stdout,"%c",values[i]);
        }
        fprintf(stdout,"} -> {");
        for(int i=0;i<n;i++){
            if(solution[i] == 1)
                fprintf(stdout,"%c",values[i]);
        }
        fprintf(stdout,"}\n");
        return;
    }
    for(int i=0;i<2;i++){
        solution[pos] = i;
        myPartition(values,solution,pos+1,n);
    }
    return;
}

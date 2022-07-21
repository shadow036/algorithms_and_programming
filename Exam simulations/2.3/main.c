#include <stdio.h>
#include <stdlib.h>
void aeiou(char *,char *,int,int);
int isValid(char *,int);
int main()
{
    char initialString[] = {'A','E','I','O','U'};
    int n;
    fprintf(stdout,"n => ");
    fscanf(stdin,"%d",&n);
    char *string = (char *) malloc(n * sizeof(char));
    aeiou(initialString,string,0,n);
    return 0;
}
void aeiou(char *initialString,char *string,int pos,int n){
    if(pos == n){
        if(isValid(string,n) == 1){
            for(int i=0;i<n;i++)
                fprintf(stdout,"%c ",string[i]);
            fprintf(stdout,"\n");
        }
        return;
    }
    for(int i=0;i<5;i++){
        string[pos] = initialString[i];
        aeiou(initialString,string,pos+1,n);
    }
    return;
}
int isValid(char *string,int n){
    int *check = (int *) calloc(5,sizeof(int));
    for(int i=0;i<n;i++){
        switch(string[i]){
            case 'A':
                check[0]++;
                break;
            case 'E':
                check[1]++;
                break;
            case 'I':
                check[2]++;
                break;
            case 'O':
                check[3]++;
                break;
            case 'U':
                check[4]++;
                break;
            default:
                fprintf(stdout,"\nNANI\n");
                break;
        }
    }
    for(int i=0;i<5;i++){
        if(check[i] == 0)
            return 0;
    }
    return 1;
}

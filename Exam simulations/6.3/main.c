#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define DIM 5
#define ASCII 256
void generatePassword(char *,int,int);
int validatePassword(char *,int);
int main()
{
    int n;
    fprintf(stdout,"n => ");
    fscanf(stdin,"%d",&n);
    char password[DIM];
    generatePassword(password,0,n);
    return 0;
}
void generatePassword(char *password,int pos,int n){
    if(pos == DIM){
        if(validatePassword(password,n) == 1){
            for(int i=0;i<DIM;i++)
                fprintf(stdout,"%c",password[i]);
            fprintf(stdout,"\n");
        }
        return;
    }
    if(pos <= 2){
        for(int i=65;i<=90;i++){
            password[pos] = (char)i;
            generatePassword(password,pos+1,n);
        }
    }else{
        for(int i=48;i<=57;i++){
            password[pos] = (char)i;
            generatePassword(password,pos+1,n);
        }
    }
    return;
}
int validatePassword(char *password,int n){
    if(isupper(password[0]) == 0 || isupper(password[1]) == 0 || isupper(password[2]) == 0 || isdigit(password[3]) == 0 || isdigit(password[4]) == 0)
        return 0;
    int ascii[ASCII];
    for(int i=0;i<ASCII;i++)
        ascii[i] = 0;
    for(int i=0;i<DIM;i++)
        ascii[(int)password[i]]++;
    for(int i=0;i<ASCII;i++){
        if(ascii[i] > n)
            return 0;
    }
    return 1;
}

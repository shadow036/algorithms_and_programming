#include "implementation.h"
void stringSearch(char *string,int *start,int *length){
    int i=0;
    int currentStart = 0;
    int currentLength = 1;
    while(string[i] != '\0'){
        if(string[i] == string[i+1]){
            currentLength++;
        }else{
            if(currentLength > *length){
                *length = currentLength;
                *start = currentStart;
            }
            currentLength = 1;
            currentStart = i+1;
        }
        i++;
    }
}
void printResults(char *string,int start,int length){
    fprintf(stdout,"\n");
    for(int i=start;i<start+length;i++)
        fprintf(stdout,"%c",string[i]);
    fprintf(stdout,"\nstart = %d\nlength = %d\n",start,length);
}

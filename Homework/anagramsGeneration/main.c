#include <stdio.h>
#include <stdlib.h>
#define DIM 10+1
#define ASCII 69
void findAnagramWithDuplicates(char *,char *,int *,int,int);
void findAnagram(int *,char *,int,int);
int myStrlen(char *);
void getFrequencies(char *,int *);
//UTILITY FUNCTION
void printFrequencies(int *);
int main()
{
    char string[DIM];
    fprintf(stdout,"string => ");
    fscanf(stdin,"%s",string);
    int length = myStrlen(string);
    char *anagram = (char *) calloc(length,sizeof(char));
    int *used = (int *) calloc(length,sizeof(int));
    findAnagramWithDuplicates(string,anagram,used,length,0);
    int frequencies[ASCII];
    getFrequencies(string,frequencies);
    //printFrequencies(frequencies);
    fprintf(stdout,"\n\n");
    findAnagram(frequencies,anagram,length,0);
    return 0;
}
void findAnagramWithDuplicates(char *string,char *anagram,int *used,int stringLength,int pos){
    if(pos >= stringLength){
        fprintf(stdout,"{");
        for(int i=0;i<stringLength;i++){
            fprintf(stdout,"%c",anagram[i]);
        }
        fprintf(stdout,"}\n");
        return;
    }
    for(int i=0;i<stringLength;i++){
        if(used[i] == 0){
            anagram[pos] = string[i];
            used[i] = 1;
            findAnagramWithDuplicates(string,anagram,used,stringLength,pos+1);
            used[i] = 0;
        }
    }
}
void getFrequencies(char *string,int *frequencies){
    for(int i=0;i<ASCII;i++)
        frequencies[i] = 0;
    for(int i=0;string[i] != '\0';i++)
        frequencies[(int)string[i]]++;
}
void findAnagram(int *frequencies,char *anagram,int stringLength,int pos){
    if(pos >= stringLength){
        fprintf(stdout,"{");
        for(int i=0;i<stringLength;i++)
            fprintf(stdout,"%c",anagram[i]);
        fprintf(stdout,"}\n");
        return;
    }
    for(int i=0;i<ASCII;i++){
        if(frequencies[i] > 0){
            anagram[pos] = i;
            frequencies[i]--;
            findAnagram(frequencies,anagram,stringLength,pos+1);
            frequencies[i]++;
        }
    }
    return;
}
int myStrlen(char *string){
    int length = 0;
    while(*string != '\0'){
        length++;
        string++;
    }
    return length;
}
//UTILITY FUNCTION
void printFrequencies(int *frequencies){
    for(int i=0;i<ASCII;i++)
        fprintf(stdout,"%c %d occurences\n",(char)i,(frequencies[i]));
}

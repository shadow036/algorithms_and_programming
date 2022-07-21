#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define FILENAME 20+1
#define POSITIONS 10
#define WORD 20+1
typedef struct wordS wordT;
struct wordS{
    char *word;
    int occurences;
    int positions[POSITIONS];
};
wordT *loadWords(int *);
void generateIndex(wordT *,int);
void myToLower(char *);
//UTILITY FUNCTION
void printAscii();
int main()
{
    int numberOfWords;
    printAscii();
    wordT *words = loadWords(&numberOfWords);
    generateIndex(words,numberOfWords);
    return 0;
}
wordT *loadWords(int *numberOfWords){
    char filename[FILENAME];
    fprintf(stdout,"words filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    fscanf(f,"%d",numberOfWords);
    wordT *words = (wordT *) malloc(*numberOfWords * sizeof(wordT));
    char word[WORD];
    for(int i=0;i<*numberOfWords;i++){
        fscanf(f,"%s",word);
        words[i].word = (char *) malloc((strlen(word)+1) * sizeof(char));
        strcpy(words[i].word,word);
        words[i].occurences = 0;
        for(int j=0;j<POSITIONS;j++)
            words[i].positions[j] = 0;
    }
    return words;
}
void generateIndex(wordT *words,int numberOfWords){
    char filename[FILENAME];
    fprintf(stdout,"text filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    char word[WORD];
    int position = 1;
    while(fscanf(f,"%s",word) != EOF){
        myToLower(word);
        for(int i=0;i<numberOfWords;i++){
            if(strcmp(words[i].word,word) == 0){
                words[i].occurences++;
                words[i].positions[words[i].occurences-1] = position;
            }
        }
        position++;
    }
    for(int i=0;i<numberOfWords;i++){
        fprintf(stdout,"\n%s - %d occurence(s) - word(s): ",words[i].word,words[i].occurences);
        for(int j=0;j < POSITIONS && words[i].positions[j] != 0;j++){
            fprintf(stdout,"%d ",words[i].positions[j]);
        }
    }
    fprintf(stdout,"\n");
}
void myToLower(char *word){
    int i=0;
    while(word[i] != '\0'){
        if(isupper(word[i]) != 0)
            word[i] += 32;
        i++;
    }
}
//UTILITY FUNCTION
void printAscii(){
    for(int i=0;i<256;i++)
        fprintf(stdout,"\n%d: %c",i,i);
    fprintf(stdout,"\n\n");
}

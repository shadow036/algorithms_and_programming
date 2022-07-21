#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME 20+1
#define LINE 100+1
#define WORD 20+1
typedef struct wordS wordT;
struct wordS{
    char *word;
    int occurences;
};
wordT *readWordsFile(int *);
void scanText(wordT *,int);
int main()
{
    int numberOfWords;
    wordT *words = readWordsFile(&numberOfWords);
    scanText(words,numberOfWords);
    return 0;
}
wordT *readWordsFile(int *numberOfWords){
    char filename[FILENAME];
    fprintf(stdout,"words filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    fscanf(f,"%d",numberOfWords);
    wordT *words = (wordT *) malloc(*numberOfWords * sizeof(wordT));
    int i=0;
    char word[WORD];
    while(fscanf(f,"%s",word) != EOF){
        words[i].word = (char *) malloc((strlen(word)+1) * sizeof(char));
        strcpy(words[i].word,word);
        words[i++].occurences = 0;
    }
    return words;
}
void scanText(wordT *words,int numberOfWords){
    char filename[FILENAME];
    fprintf(stdout,"text filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    char word[WORD];
    while(fscanf(f,"%s",word) != EOF){
        for(int i=0;i<numberOfWords;i++){
            if(stricmp(word,words[i].word) == 0)
                words[i].occurences++;
        }
    }
    for(int i=0;i<numberOfWords;i++){
        fprintf(stdout,"%s - %d occurence(s)\n",words[i].word,words[i].occurences);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 100+1
typedef struct wordS wordT;
struct wordS{
    char word[DIM];
    int occurences;
    wordT *next;
};
wordT *loadFile();
int isPresent(wordT *,char *);
wordT *createWord(char *);
void printWords(wordT *);
int main()
{
    wordT *words = loadFile();
    printWords(words);
    return 0;
}
wordT *loadFile(){
    char filename[DIM];
    fprintf(stdout,"words filename => ");
    fscanf(stdin,"%s",filename);
    wordT *words = NULL;
    char word[DIM];
    FILE *f = fopen(filename,"r");
    while(fscanf(f,"%s",word) != EOF){
        if(isPresent(words,word) == 0){
            wordT *temp = createWord(word);
            temp->next = words;
            words = temp;
        }
    }
    return words;
}
int isPresent(wordT *words,char *word){
    wordT *temp = words;
    while(temp != NULL){
        if(strcmp(temp->word,word) == 0){
            temp->occurences++;
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
wordT *createWord(char *word){
    wordT *temp = (wordT *) malloc(sizeof(wordT));
    strcpy(temp->word,word);
    temp->occurences = 1;
    temp->next = NULL;
    return temp;
}
void printWords(wordT *words){
    while(words != NULL){
        fprintf(stdout,"\n%s %d",words->word,words->occurences);
        words = words->next;
    }
    fprintf(stdout,"\n");
}

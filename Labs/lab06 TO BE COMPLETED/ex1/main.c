#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ROW 1000+1
typedef struct wordS wordT;
struct wordS{
    char *word;
    int occurences;
    wordT *next;
};
wordT *loadFileA(char *);
wordT *loadFileB(char *);
wordT *loadFileC(char *);
wordT *createWord(char *);
wordT *isPresentA(wordT *,char *);
wordT *isPresentB(wordT *,char *);
void print(char *,wordT *);
int myStrCmp(char *,char *);
int main(int argc,char *argv[])
{
    if(argc != 3){
        fprintf(stdout,"Wrong number of parameters!");
        return EXIT_FAILURE;
    }
    wordT *words = loadFileA(argv[1]);
    print(argv[2],words);
    return 0;
}
wordT *loadFileA(char *filename){
    FILE *f = fopen(filename,"r");
    wordT *words = NULL;
    char word[ROW];
    while(fscanf(f,"%s",word) != EOF){
        if(isPresentA(words,word) == NULL){
            wordT *newWord = createWord(word);
            newWord->next = words;
            words = newWord;
        }else{
            isPresentA(words,word)->occurences++;
        }
    }
    fclose(f);
    return words;
}
wordT *loadFileB(char *filename){
    FILE *f = fopen(filename,"r");
    wordT *head = NULL;
    wordT *tail = NULL;
    char word[ROW];
    while(fscanf(f,"%s",word) != EOF){
        if(head == NULL){
	        wordT *newWord = createWord(word);
	        head = newWord;
	        tail = newWord;
	    }else if(isPresentB(head,word) == NULL){
	        wordT *newWord = createWord(word);
	        tail->next = newWord;
	        tail = newWord;
	    }else{
	        isPresentB(head,word)->occurences++;
	    }
	    tail->next = head;
    }
    fclose(f);
    return head;
}
wordT *createWord(char *word){
    wordT *newWord = (wordT *) malloc(sizeof(wordT));
    newWord->word = (char *) malloc(sizeof(char));
    strcpy(newWord->word,word);
    newWord->occurences = 1;
    newWord->next = NULL;
    return newWord;
}
wordT *isPresentA(wordT *words,char *word){
    wordT *temp = words;
    while(temp != NULL){
	if(myStrCmp(temp->word,word) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
wordT *isPresentB(wordT *words,char *word){
    if(myStrCmp(words->word,word) == 0)
        return words;
    wordT *temp = words->next;
    while(temp != words){
    	if(myStrCmp(temp->word,word) == 0)
	        return temp;
	    temp = temp->next;
    }
    return NULL;
}
void print(char *filename,wordT *words){
    FILE *f = fopen(filename,"w");
    while(words != NULL){
        fprintf(f,"%s %d\n",words->word,words->occurences);
        words = words->next;
    }
    fclose(f);
}
int myStrCmp(char *str1,char *str2){
    int i=0;
    if(strlen(str1) != strlen(str2))
	return -1;
    while(str1[i] != '\0'){
        if(str1[i]-str2[i] != 0 && str1[i]-str2[i] != 32)
	    return -1;
	i++;
    }
    return 0;
}

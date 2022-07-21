#include <stdio.h>
#include <stdlib.h>
#define MAX 3+1
#define FILENAME 20+1
#include <string.h>
typedef struct resultS resultT;
struct resultS{
    char results[MAX];
};
resultT *loadResultsFile(int *);
int findPatterns(resultT *,char *,int,int,int );
int main()
{
    int numberOfResults = 0;
    int count = 0;
    char pattern[MAX];
    resultT *results = loadResultsFile(&numberOfResults);
    fprintf(stdout,"\n");
    fprintf(stdout,"%d\n",findPatterns(results,pattern,numberOfResults,0,count));
    return 0;
}
resultT *loadResultsFile(int *numberOfResults){
    char filename[FILENAME];
    fprintf(stdout,"results filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    while(fscanf(f,"%*s") != EOF)
        (*numberOfResults)++;
    fclose(f);
    resultT *results = (resultT *) malloc(*numberOfResults * sizeof(resultT));
    f = fopen(filename,"r");
    for(int i=0;i<*numberOfResults;i++)
        fscanf(f,"%s",results[i].results);
    return results;
}
int findPatterns(resultT *results,char *pattern,int numberOfResults,int pos,int count){
    if(pos >= numberOfResults){
        fprintf(stdout,"{");
        for(int i=0;i<numberOfResults;i++){
            fprintf(stdout,"%c",pattern[i]);
        }
        fprintf(stdout,"}\n");
        return ++count;
    }
    int i=0;
    while(results[pos].results[i] != '\0'){
        pattern[pos] = results[pos].results[i];
        count = findPatterns(results,pattern,numberOfResults,pos+1,count);
        i++;
    }
    return count;
}

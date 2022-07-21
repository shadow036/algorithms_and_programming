#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct propertyS propertyT;
struct propertyS{
    int value;
    int heir;
};
propertyT *loadProperties(char *,int *);
void partition(propertyT *,int *,int,int,int,int *);
void printResults(char *,propertyT *,int *,int,int);
int main(int argc,char *argv[])
{
    /*
    if(argc != 4){
        fprintf(stdout,"Wrong number of parameters!\n");
        return EXIT_FAILURE;
    }
    int numberOfProperties = 0;
    int numberOfHeirs = (int)(argv[3] - '0');
    propertyT *properties = loadProperties(argv[1],&numberOfProperties);
    */
    int numberOfProperties = 0;
    int numberOfHeirs = 3;
    int minDifference = INT_MAX;
    propertyT *properties = loadProperties("properties.txt",&numberOfProperties);
    int *bestSolution = (int *) calloc(numberOfProperties,sizeof(int));
    partition(properties,bestSolution,0,numberOfHeirs,numberOfProperties,&minDifference);
    printResults("results.txt",properties,bestSolution,numberOfProperties,numberOfHeirs);
    return 0;
}
propertyT *loadProperties(char *filename,int *numberOfProperties){
    FILE *f = fopen(filename,"r");
    fscanf(f,"%d",numberOfProperties);
    propertyT *properties = (propertyT *) malloc(*numberOfProperties * sizeof(propertyT));
    for(int i=0;i<*numberOfProperties;i++){
        fscanf(f,"%d",&properties[i].value);
        properties[i].heir = -1;
    }
    return properties;
}
void partition(propertyT *properties,int *bestSolution,int pos,int numberOfHeirs,int numberOfProperties,int *minDifference){
    if(pos == numberOfProperties){
        int *sums = (int *) calloc(numberOfHeirs,sizeof(int));
        for(int i=0;i<numberOfHeirs;i++){
            for(int j=0;j<numberOfProperties;j++){
                if(properties[j].heir == i)
                    sums[i] += properties[j].value;
            }
        }
        int totalSum = 0;
        for(int i=0;i<numberOfHeirs;i++){
            for(int j=i+1;j<numberOfHeirs;j++)
                totalSum += abs(sums[i] - sums[j]);
        }
        if(totalSum < *minDifference){
            *minDifference = totalSum;
            for(int i=0;i<numberOfProperties;i++)
                bestSolution[i] = properties[i].heir;
        }
        return;
    }
    for(int i=0;i<numberOfHeirs;i++){
        properties[pos].heir = i;
        partition(properties,bestSolution,pos+1,numberOfHeirs,numberOfProperties,minDifference);
    }
    return;
}
void printResults(char *filename,propertyT *properties,int *bestSolution,int numberOfProperties,int numberOfHeirs){
    FILE *f = fopen(filename,"w");
    for(int i=0;i<numberOfHeirs;i++){
        fprintf(f,"Heir #%d: ",i);
        for(int j=0;j<numberOfProperties;j++){
            if(bestSolution[j] == i)
                fprintf(f,"%d ",properties[j].value);
        }
        fprintf(f,"\n");
    }
}

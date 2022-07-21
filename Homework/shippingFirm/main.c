#include <stdio.h>
#include <stdlib.h>
typedef struct packageS packageT;
struct packageS{
    int weight;
    int truckId;
};
packageT *loadPackages(char *,int *);
int findBestSolution(packageT *,int *,int,int,int);
void writeSolution(packageT *,int *,int);
int main(/*int argc,char *argv[]*/)
{
    int numberOfPackages;
    //packageT *packages = loadPackages(argv[1],&numberOfPackages);
    packageT *packages = loadPackages("packages.txt",&numberOfPackages);
    int *currentBest = (int *) calloc(numberOfPackages,sizeof(int));
    fprintf(stdout,"%d trucks needed.\nPackage location:\n",findBestSolution(packages,currentBest,numberOfPackages,0,numberOfPackages));
    writeSolution(packages,currentBest,numberOfPackages);
    return 0;
}
packageT *loadPackages(char *filename,int *numberOfPackages){
    FILE *f = fopen(filename,"r");
    fscanf(f,"%d",numberOfPackages);
    packageT *packages = (packageT *) malloc(*numberOfPackages * sizeof(packageT));
    for(int i=0;i<*numberOfPackages;i++){
        fscanf(f,"%d",&packages[i].weight);
        packages[i].truckId = 0;
    }
    return packages;
}
int findBestSolution(packageT *packages,int *currentBest,int numberOfPackages,int pos,int minTrucksUsed){
    if(pos == numberOfPackages){
        for(int i=0;i<numberOfPackages;i++){    //CHECK WEIGHT CONSTRAINT
            int counter = 0;
            for(int j=0;j<numberOfPackages;j++){
                if(packages[j].truckId == i)
                    counter+=packages[j].weight;
            }
            if(counter > 100)
                return minTrucksUsed;
        }
        int trucksUsed = 0;
        for(int i=0;i<numberOfPackages;i++){    //COUNT TRUCKS USED
            for(int j=0;j<numberOfPackages;j++){
                if(packages[j].truckId == i){
                    trucksUsed++;
                    break;
                }
            }
        }
        if(trucksUsed < minTrucksUsed){   //CHECK IF THE CURRENT SOLUTION IS BETTER
            minTrucksUsed = trucksUsed;
            for(int i=0;i<numberOfPackages;i++) //IF SO, UPDATE BEST SOLUTION
                currentBest[i] = packages[i].truckId;
        }
        return minTrucksUsed;
    }
    for(int i=0;i<numberOfPackages;i++){
        packages[pos].truckId = i;
        minTrucksUsed = findBestSolution(packages,currentBest,numberOfPackages,pos+1,minTrucksUsed);
        packages[pos].truckId = -1;
    }
    return minTrucksUsed;
}
void writeSolution(packageT *packages,int *currentBest,int numberOfPackages){
    int *totalWeights = (int *) calloc(numberOfPackages,sizeof(int));
    for(int i=0;i<numberOfPackages;i++){
        for(int j=0;j<numberOfPackages;j++){
            if(currentBest[j] == i)
                totalWeights[i] += packages[j].weight;
        }
    }
    for(int i=0;i<numberOfPackages;i++){
        fprintf(stdout,"+ Truck %d, weights %d:\n",i,totalWeights[i]);
        for(int j=0;j<numberOfPackages;j++){
            if(currentBest[j] == i)
                fprintf(stdout,"    - package #%d, weight %d\n",j,packages[j].weight);
        }
    }
}

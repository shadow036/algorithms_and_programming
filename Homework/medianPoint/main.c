#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define ID 3+1
#define FILENAME 20+1
typedef struct pointS pointT;
struct pointS{
    char id[ID];
    float x,y,z;
    float distance;
};
pointT *loadPoints(int *);
void findMedianPoint(pointT *,int);
int main()
{
    int numberOfPoints;
    pointT *points = loadPoints(&numberOfPoints);
    findMedianPoint(points,numberOfPoints);
    return 0;
}
pointT *loadPoints(int *numberOfPoints){
    char filename[FILENAME];
    fprintf(stdout,"points filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    fscanf(f,"%d",numberOfPoints);
    pointT *points = (pointT *) malloc(*numberOfPoints * sizeof(pointT));
    for(int i=0;i<*numberOfPoints;i++){
        fscanf(f,"%s %f %f %f",points[i].id,&points[i].x,&points[i].y,&points[i].z);
        points[i].distance = 0;
    }
    return points;
}
void findMedianPoint(pointT *points,int numberOfPoints){
    for(int i=0;i<numberOfPoints;i++){
        for(int j=0;j<numberOfPoints;j++)
            points[i].distance += sqrt(pow(points[i].x-points[j].x,2) + pow(points[i].y-points[j].y,2) + pow(points[i].z-points[j].z,2));
    }
    int min = 0;
    for(int i=1;i<numberOfPoints;i++){
        if(points[i].distance < points[min].distance)
            min = i;
    }
    fprintf(stdout,"\nMedian point: %s %f %f %f\n",points[min].id,points[min].x,points[min].y,points[min].z);
}

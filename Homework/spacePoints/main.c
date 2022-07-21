#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FILENAME 20+1
typedef struct pointS pointT;
struct pointS{
    float x;
    float y;
    float z;
    float distanceFromTheOrigin;
    pointT *next;
};
pointT *loadFile();
pointT *createPoint(float,float,float);
void writeSortedPoints(pointT *);
pointT *removeMin(pointT *,pointT *);
int main()
{
    pointT *points = loadFile();
    writeSortedPoints(points);
    return 0;
}
pointT *loadFile(){
    char filename[FILENAME];
    fprintf(stdout,"points filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    pointT *points = NULL;
    float x,y,z;
    while(fscanf(f,"%f %f %f",&x,&y,&z) != EOF){
        pointT *newPoint = createPoint(x,y,z);
        newPoint->next = points;
        points = newPoint;
    }
    return points;

}
pointT *createPoint(float x,float y,float z){
    pointT *newPoint = (pointT *) malloc(sizeof(pointT));
    newPoint->x = x;
    newPoint->y = y;
    newPoint->z = z;
    newPoint->distanceFromTheOrigin = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
    newPoint->next = NULL;
    return newPoint;
}
void writeSortedPoints(pointT *points){
    char filename[FILENAME];
    fprintf(stdout,"sorted point filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"w");
    while(points != NULL){
        pointT *min = points;
        pointT *temp = points;
        while(temp != NULL){
            if(temp->distanceFromTheOrigin < min->distanceFromTheOrigin)
                min = temp;
            temp = temp->next;
        }
        fprintf(f,"%f %f %f %f\n",min->x,min->y,min->z,min->distanceFromTheOrigin);
        points = removeMin(points,min);
    }
}
pointT *removeMin(pointT *points,pointT *min){
    pointT *temp = points;
    if(points == min){
        points = points->next;
        free(temp);
    }else{
        while(temp != NULL){
            if(temp->next == min){
                pointT *temp2 = temp->next;
                temp->next = temp->next->next;
                free(temp2);
                break;
            }
            temp = temp->next;
        }
    }
    return points;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 4+1
#define FILENAME 20+1
typedef struct rectangleS rectangleT;
struct rectangleS{
    char identifier[DIM];
    float firstX;
    float firstY;
    float secondX;
    float secondY;
    float perimeter;
    float area;
};
int isPresent(rectangleT *,int,char *);
void calculatePerimeterAndArea(float,float,float,float,float *,float *);
rectangleT *loadFile(int *);
void createOrderedFiles(rectangleT *,int);
void selectionSort(rectangleT *,int,int);
//UTILITY FUNCTION
void printArray(rectangleT *,int);
int main()
{
    int numberOfLines;
    rectangleT *arrayOfRectangles = loadFile(&numberOfLines);
    createOrderedFiles(arrayOfRectangles,numberOfLines/2);
    printArray(arrayOfRectangles,numberOfLines/2);
    return 0;
}
int isPresent(rectangleT *arrayOfRectangles,int numberOfRectangles,char *identifier){
    for(int i=0;arrayOfRectangles[i].identifier != NULL && i < numberOfRectangles;i++){
        if(strcmp(arrayOfRectangles[i].identifier,identifier) == 0)
            return i;
    }
    return -1;
}
void calculatePerimeterAndArea(float firstX,float firstY,float secondX,float secondY,float *perimeter,float *area){
    if(firstX <= secondX && firstY >= secondY){ //first is top-left
        *perimeter = 2*(firstY - secondY) + 2*(secondX-firstX);
        *area = (secondX-firstX)*(firstY - secondY);
    }else if(firstX >= secondX && firstY <= secondY){   //first is bottom-right
        *perimeter = 2*(firstX - secondX) + 2*(secondY-firstY);
        *area = (firstX - secondX)*(secondY-firstY);
    }else if(firstX >= secondX && firstY >= secondY){   //first is top-right
        *perimeter = 2*(firstX - secondX) + 2*(firstY - secondY);
        *area = (firstX-secondX)*(firstY-secondY);
    }else{  //first is bottom-left
        *perimeter = 2*(secondX-firstX) + 2*(secondY-firstY);
        *area = (secondX-firstX)*(secondY-firstY);
    }
}
rectangleT *loadFile(int *numberOfLines){
    char filename[FILENAME];
    fprintf(stdout,"filename => ");
    fscanf(stdin,"%s",filename);
    fprintf(stdout,"\n");
    FILE *f = fopen(filename,"r");
    if(f == NULL)
        return EXIT_FAILURE;
    fscanf(f,"%d",numberOfLines);
    rectangleT *arrayOfRectangles = (rectangleT *) calloc((*numberOfLines)/2,sizeof(rectangleT));
    int i=0;
    char identifier[DIM];
    float x,y;
    while(fscanf(f,"%s %f %f",identifier,&x,&y) != EOF){
        int flag = isPresent(arrayOfRectangles,(*numberOfLines)/2,identifier);
        if(flag == -1){
            strcpy(arrayOfRectangles[i].identifier,identifier);
            arrayOfRectangles[i].firstX = x;
            arrayOfRectangles[i].firstY = y;
            i++;
        }else{
            arrayOfRectangles[flag].secondX = x;
            arrayOfRectangles[flag].secondY = y;
            calculatePerimeterAndArea(arrayOfRectangles[flag].firstX,arrayOfRectangles[flag].firstY,arrayOfRectangles[flag].secondX,arrayOfRectangles[flag].secondY,&arrayOfRectangles[flag].perimeter,&arrayOfRectangles[flag].area);

        }
    }
    return arrayOfRectangles;
}
void createOrderedFiles(rectangleT *arrayOfRectangles,int numberOfRectangles){
    selectionSort(arrayOfRectangles,numberOfRectangles,0);
    selectionSort(arrayOfRectangles,numberOfRectangles,1);
}
void selectionSort(rectangleT *arrayOfRectangles,int numberOfRectangles,int mode){
    rectangleT rectanglesOrdered[numberOfRectangles];
    for(int i=0;i<numberOfRectangles;i++)
        rectanglesOrdered[i] = arrayOfRectangles[i];
    FILE *f;
    if(mode == 0)
        f = fopen("rectanglesOrderedByPerimeter.txt","w");
    else
        f = fopen("rectanglesOrderedByArea.txt","w");
    for(int i=0;i<numberOfRectangles-1;i++){
        int min = i;
        for(int j=i+1;j<numberOfRectangles;j++){
            if(mode == 0){
                if(rectanglesOrdered[j].perimeter < rectanglesOrdered[min].perimeter)
                    min = j;
            }else{
                if(rectanglesOrdered[j].area < rectanglesOrdered[min].area)
                    min = j;
            }
        }
        rectangleT temp = rectanglesOrdered[i];
        rectanglesOrdered[i] = rectanglesOrdered[min];
        rectanglesOrdered[min] = temp;
    }
    for(int i=0;i<numberOfRectangles;i++)
        fprintf(f,"%s\n",rectanglesOrdered[i].identifier);
}
//UTILITY FUNCTION
void printArray(rectangleT *arrayOfRectangles,int numberOfRectangles){
    for(int i=0;i<numberOfRectangles;i++)
        fprintf(stdout,"ID: %s\nx1: %f\ny1: %f\nx2: %f\ny2: %f\nPerimeter: %f\nArea: %f\n\n",arrayOfRectangles[i].identifier,arrayOfRectangles[i].firstX,arrayOfRectangles[i].firstY,arrayOfRectangles[i].secondX,arrayOfRectangles[i].secondY,arrayOfRectangles[i].perimeter,arrayOfRectangles[i].area);
}

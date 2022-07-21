#include "implementation.h"
int main()
{
    char string[DIM];
    int start = 0;
    int length = 0;
    fprintf(stdout,"string => ");
    fscanf(stdin,"%s",string);
    stringSearch(string,&start,&length);
    printResults(string,start,length);
    return 0;
}

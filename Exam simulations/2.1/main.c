#include "rotate.h"
int main()
{
    int n,shift;
    int *array = loadArray(&n,&shift);
    fprintf(stdout,"\nINITIAL ARRAY");
    print(array,n);
    int *auxArray = rotateArray(array,n,shift);
    fprintf(stdout,"\nSHIFTED ARRAY");
    print(auxArray,n);
    return 0;
}

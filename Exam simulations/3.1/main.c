#include "implementation.h"
int main()
{
    int size1,size2;
    fprintf(stdout,"ARRAY 1\n");
    int *array1 = loadArray(&size1);
    fprintf(stdout,"\nARRAY 2\n");
    int *array2 = loadArray(&size2);
    fprintf(stdout,"\nARRAY 1\n");
    print(array1,size1);
    fprintf(stdout,"\n\nARRAY 2\n");
    print(array2,size2);
    if(searchSubArray(array1,array2,size1,size2) == -1)
        fprintf(stdout,"\n\nThe second array doesn't appear in the first array\n");
    else
        fprintf(stdout,"\n\nThe second array appears in the first array starting from index %d\n",searchSubArray(array1,array2,size1,size2));
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "treePrivate.h"
#include "st.h"
int main(int argc,char *argv[])
{
    FILE *fp = fopen("students.txt","r");
    FILE *fp2 = fopen("output.txt","w");
    node_t *root = readTree(fp);
    writeTree(fp2,root,INORDER);
    ST *hashTable = STinit(3);
    fclose(fp);
    fclose(fp2);
    return 0;
}

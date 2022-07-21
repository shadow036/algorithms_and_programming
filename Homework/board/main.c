#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    fprintf(stdout,"number => ");
    fscanf(stdin,"%d",&n);
    for(int i=0;i<n+2;i++){
        fprintf(stdout,"-");
    }
    fprintf(stdout,"\n");
    for(int i=0;i<n;i++){
        fprintf(stdout,"|");
        for(int j=0;j<n;j++){
            if((i+j) % 2 == 0)
                fprintf(stdout,"#");
            else
                fprintf(stdout," ");
        }
        fprintf(stdout,"|\n");
    }
    for(int i=0;i<n+2;i++){
        fprintf(stdout,"-");
    }
    return 0;
}

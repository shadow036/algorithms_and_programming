#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    fprintf(stdout,"number => ");
    fscanf(stdin,"%d",&n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i <= n/2){
                if(j == (n/2) - i || j == (n/2) + i)
                    fprintf(stdout,"+");
                else
                    fprintf(stdout,"-");
            }else{
                if(j == (n/2) - (n-i-1) || j == (n/2) + (n-i-1))
                    fprintf(stdout,"+");
                else
                    fprintf(stdout,"-");
            }
        }
        fprintf(stdout,"\n");
    }
    return 0;
}

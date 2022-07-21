#include "list.h"
int main()
{
    int answer = 1;
    personT *people = NULL;
    char name[DIM];
    char surname[DIM];
    while(answer == 1 || answer == 2){
        fprintf(stdout,"0.Stop\n1.Add\n2.Show list\n=> ");
        fscanf(stdin,"%d",&answer);
        switch(answer){
            case 1:
                fprintf(stdout,"surname name => ");
                fscanf(stdin,"%s %s",surname,name);
                if(orderedInsertion(&people,surname,name) == 1)
                    fprintf(stdout,"\nInsertion successful!\n\n");
                else
                    fprintf(stdout,"\nInsertion failed!\n\n");
                break;
            case 2:
                printPeople(people);
                break;
            default:
                break;
        }
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ID 5+1
#define DIM 20+1
typedef struct voluntaryS voluntaryT;
struct voluntaryS{
    char id[ID];
    char title[DIM];
    char surname[DIM];
    char name[DIM];
    int numberOfDonations;
    int totalAmount;
    voluntaryT *next;
};
voluntaryT *loadVoluntaryFile();
voluntaryT *createVoluntary(char *,char *,char *,char *);
void scanDonations(voluntaryT *);
int main()
{
    voluntaryT *voluntaries = loadVoluntaryFile();
    scanDonations(voluntaries);
    return 0;
}
voluntaryT *loadVoluntaryFile(){
    voluntaryT *head = NULL;
    char filename[DIM];
    fprintf(stdout,"voluntary filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    char id[ID],title[DIM],surname[DIM],name[DIM];
    while(fscanf(f,"%s %s %s %s",id,title,surname,name) != EOF){
        voluntaryT *voluntary = createVoluntary(id,title,surname,name);
        voluntary->next = head;
        head = voluntary;
    }
    fclose(f);
    return head;
}
voluntaryT *createVoluntary(char *id,char *title,char *surname,char *name){
    voluntaryT *voluntary = (voluntaryT *) malloc(sizeof(voluntaryT));
    strcpy(voluntary->id,id);
    strcpy(voluntary->title,title);
    strcpy(voluntary->surname,surname);
    strcpy(voluntary->name,name);
    voluntary->numberOfDonations = 0;
    voluntary->totalAmount = 0;
    voluntary->next = NULL;
    return voluntary;
}
void scanDonations(voluntaryT *voluntaries){
    char filename[DIM];
    fprintf(stdout,"donations filename => ");
    fscanf(stdin,"%s",filename);
    FILE *f = fopen(filename,"r");
    char id[ID];
    int amount;
    while(fscanf(f,"%s %d",id,&amount) != EOF){
        voluntaryT *temp = voluntaries;
        while(temp != NULL){
            if(strcmp(temp->id,id) == 0){
                temp->numberOfDonations++;
                temp->totalAmount+=amount;
            }
            temp = temp->next;
        }
    }
    fclose(f);
    fprintf(stdout,"informations filename => ");
    fscanf(stdin,"%s",filename);
    f = fopen(filename,"w");
    while(voluntaries != NULL){
        fprintf(f,"%s %s %s: %d donation/s - %d cc\n",voluntaries->id,voluntaries->surname,voluntaries->name,voluntaries->numberOfDonations,voluntaries->totalAmount);
        voluntaries = voluntaries->next;
    }
    fclose(f);
}

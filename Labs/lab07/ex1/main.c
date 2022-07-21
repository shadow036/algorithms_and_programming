#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME 20+1
#define ANSWER 4
typedef struct producerS producerT;
typedef struct productS productT;
struct producerS{
    char *name;
    char *id;
    productT *products;
    producerT *next;
};
struct productS{
    char *name;
    int price;
    productT *next;
};
producerT *loadProducers(char *);
producerT *createProducer(char *,char *);
void loadProducts(producerT *,char *);
productT *createProduct(char *,int);
producerT *findProducer(producerT *,char *);
void printProducts(producerT *);
int main(int argc,char *argv[])
{/*
    if(argc != 3){
        fprintf(stdout,"Wrong number of parameters!\n");
        return EXIT_FAILURE;
    }*/
    char filename[NAME];
    fprintf(stdout,"Producers filename => ");
    fscanf(stdin,"%s",filename);
    producerT *producers = loadProducers(filename);
    fprintf(stdout,"Products filename => ");
    fscanf(stdin,"%s",filename);
    loadProducts(producers,filename);
    char answer[ANSWER];
    char id[NAME];
    do{
        fprintf(stdout,"Producer name => ");
        fscanf(stdin,"%s",id);
        producerT *temp = findProducer(producers,id);
        if(temp != NULL)
          printProducts(temp);
        fprintf(stdout,"\nContinue? (yes/no) ");
	fscanf(stdin,"%s",answer);
	fprintf(stdout,"\n");
    }while(strcmp(answer,"yes") == 0);
    return 0;
}
producerT *loadProducers(char *filename){
    producerT *producers = NULL;
    FILE *f = fopen(filename,"r");
    char name[NAME];
    char id [NAME];
    while(fscanf(f,"%s %s\n",name,id) != EOF){
        producerT *newProducer = createProducer(name,id);
        newProducer->next = producers;
        producers = newProducer;
    }
    return producers;
}
producerT *createProducer(char *name,char *id){
    producerT *newProducer = (producerT *) malloc(sizeof(producerT));
    newProducer->name = (char *) malloc((strlen(name)+1) * sizeof(char));
    strcpy(newProducer->name,name);
    newProducer->id = (char *) malloc((strlen(id)+1) * sizeof(char));
    strcpy(newProducer->id,id);
    newProducer->next = NULL;
    newProducer->products = NULL;
    return newProducer;
}
void loadProducts(producerT *producers,char *filename){
    FILE *f = fopen(filename,"r");
    char producerName[NAME];
    char name[NAME];
    int price;
    while(fscanf(f,"%s %s %d\n",producerName,name,&price) != EOF){
        producerT *temp = findProducer(producers,producerName);
        if(temp != NULL){
            productT *newProduct = createProduct(name,price);
            newProduct->next = temp->products;
            temp->products = newProduct;
        }
    }
}
productT *createProduct(char *name,int price){
    productT *newProduct = (productT *) malloc(sizeof(productT));
    newProduct->name = (char *) malloc((strlen(name)+1) * sizeof(char));
    strcpy(newProduct->name,name);
    newProduct->price = price;
    newProduct->next = NULL;
    return newProduct;
}
producerT *findProducer(producerT *producers,char *id){
    producerT *temp = producers;
    while(strcmp(temp->id,id) != 0 && temp != NULL)
        temp = temp->next;
    return temp;
}
void printProducts(producerT *producer){
    productT *temp = producer->products;
    fprintf(stdout,"\n");
    while(temp != NULL){
        fprintf(stdout,"%s %d -> ",temp->name,temp->price);
        temp = temp->next;
    }
    fprintf(stdout,"NULL\n");
}

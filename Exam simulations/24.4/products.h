#ifndef PRODUCTS_H_INCLUDED
#define PRODUCTS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PRODUCT_ID 10+1
#define PRODUCT_NAME 255+1
#define CATEGORY_NAME 10+1
typedef struct productS productT;
struct productS{
    char productId[PRODUCT_ID];
    char productName[PRODUCT_NAME];
    float productPrice;
    int availability;
    char categoryName[CATEGORY_NAME];
    productT *leftProduct;
    productT *rightProduct;
};
productT *createProduct(char *,char *,float,int,char *);
productT *insertProduct(productT *,productT *);
void searchProduct(productT *,char *);
void filter(productT *,char *);
int modifiedStrcmp(char *,char *);
void adder(productT *,char *,int);
void printer(productT *);
#endif // PRODUCTS_H_INCLUDED

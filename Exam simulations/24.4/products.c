#include "products.h"
productT *createProduct(char *productId,char *productName,float productPrice,int availability,char *categoryName){
    productT *newProduct = (productT *) malloc(sizeof(productT));
    strcpy(newProduct->productId,productId);
    strcpy(newProduct->productName,productName);
    newProduct->productPrice = productPrice;
    newProduct->availability = availability;
    strcpy(newProduct->categoryName,categoryName);
    newProduct->leftProduct = NULL;
    newProduct->rightProduct = NULL;
    return newProduct;
}
productT *insertProduct(productT *productsRoot,productT *newProduct){
    if(productsRoot == NULL)
        return newProduct;
    if(strcmp(newProduct->productId,productsRoot->productId) < 0)
        productsRoot->leftProduct = insertProduct(productsRoot->leftProduct,newProduct);
    else
        productsRoot->rightProduct = insertProduct(productsRoot->rightProduct,newProduct);
    return productsRoot;
}
void searchProduct(productT *productsRoot,char *productId){
    if(!strcmp(productsRoot->productId,productId))
        fprintf(stdout,"\nName: %s\nPrice: %.2f\nAvailability: %d\n",productsRoot->productName,productsRoot->productPrice,productsRoot->availability);
    else if(strcmp(productId,productsRoot->productId) < 0)
        searchProduct(productsRoot->leftProduct,productId);
    else
        searchProduct(productsRoot->rightProduct,productId);
}
void filter(productT *productsRoot,char *filterName){  //IN-ORDER VISIT
    if(productsRoot == NULL)
        return;
    filter(productsRoot->leftProduct,filterName);
    if(modifiedStrcmp(productsRoot->productName,filterName) == 1)
        fprintf(stdout,"\nId: %s\nName: %s\nPrice: %.2f\nAvailability: %d\nCategory: %s\n",productsRoot->productId,productsRoot->productName,productsRoot->productPrice,productsRoot->availability,productsRoot->categoryName);
    filter(productsRoot->rightProduct,filterName);
}
int modifiedStrcmp(char *productName,char *filterName){
    for(int i=0;filterName[i] != '*';i++){
        if(productName[i] != filterName[i])
            return 0;
    }
    return 1;
}
void adder(productT *productsRoot,char *productId,int quantityToBeAdded){  //IN-ORDER VISIT
    if(productsRoot == NULL)
        return;
    if(!strcmp(productsRoot->productId,productId))
        productsRoot->availability += quantityToBeAdded;
    if(strcmp(productId,productsRoot->productId) < 0)
        adder(productsRoot->leftProduct,productId,quantityToBeAdded);
    else
        adder(productsRoot->rightProduct,productId,quantityToBeAdded);
}
void printer(productT *productsRoot){   //SAMEEEEEEEEEEEEEE
    if(productsRoot == NULL)
        return;
    printer(productsRoot->leftProduct);
    fprintf(stdout,"\nName: %s\nId: %s\nPrice: %.2f\nAvailability: %d\n",productsRoot->productName,productsRoot->productId,productsRoot->productPrice,productsRoot->availability);
    printer(productsRoot->rightProduct);
}

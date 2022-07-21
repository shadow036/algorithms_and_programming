#include "categories.h"
categoryT *createCategoriesBST(FILE *f){
    char productId[PRODUCT_ID];
    char productName[PRODUCT_NAME];
    float productPrice;
    int availability;
    char categoryName[CATEGORY_NAME];
    categoryT *categoriesRoot = NULL;
    while(fscanf(f,"%s %s %f %d %s",productId,productName,&productPrice,&availability,categoryName) != EOF){
        categoryT *newCategory = createCategory(categoryName);
        productT *newProduct = createProduct(productId,productName,productPrice,availability,categoryName);
        categoriesRoot = insertCategory(categoriesRoot,newCategory,newProduct);
    }
    return categoriesRoot;
}
categoryT *createCategory(char *categoryName){
    categoryT *newCategory = (categoryT *) malloc(sizeof(categoryT));
    strcpy(newCategory->categoryName,categoryName);
    newCategory->productsBST = NULL;
    newCategory->leftCategory = NULL;
    newCategory->rightCategory = NULL;
    return newCategory;
}
categoryT *insertCategory(categoryT *categoriesRoot,categoryT *newCategory,productT *newProduct){
    if(categoriesRoot == NULL){
        newCategory->productsBST = insertProduct(newCategory->productsBST,newProduct);
        return newCategory;
    }
    if(!strcmp(categoriesRoot->categoryName,newCategory->categoryName)){    //CATEGORY ALREADY PRESENT
        categoriesRoot->productsBST = insertProduct(categoriesRoot->productsBST,newProduct);
        free(newCategory);
        return categoriesRoot;
    }
    if(strcmp(newCategory->categoryName,categoriesRoot->categoryName) < 0)
        categoriesRoot->leftCategory = insertCategory(categoriesRoot->leftCategory,newCategory,newProduct);
    else
        categoriesRoot->rightCategory = insertCategory(categoriesRoot->rightCategory,newCategory,newProduct);
    return categoriesRoot;
}
void searchCategory(categoryT *categoriesRoot,char *categoryName,char *productId){
    if(!strcmp(categoriesRoot->categoryName,categoryName))
        searchProduct(categoriesRoot->productsBST,productId);
    else if(strcmp(categoryName,categoriesRoot->categoryName) < 0)
        searchCategory(categoriesRoot->leftCategory,categoryName,productId);
    else
        searchCategory(categoriesRoot->rightCategory,categoryName,productId);
}
void filterWrapper(categoryT *categoriesRoot,char *productName){  //IN-ORDER VISIT
    if(categoriesRoot == NULL)
        return;
    filterWrapper(categoriesRoot->leftCategory,productName);
    filter(categoriesRoot->productsBST,productName);
    filterWrapper(categoriesRoot->rightCategory,productName);
}
void adderWrapper(categoryT *categoriesRoot,char *productId,int quantityToBeAdded){  //IN-ORDER VISIT
    if(categoriesRoot == NULL)
        return;
    adderWrapper(categoriesRoot->leftCategory,productId,quantityToBeAdded);
    adder(categoriesRoot->productsBST,productId,quantityToBeAdded);
    adderWrapper(categoriesRoot->rightCategory,productId,quantityToBeAdded);
}
void printerWrapper(categoryT *categoriesRoot){  //YET ANOTHER IN-ORDER VISIT...
    if(categoriesRoot == NULL)
        return;
    printerWrapper(categoriesRoot->leftCategory);
    fprintf(stdout,"\n----------|%s|----------",categoriesRoot->categoryName);
    printer(categoriesRoot->productsBST);
    printerWrapper(categoriesRoot->rightCategory);
}

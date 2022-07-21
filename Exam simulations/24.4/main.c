#include "categories.h"
#define ANSWER 10+1
int main()
{
    categoryT *categoriesBST = createCategoriesBST(fopen("file.txt","r"));
    char answer[ANSWER];
    while(strcmp(answer,"stop")){
        fprintf(stdout,"\n->search categoryName productId\n->filter filterString*\n->insert productId productName productPrice availability categoryName\n->update productId piecesToBeAdded\n->print\nstop\n=> ");
        fscanf(stdin,"%s",answer);
        if(!strcmp(answer,"search")){
            char categoryName[CATEGORY_NAME];
            char productId[PRODUCT_ID];
            fscanf(stdin,"%s %s",categoryName,productId);
            searchCategory(categoriesBST,categoryName,productId);
        }else if(!strcmp(answer,"filter")){
            char filt[PRODUCT_NAME];
            fscanf(stdin,"%s",filt);
            filterWrapper(categoriesBST,filt);
        }else if(!strcmp(answer,"insert")){
            char productId[PRODUCT_ID];
            char productName[PRODUCT_NAME];
            float productPrice;
            int availability;
            char categoryName[CATEGORY_NAME];
            fscanf(stdin,"%s %s %f %d %s",productId,productName,&productPrice,&availability,categoryName);
            categoryT *newCategory = createCategory(categoryName);
            productT *newProduct = createProduct(productId,productName,productPrice,availability,categoryName);
            categoriesBST = insertCategory(categoriesBST,newCategory,newProduct);
        }else if(!strcmp(answer,"update")){
            char productId[PRODUCT_ID];
            int quantityToBeAdded;
            fscanf(stdin,"%s %d",productId,&quantityToBeAdded);
            adderWrapper(categoriesBST,productId,quantityToBeAdded);
        }else if(!strcmp(answer,"print"))
            printerWrapper(categoriesBST);
    }
    return 0;
}

#ifndef CATEGORIES_H_INCLUDED
#define CATEGORIES_H_INCLUDED
#include "products.h"
typedef struct categoryS categoryT;
struct categoryS{
    char categoryName[CATEGORY_NAME];
    productT *productsBST;
    categoryT *leftCategory;
    categoryT *rightCategory;
};
categoryT *createCategory(char *);
categoryT *insertCategory(categoryT *,categoryT *,productT *);
categoryT *createCategoriesBST(FILE *);
void searchCategory(categoryT *,char *,char *);
void filterWrapper(categoryT *,char *);
void adderWrapper(categoryT *,char *,int);
void printerWrapper(categoryT *);
#endif // CATEGORIES_H_INCLUDED

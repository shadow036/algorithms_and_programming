#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 100+1
#define FILENAME 20+1
typedef struct userS userT;
typedef struct borrowS borrowT;
typedef struct bookS bookT;
struct userS{
    char name[DIM];
    char phoneNumber[DIM];
    char job[DIM];
    char id[DIM];
};
struct borrowS{
    char userId[DIM];
    char bookId[DIM];
    char date[DIM];
};
struct bookS{
    char authorName[DIM];
    char title[DIM];
    char bookPosition[DIM];
    char id[DIM];
    int totalNumberOfCopies;
};
userT *loadUsers(int *);
borrowT *loadBorrows(int *);
bookT *loadBooks(int *);
void userBorrows(userT *,int,borrowT *,int);
void bookBorrow(bookT *,int,borrowT *,int);
//UTILITY FUNCTIONS
void printUsers(userT *,int);
void printBorrows(borrowT *,int);
void printBooks(bookT *,int);
int main()
{
    int numberOfUsers,numberOfBorrows,numberOfBooks;
    userT *users = loadUsers(&numberOfUsers);
    borrowT *borrows = loadBorrows(&numberOfBorrows);
    bookT *books = loadBooks(&numberOfBooks);
    printUsers(users,numberOfUsers);
    printBooks(books,numberOfBooks);
    printBorrows(borrows,numberOfBorrows);
    userBorrows(users,numberOfUsers,borrows,numberOfBorrows);
    bookBorrow(books,numberOfBooks,borrows,numberOfBorrows);
    return 0;
}
userT *loadUsers(int *numberOfUsers){
    FILE *f = fopen("users.txt","r");
    *numberOfUsers = 0;
    while(fscanf(f,"%*s %*s %*s %*s") != EOF){
        (*numberOfUsers)++;
    }
    fclose(f);
    userT *users = (userT *) malloc(*numberOfUsers * sizeof(userT));
    f = fopen("users.txt","r");
    char name[DIM];
    char phoneNumber[DIM];
    char job[DIM];
    char id[DIM];
    int i = 0;
    while(fscanf(f,"%s %s %s %s",name,phoneNumber,job,id) != EOF){
        strcpy(users[i].name,name);
        strcpy(users[i].phoneNumber,phoneNumber);
        strcpy(users[i].job,job);
        strcpy(users[i].id,id);
        i++;
    }
    fclose(f);
    return users;
}
borrowT *loadBorrows(int *numberOfBorrows){
    FILE *f = fopen("borrows.txt","r");
    *numberOfBorrows = 0;
    while(fscanf(f,"%*s %*s %*s") != EOF){
        (*numberOfBorrows)++;
    }
    fclose(f);
    borrowT *borrows = (borrowT *) malloc(*numberOfBorrows * sizeof(borrowT));
    f = fopen("borrows.txt","r");
    char userID[DIM];
    char bookID[DIM];
    char date[DIM];
    int i = 0;
    while(fscanf(f,"%s %s %s",userID,bookID,date) != EOF){
        strcpy(borrows[i].userId,userID);
        strcpy(borrows[i].bookId,bookID);
        strcpy(borrows[i].date,date);
        i++;
    }
    fclose(f);
    return borrows;
}
bookT *loadBooks(int *numberOfBooks){
    FILE *f = fopen("catalogue.txt","r");
    *numberOfBooks = 0;
    while(fscanf(f,"%*s %*s %*s %*s %*d") != EOF){
        (*numberOfBooks)++;
    }
    fclose(f);
    bookT *books = (bookT *) malloc(*numberOfBooks * sizeof(bookT));
    f = fopen("catalogue.txt","r");
    char authorName[DIM];
    char title[DIM];
    char bookPosition[DIM];
    char id[DIM];
    int totalNumberOfCopies;
    int i = 0;
    while(fscanf(f,"%s %s %s %s %d",authorName,title,bookPosition,id,&totalNumberOfCopies) != EOF){
        strcpy(books[i].authorName,authorName);
        strcpy(books[i].title,title);
        strcpy(books[i].bookPosition,bookPosition);
        strcpy(books[i].id,id);
        books[i].totalNumberOfCopies = totalNumberOfCopies;
        i++;
    }
    fclose(f);
    return books;
}
void userBorrows(userT *users,int numbersOfUsers,borrowT *borrows,int numberOfBorrows){
    FILE *f = fopen("user_borrows.txt","w");
    for(int i=0;i<numbersOfUsers;i++){
        fprintf(f,"%s %s %s %s ",users[i].name,users[i].phoneNumber,users[i].job,users[i].id);
        int numberOfBorrowedBooks = 0;
        for(int j=0;j<numberOfBorrows;j++){
            if(strcmp(users[i].id,borrows[j].userId) == 0)
                numberOfBorrowedBooks++;
        }
        fprintf(f,"%d\n",numberOfBorrowedBooks);
        for(int j=0;j<numberOfBorrows;j++){
            if(strcmp(users[i].id,borrows[j].userId) == 0)
                fprintf(f,"%s %s\n",borrows[j].bookId,borrows[j].date);
        }
        fprintf(f,"\n");
    }
}
void bookBorrow(bookT *books,int numberOfBooks,borrowT *borrows,int numberOfBorrows){
    FILE *f = fopen("book_borrows.txt","w");
    for(int i=0;i<numberOfBooks;i++){
        fprintf(f,"%s %s %s %s %d ",books[i].authorName,books[i].title,books[i].bookPosition,books[i].id,books[i].totalNumberOfCopies);
        int numberOfBorrowedBooks = 0;
        for(int j=0;j<numberOfBorrows;j++){
            if(strcmp(books[i].id,borrows[j].bookId) == 0)
                numberOfBorrowedBooks++;
        }
        fprintf(f,"%d\n",numberOfBorrowedBooks);
        for(int j=0;j<numberOfBorrows;j++){
            if(strcmp(books[i].id,borrows[j].bookId) == 0)
                fprintf(f,"%s %s\n",borrows[j].userId,borrows[j].date);
        }
        fprintf(f,"\n");
    }
}
//UTILITY FUNCTIONS
void printUsers(userT *users,int numberOfUsers){
    fprintf(stdout,"\n");
    for(int i=0;i<numberOfUsers;i++){
        fprintf(stdout,"%s %s %s %s\n",users[i].name,users[i].phoneNumber,users[i].job,users[i].id);
    }
}
void printBorrows(borrowT *borrows,int numberOfBorrows){
    fprintf(stdout,"\n");
    for(int i=0;i<numberOfBorrows;i++){
        fprintf(stdout,"%s %s %s\n",borrows[i].userId,borrows[i].bookId,borrows[i].date);
    }
}
void printBooks(bookT *books,int numberOfBooks){
    fprintf(stdout,"\n");
    for(int i=0;i<numberOfBooks;i++){
        fprintf(stdout,"%s %s %s %s %d\n",books[i].authorName,books[i].title,books[i].bookPosition,books[i].id,books[i].totalNumberOfCopies);
    }
}

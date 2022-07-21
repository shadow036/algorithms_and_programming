#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define DIM 100+1
//A
int mult(int,int);
//B
void d2b(int,int *,int *);
//C
int catalan (int);
//D
int countSpaces(char *);
//E
int isPalindrome(char *,int);
//F
void triangle1(int,int);
//G
void triangle2(int,int,int);
int main()
{
    fprintf(stdout,"----------PART A----------\n");
    int x,y;
    fprintf(stdout,"x y => ");
    fscanf(stdin,"%d %d",&x,&y);
    fprintf(stdout,"%d x %d = %d\n",x,y,mult(x,y));
    fprintf(stdout,"\n----------PART B----------\n");
    int n = 0;
    int *b = (int *) calloc(n,sizeof(int));
    d2b(23,b,&n);
    fprintf(stdout,"\n----------PART C----------\n");
    fprintf(stdout,"Insert catalan index => ");
    fscanf(stdin,"%d",&n);
    fprintf(stdout,"The catalan number of index %d is: %d\n",n,catalan(n));
    fprintf(stdout,"\n----------PART D----------\n");
    char s[DIM];
    fprintf(stdout,"Insert string with spaces => ");
    fscanf(stdin,"%*c");
    gets(s);
    char *temp = s;
    fprintf(stdout,"%s: %d spaces\n",temp,countSpaces(s));
    fprintf(stdout,"\n----------PART E----------\n");
    fprintf(stdout,"Insert palindrome string => ");
    gets(s);
    temp = s;
    if(isPalindrome(s,strlen(s)) == 1)
        fprintf(stdout,"%s is palindrome\n",temp);
    else
        fprintf(stdout,"\n%s is not palindrome\n",temp);
    fprintf(stdout,"\n----------PART F----------\n");
    triangle1(10,1);
    fprintf(stdout,"\n----------PART G----------\n");
    triangle2(10,1,1);
    return 0;
}
//A
int mult(int x,int y){
    if(y == 0)
        return 0;
    if(y == 1)
        return x;
     return x + mult(x,y-1);
}
//B
void d2b(int d,int *b,int *n){
    if(d == 0){
        for(int i=*n-1;i>=0;i--)
            fprintf(stdout,"%d",b[i]);
        fprintf(stdout,"\n");
        return;
    }
    b[*n] = d % 2;
    (*n)++;
    d2b(d/2,b,n);
    return;
}
//C
int catalan(int n){
    if(n == 0)
        return 1;
    int sum = 0;
    for(int i=n-1;i>=0;i--)
        sum += (catalan(i)*catalan(n-i-1));
    return sum;
}
//D
int countSpaces(char *s){
    if(*s == '\0')
        return 0;
    if(isspace(*s) != 0)
        return 1 + countSpaces(s+1);
    else
        return countSpaces(s+1);
}
//E
int isPalindrome(char *s,int l){
    if(*s == '\0')
        return 1;
    while(ispunct(*s) != 0 || isspace(*s) != 0){
        s++;
        l--;
    }
    while(ispunct(s[l-1]) != 0 || isspace(s[l-1]) != 0)
        l--;
    if(*s == s[l-1] || *s == s[l-1]-32 || *s == s[l-1]+32)
        return isPalindrome(s+1,l-2);
    else
        return 0;
}
//F
void triangle1(int n,int currentRow){
    if(currentRow == n+1)
        return;
    for(int i=1;i<=currentRow;i++)
        fprintf(stdout,"%d ",currentRow);
    fprintf(stdout,"\n");
    triangle1(n,currentRow+1);
}
//G
void triangle2(int n,int currentRow,int currentColumn){
   if(currentRow == n+1)
        return;
   if(currentColumn == currentRow+1){
        fprintf(stdout,"\n");
        triangle2(n,currentRow+1,1);
        return;
   }
   fprintf(stdout,"%d ",currentRow);
   triangle2(n,currentRow,currentColumn+1);
}

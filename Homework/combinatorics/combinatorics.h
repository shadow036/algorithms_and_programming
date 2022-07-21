#ifndef COMBINATORICS_H_INCLUDED
#define COMBINATORICS_H_INCLUDED
void simpleArrangements(char *input,char *solution,int *used,int n,int k,int pos);
void arrangementsWithRepetitions(char *,char *,int,int,int);
void simplePermutations(char *,char *,int *,int,int);
void permutationsWithRepetitions(char *input,char *solution,int *used,int n,int dist,int pos);
void simpleCombinations(char *,char *,int,int,int,int);
void combinationsWithRepetitions(char *,char *,int,int,int,int);
void powerSet(char *,char *,int);
void partition(char *,char *,int,int,int);

#endif // COMBINATORICS_H_INCLUDED

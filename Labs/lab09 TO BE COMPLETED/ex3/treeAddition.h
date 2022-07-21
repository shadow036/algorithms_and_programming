#ifndef _DATA_INCLUDED
#define _DATA_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXC 60

void countNode(node_t *,int *);
void countLevel(node_t *,int *,int);
void countPath(node_t *,int *,int);
int visit(node_t *,int,int);
#endif

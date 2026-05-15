#ifndef BINTREE_H
#define BINTREE_H
#include <stdbool.h>

typedef enum { RED, BLACK } Color;
typedef struct _no No;

typedef struct _rbtree{
	No* root;
	No* nil;
	unsigned int rotacoes, coloracoes;
}RBtree;

RBtree* RBcreate();

bool RBinsert(RBtree*, int);
int BTaltura(No*);
short alturaNo(No*);
void BTpre(No*);
void BTprint(No*);
void BTin(No*);
void BTpos(No*);
void transplant(BinTree*, No*, No*);
No* BTsearch(No*, int);
No* BTmax(No*);
int BTmin(No*);
No* BTsucc(No*);
void RBinsertFixup(RBtree*, No*);
int BTnodeKey(No*);



#endif

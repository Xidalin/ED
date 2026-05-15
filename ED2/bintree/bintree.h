#ifndef BINTREE_H
#define BINTREE_H
#include <stdbool.h>

typedef enum { RED, BLACK } Color;
typedef struct _no No;

typedef struct _bintree{
	No* root;
	unsigned int rotacoes;
}BinTree;

typedef struct _rbtree{
	No* root;
	No* nil;
	unsigned int rotacoes, coloracoes;
}RBtree;

BinTree* BTcreate();
RBtree* RBcreate();

bool BTinsert(BinTree*, int);
bool RBinsert(RBtree*, int);
bool Tree_delete(BinTree*, No*);
bool isbst (No*);
int BTaltura(No*);
short alturaNo(No*);
No* insertAVL(BinTree*, No*, int);
void BTpre(No*);
void BTprint(No*);
void BTin(No*);
void BTpos(No*);
void transplant(BinTree*, No*, No*);
No* BTsearch(No*, int);
No* BTmax(No*);
int BTmin(No*);
No* BTsucc(No*);
No* lerArvore(char*, int* );
No* rotacaoEsq(BinTree*, No*);
No* rotacaoDir(BinTree*, No*);
void RBinsertFixup(RBtree*, No*);
int BTnodeKey(No*);



#endif
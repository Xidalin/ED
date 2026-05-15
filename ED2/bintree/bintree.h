#ifndef BINTREE_H
#define BINTREE_H
#include <stdbool.h>

typedef struct _no No;

typedef struct _bintree{
	No* root;
	unsigned int rotacoes;
}BinTree;

BinTree* BTcreate();

bool BTinsert(BinTree*, int);
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
No* rotacaoEsq(BinTree*, No*);
No* rotacaoDir(BinTree*, No*);
int BTnodeKey(No*);



#endif

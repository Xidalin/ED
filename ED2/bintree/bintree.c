#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

typedef struct _no{
    int key;
    No* left;
    No* rgt;
    No* p;
    short h;
}No;

BinTree* BTcreate(){
    BinTree* novo = malloc(sizeof(BinTree));
    if (novo != NULL){
        novo->root = NULL;
        novo->rotacoes = 0;
    }

    return novo;

}

static No* criarNo(int valor) {
    No* novo = malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->key = valor;
    novo->left = NULL;
    novo->rgt = NULL;
    novo->p = NULL;
    novo->color = RED;
    novo->h = 0;
    return novo;
}

bool BTinsert(BinTree* t, int key){

    No* novo = criarNo(key);

    No* y = NULL;
    No* x = t->root;

    while (x != NULL){
        y = x;
        if( key < x->key){
            x = x->left;
        }else{
            x = x->rgt;
        }

    }
    novo->p = y;
    if (y == NULL) {
        t->root = novo; 
    } else if (key < y->key) {
        y->left = novo; 
    } else {
        y->rgt = novo;  
    }

    return true;

}

void Transplant(BinTree* t, No* u, No* v){
    if (u->p == NULL){ // se o no a ser transplantado eh a raiz
        t->root = v;
    }else if (u == u->p->left){
        u->p->left = v;
    }else u->p->rgt = v;
    if (v != NULL){
        v->p = u->p;
    }
}

bool ehSentinela(No* n) {
    return n != NULL && n->left == n && n->rgt == n && n->p == n;
}

int BTmin(No* t){
    if (t == NULL || ehSentinela(t)) return 0;

    No* aux = t;

    while(aux->left != NULL && !ehSentinela(aux->left)){
        aux = aux->left;
    }
    int min = aux->key;
    return min;

}

No* BTmax(No* t){
    if (t == NULL || ehSentinela(t)) return NULL;

    No* aux = t;

    while(aux->rgt != NULL && !ehSentinela(aux->rgt)){
        aux = aux->rgt;
    }
    return aux;
}

void BTprint(No* t){
    if(t != NULL && !ehSentinela(t)){
        printf("%d ", t->key);
        BTprint(t->left);
        BTprint(t->rgt);
    }
}

No* BTsearch(No* t, int target){
    if( t == NULL || ehSentinela(t) || t->key == target){
        return t;
    }
    if(t->key < target ) return BTsearch (t->rgt, target); //se a chave é menor que o target, entra na rcs do filho a direita
    return BTsearch(t->left, target); //caso contrario, entra na recursividade do filho a esquerda (menor)
}

int BTnodeKey(No* n){
    if (n == NULL || ehSentinela(n)) return 0;
    return n->key;
}

int BTaltura(No* n) {
    if (n == NULL || ehSentinela(n)) return -1;  // árvore vazia = -1 (altura em arestas)
    int hEsq = BTaltura(n->left);
    int hDir = BTaltura(n->rgt);
    return (hEsq > hDir ? hEsq : hDir) + 1;
}

static void atualizarAltura(No* n) {
    if (n == NULL || ehSentinela(n)) return;
    short hl = (n->left == NULL || ehSentinela(n->left)) ? -1 : n->left->h;
    short hr = (n->rgt == NULL || ehSentinela(n->rgt)) ? -1 : n->rgt->h;
    n->h = (hl > hr ? hl : hr) + 1;
}

short alturaNo (No* n){
    if (n == NULL || ehSentinela(n)) return -1; else return n->h;
}

short verfbalance (No* n){
    if(n){
        return (alturaNo(n->left) - alturaNo(n->rgt));
    }else return 0;
}

No* rotacaoEsq (BinTree* t, No* r){
    t->rotacoes++;
    No *y, *f;

    if (r == NULL || r->rgt == NULL) return r;

    y = r->rgt;
    f = y->left;

    y->left = r;
    r->rgt = f;

    y->p = r->p;
    r->p = y;
    if (f != NULL) f->p = r;

    atualizarAltura(r);
    atualizarAltura(y);

    return y;

}

No* rotacaoRgt (BinTree* t, No* r){
    t->rotacoes++;
    No *y, *f;

    if (r == NULL || r->left == NULL) return r;

    y = r->left;
    f = y->rgt;

    y->rgt = r;
    r->left = f;

    y->p = r->p;
    r->p = y;
    if (f != NULL) f->p = r;

    atualizarAltura(r);
    atualizarAltura(y);

    return y;

}

No* rotacaoEsqDir (BinTree* t, No* r){
    r->left = rotacaoEsq(t, r->left);
    return rotacaoRgt(t, r);
}

No* rotacaoDirEsq(BinTree* t, No* r){
    r->rgt = rotacaoRgt(t, r->rgt);
    return rotacaoEsq(t, r);
}

bool inOrderbst(No* no, int* prev){
    if( no == NULL || ehSentinela(no)) return true;

    if(!inOrderbst(no->left, prev)) return false;

    printf("%d ", no->key);

    if(*prev >= no->key){
        printf("\n");
        printf("%d >= %d, nao pode\n", *prev, no->key);
        return false;
    }

    *prev = no->key;

    return inOrderbst(no->rgt, prev);
}

bool isbst (No* root){
    int prev = INT_MIN;
    return inOrderbst(root, &prev);


}

No* balanceamento (BinTree* t, No* r){
    short fb = verfbalance(r);

    if (fb < -1 && verfbalance(r->rgt) <= 0){
        r = rotacaoEsq(t, r);
    }else if (fb > 1 && verfbalance(r->left) >= 0){
        r = rotacaoRgt(t, r); 
    }else if (fb < -1 && verfbalance(r->rgt) > 0){
       r = rotacaoDirEsq(t, r);
    }else if (fb > 1 && verfbalance(r->left) < 0){
        r = rotacaoEsqDir(t, r);
    }

    return r;
}

No* insertAVL(BinTree*t, No *r, int x){
    if(r == NULL) 
        return criarNo(x);
    else{ // inserção será à esquerda ou à direita
        if(x < r->key)
            r->left = insertAVL(t, r->left, x);
        else if(x > r->key)
            r->rgt = insertAVL(t, r->rgt, x);
        else
            printf("\nnao deu pra inserir dog\nO elemento %d a existe\n", x);
    }
    atualizarAltura(r);
    // verifica a necessidade de rebalancear a árvore
    r = balanceamento(t, r);
    return r;
}

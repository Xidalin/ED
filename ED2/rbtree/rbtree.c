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
    Color color;
    short h;
}No;


RBtree* RBcreate(){
    RBtree* novo = malloc(sizeof(RBtree));
    if (novo == NULL) return NULL;

    novo->nil = malloc(sizeof(No));
    if (novo->nil == NULL) {
        free(novo);
        return NULL;
    }

    novo->nil->key = 0;
    novo->nil->left = novo->nil;
    novo->nil->rgt = novo->nil;
    novo->nil->p = novo->nil;
    novo->nil->color = BLACK;
    novo->nil->h = -1;
    novo->root = novo->nil;

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

static void rbPintar(No* n, Color cor) {
    if (n != NULL && n->color != cor) {
        n->color = cor;
    }
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

short alturaNo (No* n){
    if (n == NULL || ehSentinela(n)) return -1; else return n->h;
}

static void rbRotacaoEsq(RBtree* t, No* x){
    No* y = x->rgt;
    t->rotacoes++;
    x->rgt = y->left;
    if (y->left != t->nil) {
        y->left->p = x;
    }

    y->p = x->p;
    if (x->p == t->nil) {
        t->root = y;
    } else if (x == x->p->left) {
        x->p->left = y;
    } else {
        x->p->rgt = y;
    }

    y->left = x;
    x->p = y;
}

static void rbRotacaoRgt(RBtree* t, No* x){
    No* y = x->left;
    t->rotacoes++;
    x->left = y->rgt;
    if (y->rgt != t->nil) {
        y->rgt->p = x;
    }

    y->p = x->p;
    if (x->p == t->nil) {
        t->root = y;
    } else if (x == x->p->rgt) {
        x->p->rgt = y;
    } else {
        x->p->left = y;
    }

    y->rgt = x;
    x->p = y;
}

void RBinsertFixup(RBtree* t, No* z) {
    while (z->p->color == RED) {
        if (z->p == z->p->p->left) {
            No* y = z->p->p->rgt;  // tio

            if (y->color == RED) {
                rbPintar(z->p, BLACK);  t->coloracoes++;
                rbPintar(y, BLACK); t->coloracoes++;
                rbPintar(z->p->p, RED); t->coloracoes++;
                z = z->p->p;
            } else {
                if (z == z->p->rgt) {
                    z = z->p;
                    rbRotacaoEsq(t, z);
                }

                rbPintar(z->p, BLACK);  t->coloracoes++;
                rbPintar(z->p->p, RED); t->coloracoes++;
                rbRotacaoRgt(t, z->p->p);
            }
        } else {
            No* y = z->p->p->left;  // tio

            if (y->color == RED) {
                rbPintar(z->p, BLACK);  t->coloracoes++;
                rbPintar(y, BLACK); t->coloracoes++;
                rbPintar(z->p->p, RED); t->coloracoes++;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    rbRotacaoRgt(t, z);
                }

                rbPintar(z->p, BLACK);  t->coloracoes++;
                rbPintar(z->p->p, RED); t->coloracoes++;
                rbRotacaoEsq(t, z->p->p);
            }
        }
    }

    rbPintar(t->root, BLACK);   t->coloracoes++;
    t->root->p = t->nil;
}

bool RBinsert (RBtree* t, int z){
    No* novo = criarNo(z);
    if (novo == NULL) return false;
    
    No* y = t->nil;
    No* x = t->root;
    while (x != t->nil){
    
        y = x;

        if (z < x->key) x = x->left;
        else x = x->rgt;
    }

    novo->p = y; 

    if (y == t->nil)t->root = novo;
    else if (z < y->key)y->left = novo;
    else y->rgt = novo;

    novo->left = t->nil;
    novo->rgt = t->nil;
    novo->color = RED;

    RBinsertFixup(t, novo);

    return true;
}


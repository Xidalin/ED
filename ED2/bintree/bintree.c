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

BinTree* BTcreate(){
    BinTree* novo = malloc(sizeof(BinTree));
    if (novo != NULL){
        novo->root = NULL;
        novo->rotacoes = 0;
    }

    return novo;

}

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
    novo->rotacoes = 0;
    novo->coloracoes = 0;

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

/*bool Tree_delete(BinTree* t, No* z){
    if (t == NULL || z == NULL) return false;
    if(z->left == NULL){
        Transplant(t, z, z->rgt);
    }else if (z->rgt == NULL){
        Transplant(t, z, z->left);
    }
    else {

        No* y = BTmin(z->rgt);
        if( y->p != z){
            Transplant(t, y, y->rgt);
            y->rgt = z->rgt;
            y->rgt->p = y;
        }
        Transplant(t, z, y);
        y->left = z->left;
        y->left->p = y;

    }

    free(z);
    return true;
}*/

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

static void pularEspacos(const char* str, int* pos) {
    while (str[*pos] != '\0' && isspace((unsigned char)str[*pos])) {
        (*pos)++;
    }
}

No* lerArvore(char* str, int* pos) {
    pularEspacos(str, pos);

    if (str[*pos] != '(') return NULL;

    (*pos)++; // Pula o '('
    pularEspacos(str, pos);

    if (str[*pos] == ')') { // No vazio: ()
        (*pos)++;
        return NULL;
    }

    char* fim = NULL;
    long valor = strtol(&str[*pos], &fim, 10);
    if (fim == &str[*pos]) return NULL;

    *pos = (int)(fim - str);

    No* novo = criarNo((int)valor);
    if (novo == NULL) return NULL;

    pularEspacos(str, pos);

    if (str[*pos] == '(') {
        novo->left = lerArvore(str, pos);
        if (novo->left != NULL) novo->left->p = novo;

        pularEspacos(str, pos);

        if (str[*pos] == '(') {
            novo->rgt = lerArvore(str, pos);
            if (novo->rgt != NULL) novo->rgt->p = novo;
        }
    }

    pularEspacos(str, pos);
    if (str[*pos] == ')') {
        (*pos)++; // Pula o ')' do no atual
    }

    return novo;
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
    atualizarAltura(x);
    atualizarAltura(y);
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
    atualizarAltura(x);
    atualizarAltura(y);
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

No* removeAVL (BinTree* t, No* r, int x){
    if (r == NULL) {
        return NULL;
    }else {
        if (r->key == x){
            if (r->left == NULL && r->rgt == NULL){
                free(r);
                printf("\nnó folha removido pae\n");
                return NULL;
            }
        else { //o nó tem dois boneco xx

            if( r->left != NULL && r->rgt != NULL){
                No* aux = r->left;
                while(aux->rgt != NULL){ // maior valor da sub arvore a esquerda   (predecessor direto)
                    aux = aux->rgt;
                }
                r->key = aux->key;
                aux->key = x;
                printf("Elemento trocado: %d !\n", x);
                r->left = removeAVL(t, r->left, x);
            }
            else if (r->left != NULL){
                No* aux = r->left;
                free(r);
                printf("\nremovemo o no com filho esquerdo\n");
                return aux;
            }
        }
        }else {
            if ( x < r->key){
                r->left = removeAVL(t, r->left, x);
            } else if ( x > r->key){
                r->rgt = removeAVL(t, r->rgt, x);
            }
        }

        atualizarAltura(r);
        r = balanceamento(t, r);

        return r;
    }
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


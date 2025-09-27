#include "sequencia.h"
#include <stdio.h>
#include <stdlib.h>

struct _no{
    float valor;
    int id;
    int prox_id;
    No* prox;
};
struct _sequencia{
    No* inicio;
    No* fim;
    int tamanho;
};

int inserir_final(Sequencia* s, float valor, int id, int proxid){
    if( s == NULL) {
        printf("nao tem sequencia\n");
        return 0;
    };
    No* novo = (No*) malloc(sizeof(No));
    if( novo == NULL) return 0;

    novo->valor = valor;
    novo->id = id;
    novo->prox_id = proxid;
    novo->prox = NULL;

    if( s->inicio == NULL){
        s->inicio = novo;
    }else{
        s->fim->prox = novo;
    }
    s->fim = novo;
    s->tamanho++;
    return 1;
}
int imprimir_sequencia(Sequencia* s){
    if(s == NULL) return 0;

    No* aux = s->inicio;
    while(aux != NULL){
        printf("[%d] [%.1f] [%d]\n",aux->id,aux->valor, aux->prox_id);
        aux = aux-> prox;
    }
    return 1;
}

Sequencia* cria_sequencia(){
    Sequencia* s = (Sequencia*) malloc(sizeof(Sequencia));
    if( s != NULL){
        s->inicio = NULL;
        s->fim = NULL;
        s->tamanho = 0;
    }
    return s;

}
No* buscaporid (Sequencia* s, int procurado){
    if( s == NULL || s->inicio == NULL) return NULL;
    No* aux = s->inicio;
    while(aux != NULL){
        if(aux->id == procurado){
            return aux;
        }
        aux = aux->prox;

    }
    return NULL;
}
Sequencia* recupera_sequencia(Sequencia* s){
    if( s == NULL || s->inicio == NULL) return NULL;
    Sequencia* recsec = cria_sequencia();

    No* noatual = s->inicio;
    inserir_final(recsec, noatual->valor, noatual->id, noatual->prox_id);
    noatual = buscaporid(s, noatual->prox_id);
    while(noatual != NULL){

        inserir_final(recsec, noatual->valor, noatual->id, noatual->prox_id);
        noatual = buscaporid(s, noatual->prox_id);

    }
    return recsec;
}
int imprimir_sequenciarec(Sequencia* s){
    if(s == NULL) return 0;

    No* aux = s->inicio;
    while(aux != NULL){
        printf("%.1f,", aux->valor);
        aux = aux-> prox;
    }
    return 1;
}

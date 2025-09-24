#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _no{
    int info1;
    int info2;
    no* prox;
}no;

typedef struct _lista{
    no* inicio;
    no* fim;
    int tamanho;

}Lista;
Lista* cria_lista(){
    Lista* l = (Lista*) malloc(sizeof(Lista));
    if (l != NULL) {
        l->inicio = NULL;
        l->fim = NULL;
    }
    return l;
}
int inserir_final( Lista* l, int valor ) {
    if( l == NULL ) return 0;
    no* novo = (no*) malloc(sizeof(no));
    if( novo == NULL ) return 0;

    novo->info1 = valor;
    novo->prox = NULL;

    if (l->inicio == NULL) {
        l->inicio = novo;
    } else {
        l->fim->prox = novo;
    }
        l->fim = novo;
    return 1;

}
int inserir_finaldec(Lista* l, int valor1, int valor2) {
    if (l == NULL) return 0;
    no* novo = (no*) malloc(sizeof(no));
    if (novo == NULL) return 0;

    novo->info1 = valor1;
    novo->info2 = valor2;
    novo->prox = NULL;

    if (l->inicio == NULL) {
        l->inicio = novo;
    } else {
        l->fim->prox = novo; // Use o ponteiro 'fim' diretamente
    }
    l->fim = novo; // Atualize o ponteiro 'fim'
    return 1;
}
void imprimir_listacod(Lista* l) {
    if (l == NULL || l->inicio == NULL) {
        printf("Lista vazia\n");
        return;
    }

    no* aux = l->inicio;
    while (aux != NULL) {
        printf("(%d, %d) ", aux->info1, aux->info2);
        aux = aux->prox;
    }
    printf("\n");
}
void imprimir_listadec(Lista* l) {
    if (l == NULL || l->inicio == NULL) {
        printf("Lista vazia\n");
        return;
    }

    no* aux = l->inicio;
    while (aux != NULL) {
        printf("%d ", aux->info1);
        aux = aux->prox;
    }
    printf("\n");
}
Lista* codifica_listabinaria(Lista* l) {
    if (l == NULL || l->inicio == NULL) return NULL;
    
    Lista* cod = cria_lista();
    if (cod == NULL) return NULL;

    no* aux = l->inicio;
    while (aux != NULL) {
        int digito_atual = aux->info1;
        int contagem = 0;

        // Loop para contar a sequência do dígito atual
        while (aux != NULL && aux->info1 == digito_atual) {
            contagem++;
            aux = aux->prox; // Avança o ponteiro na lista original
        }
        
        // Insere o par (dígito, contagem) na lista codificada
        inserir_finaldec(cod, digito_atual, contagem);
    }
    
    // Não se esqueça de retornar a lista criada!
    return cod;
}
Lista* decodifica_listabinaria(Lista* l){
    if (l == NULL || l->inicio == NULL) return NULL;
    
    Lista* dec = cria_lista();
    if (dec == NULL) return NULL;

    no* aux = l->inicio;
    while (aux != NULL){
        int digito_atual = aux->info2;
        int contagem = aux->info1;

        for (int i = 0; i < contagem; i++){
            inserir_final(dec, digito_atual);
        }
        aux = aux->prox;
    }
    return dec;
}
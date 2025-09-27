#include "intbacanas.h"
#include <stdio.h>
#include <stdlib.h>

struct _no{
    int info;
    No* prox;
};
struct _bacanas{
    No* inicio;
    No* fim;
    int tamanho;
};

Bacanas* cria_bacana(){
    Bacanas* b = (Bacanas*) malloc(sizeof(Bacanas));
    if(b != NULL){
        b->inicio = NULL;
        b->fim = NULL;
        return b;
    }
    return 0;

}
int inserir_algarismos(Bacanas* b, int valor){
    if(b == NULL) return 0;
    
    int temp = valor;
    while(temp > 0){
        No* novo = (No*) malloc(sizeof(No));
        if(novo == NULL) return 0;
        int digito = temp % 10;
        novo->info = digito;
        novo->prox = b->inicio;
        novo->prox = b->inicio;
        b->inicio = novo;
        if(b->inicio != NULL)b->fim = novo;
        temp = temp / 10;
    }
    return 1;
}
void imprimir_lista(Bacanas* b) {
    if (b == NULL || b->inicio == NULL) {
        printf("Lista vazia\n");
        return;
    }

    No* aux = b->inicio;
    while (aux != NULL) {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}
int verifica_bacana(Bacanas* b){
    if (b == NULL || b->inicio == NULL) return 0;

    // Pega o número original da lista
    int numero_atual = 0;
    int multiplicador = 1;
    No* no_atual = b->inicio;
    while(no_atual != NULL){
        numero_atual += no_atual->info * multiplicador;
        multiplicador *= 10;
        no_atual = no_atual->prox;
    }

    // Loop para verificar se é bacana
    // O número 4 é o início de um ciclo comum para números não-bacanas
    while (numero_atual != 1 && numero_atual != 4) {
        int soma_quadrados = 0;
        int temp = numero_atual;
        while (temp > 0) {
            int digito = temp % 10;
            soma_quadrados += digito * digito;
            temp /= 10;
        }
        numero_atual = soma_quadrados;
    }

    if (numero_atual == 1) {
        return 1; // É bacana
    } else {
        return numero_atual; // Não é bacana
    }
}

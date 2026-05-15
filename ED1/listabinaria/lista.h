#ifndef LISTA_H
#define LISTA_H

typedef struct _no no;
typedef struct _lista Lista;

Lista* cria_lista();
int inserir_final(Lista* l, int valor);
int inserir_finaldec(Lista* l, int valor1, int valor2);
Lista* codifica_listabinaria(Lista* l);
Lista* decodifica_listabinaria(Lista* l);
void imprimir_listacod(Lista* l);
void imprimir_listadec(Lista* l);
void preencher_lista(Lista* l);

#endif //LISTA_H
#ifndef SEQUENCIA_H
#define SEQUENCIA_H

typedef struct _no No;
typedef struct _sequencia Sequencia;

Sequencia* cria_sequencia();
Sequencia* recupera_sequencia(Sequencia* s);
int inserir_final(Sequencia* s, float valor, int id, int proxid);
int imprimir_sequencia(Sequencia* s);
int imprimir_sequenciarec(Sequencia* s);


#endif 
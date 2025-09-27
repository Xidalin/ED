#ifndef INTBACANAS_H
#define INTBACANAS_H

typedef struct _no No;
typedef struct _bacanas Bacanas;

Bacanas* cria_bacana();
int verifica_bacana(Bacanas* b);
/*
*verificação se um número inteiro e positivo é ou não bacana; 
*Isso se dá quando somamos os quadrados de seus digitos,
*e fazendo essa operação sucessivamente,
*obtiver o número 1
*
*/
int inserir_final( Bacanas* b, int valor );
int inserir_algarismos(Bacanas* b, int a);
void imprimir_lista(Bacanas* b);

#endif //INTBACANAS_H
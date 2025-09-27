#include <stdio.h>
#include "sequencia.h"

int main(){
    Sequencia* s = cria_sequencia();
    inserir_final(s, 8.2, 1, 7);
    inserir_final(s, 8.6, 2, 0);
    inserir_final(s, 3.3, 3, 10);
    inserir_final(s, 1.6, 4, 9);
    inserir_final(s, 10.0, 5, 8);
    inserir_final(s, 9.5, 6, 5);
    inserir_final(s, 6.5, 7, 4);
    inserir_final(s, 0.4, 8, 2);
    inserir_final(s, 5.2, 9, 3);
    inserir_final(s, 2.5, 10, 6);

    imprimir_sequencia(s);

    printf("sequencia recuperada: \n");
    Sequencia* recsec = recupera_sequencia(s);
    imprimir_sequenciarec(recsec);


}  // teste
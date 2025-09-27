#include <stdio.h>
#include "intbacanas.h"

int main(){
    Bacanas* b1 = cria_bacana();
    inserir_algarismos(b1, 120);
    imprimir_lista(b1);
    int bresultado;
    if(bresultado = verifica_bacana(b1) == 1){
        printf("Resultado é um número bacana: %d\n", bresultado);
    }else{
        printf("Inteiro não-bacana: %d\n", bresultado);
    } 

}
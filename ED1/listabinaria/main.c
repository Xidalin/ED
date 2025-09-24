#include <stdio.h>
#include "lista.h"

int main(){
    
    //verificação do modo operacional do programa "c" "d" (codificação ou decodificação)
    printf("Digite 'c' para codificar ou 'd' para decodificar: \n");
    char modo;
    scanf(" %c", &modo);
    if (modo != 'c' && modo != 'd'){
        printf("Modo invalido. Digite 'c' para codificar ou 'd' para decodificar.\n");
        return 1;
    }
    if (modo == 'c'){
        Lista* lbin = cria_lista();

        int num;
        do{
            printf("Digite um numero entre 0 e 1:\n");
            scanf("%d", &num);
            if( num != 0 && num != 1) break;
            inserir_final(lbin, num);
        }while ( num == 0 || num == 1);

        lbin = codifica_listabinaria(lbin);
        printf("Lista codificada: \n");
        imprimir_listacod(lbin);

    }else if (modo == 'd'){
        Lista* ldec = cria_lista();

        int num1, num2;
        do{
            printf("Digite um par de numeros, sendo o segundo 0 ou 1:\n");
            scanf("%d %d", &num1, &num2);
            if( num2 != 0 && num2 != 1) break;
            inserir_finaldec(ldec, num1, num2);
        }while (num2 == 0 || num2 == 1);

        ldec = decodifica_listabinaria(ldec);
        printf("Lista decodificada: \n");
        imprimir_listadec(ldec);
    }

    return 0;
}
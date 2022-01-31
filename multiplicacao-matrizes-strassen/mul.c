#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"


int main(){    

    int entrada;
    int limite;

    clock_t comeco_t, fim_t; 
    double total_t;

    while(1){

        puts("Entre com um valor não positivo na dimensao para abortar");

        puts("Entre com a dimensão da matriz:");
        scanf("%d", &entrada);

        puts("Entre com o valor limite dos elementos da matriz:");
        scanf("%d", &limite);

        Matriz m1 = nova_matriz_rand(entrada, limite);
        Matriz m2 = nova_matriz_rand(entrada, limite);
        Matriz mx, my;

        if(entrada <= 0 || limite <= 0){
            exit(0);
        }

        comeco_t = clock();
        mx = strassen(&m1, &m2);

        if(mx.e == NULL){
            printf("A dimensão da matriz deve ser uma potencia de 2\n");           
            continue;
        }

        fim_t = clock();
        total_t = (double) (fim_t - comeco_t) / CLOCKS_PER_SEC;
        printf("Tempo gasto usando Strassen: %fs\n", total_t);

        comeco_t = clock();
        my = naive(&m1, &m2);

        fim_t = clock();
        total_t = (double) (fim_t - comeco_t) / CLOCKS_PER_SEC;
        printf("Tempo gasto usando a multiplicação tradicional: %fs\n", total_t);   

        //print(&mx);
        //print(&my);

        free(m1.e);
        free(m2.e);   
        free(mx.e); 
        free(my.e); 
 
        printf("\n");
    }

}
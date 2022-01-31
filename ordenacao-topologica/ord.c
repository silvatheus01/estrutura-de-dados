#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

// Definição de um Nó
struct No{
   int v;
   struct No *proxno;
};

// Dando um nome especial para struct No: No
typedef struct No No;

// Definição de um grafo
typedef struct{
   No **adj;
   int *gent, numv;
} Grafo;

Grafo criagrafo(){

    char tmp[MAX];

    Grafo grafo;

    No *noatual;

    /*l: linha atual que sendo lida
    vlido: Se 0, numero que representa o número de vértices no grafo (primeiro numero) não foi lido
        1 se foi lido
    aux: Variável que delimita o número de linhas que serão lidas, ou seja, v + 1
    nocb: Se 1, estamos no nó cabeça em grafo.adj[i], ou seja, o primeiro nó que é pai de todos os outros em grafo.adj[i]
        0 se não estivermos*/
    int l = 0, vlido = 0, aux, nocb = 1;

    do{

        fgets(tmp, MAX - 1, stdin);

        if(vlido == 0){

            //numero de vertices            
            long int v = strtol(tmp, NULL, 10);
            aux = v + 1;

            // Definindo dimensões do grafo
            grafo.adj = (No**) malloc(sizeof(No*) * v);
            grafo.gent = (int*) malloc(sizeof(int) * v);
            grafo.numv = v;

            for (int i = 0; i < v; i++)
            {
                // Todos os vertices tem grau de entrada 0 no começo
                grafo.gent[i] = 0;
            }            

            vlido = 1;
            l++;
            aux--;

            continue;

        }else{

            char *token;
            token = strtok(tmp, " ");

            while(token != NULL){

                long int v = strtol(token, NULL, 10);

                if(v == 0) {

                    grafo.adj[(l-1)] = NULL;

                    break;

                }else if(nocb){

                    grafo.gent[v-1]++;

                    noatual = (No*) malloc(sizeof(No));

                    noatual->v = v;
                    noatual->proxno = NULL;
                    grafo.adj[(l-1)] = noatual;

                    nocb = 0;

                }else{

                    grafo.gent[v-1]++;
                    
                    No *novono;

                    novono = (No*) malloc(sizeof(No));

                    novono->v = v;
                    novono->proxno = NULL;
                    noatual->proxno = novono;
                    noatual = novono;  

                }

                token = strtok(NULL, " ");

            }

            l++;         
            aux--;
            nocb = 1;
        }

    }while(aux);  

    return grafo;

}

void printgf(Grafo grafo){

    
    for(int i = 0; i < grafo.numv; i++){

        printf("[%d]->", i + 1);

        No* noaux = (No*) malloc(sizeof(No));
        noaux = grafo.adj[i];

        while(noaux != NULL){
            
            printf("(%d)->", noaux->v);
            noaux = noaux->proxno; 
        }

        printf("\n");
    }    
}

void printge(Grafo grafo){

    printf("[");

    for(int i = 0; i < grafo.numv; i++){

        if(i == grafo.numv - 1){
            printf("%d", grafo.gent[i]);
            break;
        }

        printf("%d, ", grafo.gent[i]);
    }

    printf("]\n");
}

void ordtop(Grafo grafo){

    int *ord = (int*) malloc(sizeof(int) * grafo.numv);

    int pos = 0;

    for(int i = 0; i < grafo.numv; i++){
        if(grafo.gent[i] == 0){
            ord[pos] = i;
            pos++;
        }
    }

    int v;

    No* noaux = (No*) malloc(sizeof(No));

    for(int i = 0; i < pos; i++){

        noaux = grafo.adj[ord[i]];

        while(noaux != NULL){            

            v = noaux->v - 1;

            grafo.gent[v]--;

            if(grafo.gent[v] == 0){
                ord[pos] = v;
                pos++;
            } 

            noaux = noaux->proxno;
        }    
    }

    // Printa a ordenação
    if(pos == grafo.numv){

        //printf("[");

        for(int i = 0; i < grafo.numv; i++){

            /*if(i == grafo.numv - 1){
                printf("%d ", ord[i] + 1);
                break;
            }*/

            printf("%d ", ord[i] + 1);
        }

        printf("\n");

    }else{
        puts("Tem ciclo");
    }


}

int main(){

    Grafo grafo;

    //puts("Grafo:");

    grafo = criagrafo(/*arq*/);

    //printgf(grafo);

    // printf("\n");

    //puts("Lista de graus de entrada, do vetor 1 ao n:");
    //printge(grafo);

    // printf("\n");

    //puts("Resultado da ordenação no grafo:");
    ordtop(grafo);

    exit(0);
}
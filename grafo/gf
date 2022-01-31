#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct No{
   int v;
   struct No *proxno;
};

typedef struct No No;

typedef struct{
   No **adj;
   int *gent, numv;
} Grafo;

// Gera o grafo
Grafo criagrafo(FILE *arq){

    char tmp;

    Grafo grafo;

    No *noatual;

    int l = 0, s = 0, pl = 1, vlido = 0;

    while( (tmp = fgetc(arq)) != EOF){

        if(vlido == 0){

            //numero de vertices            
            int v = atoi(&tmp);

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

            continue;
        }        
       
        if(tmp == '\n'){
            l++;
            s = 1;
            pl = 0;
            continue;
        }

        if(tmp == '\n' && s == 1){

            int v = atoi(&tmp);

            noatual->v = v;
            noatual->proxno = NULL;
            grafo.adj[(l-1)] = noatual;

            s = 0;

            continue;
        }

        if(tmp != ' ' && pl == 0){

            int v = atoi(&tmp);

            grafo.gent[v-1]++;

            if(s == 1){

                noatual = (No*) malloc(sizeof(No));
                
                noatual->v = v;
                noatual->proxno = NULL;
                grafo.adj[(l-1)] = noatual;

                s = 0;

            }else{

                No *novono;

                novono = (No*) malloc(sizeof(No));

                novono->v = v;
                novono->proxno = NULL;
                noatual->proxno = novono;
                noatual = novono;              
                
            }            
    
        }

    }   

    return grafo;

}

// "Printa" o grafo
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

int main(){

    FILE *arq;
    arq = fopen("grafo", "r");

    if(arq == NULL || (fgetc(arq) == EOF) ){
        puts("Arquivo não pode ser aberto ou está vazio.");
        exit(-1);
    }

    Grafo grafo;

    grafo = criagrafo(arq);
    printgf(grafo);

}

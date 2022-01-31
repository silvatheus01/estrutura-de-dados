#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Grafo criagrafo(FILE *arq){

    char tmp;

    Grafo grafo;

    No *noatual;
    
    /*
    l: Linha atual de leitura no arquivo por fgetc
    s:  Sinal para que o programa crie um Nó em grafo.adj[l-1] se s = 1.
        Se s = 0, cria uma lista encadeada a partir do nó já criado
        em grafo.adj[l-1], ou seja, caso que ocorre quando o vértice aponta para 1 ou mais vértices
    pl:  Sinal que relata se a leitura está na primeira linha do arquivo,
        ou seja, na linha do numero de vértices e do numero de arestas
        pl = 1, está na primeira linha
        pl = 0, não está
    vlido: Se 1, numero de vértices já foi lido (primeiro caractere do arquivo)
        Senão, ainda não foi lido
    */ 

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
       
        // Pula para a próxima linha quando encontra em caractere de quebra de linha
        if(tmp == '\n'){
            l++;
            s = 1;
            pl = 0;
            continue;
        }

        // Caso que ocorre quando o vertice não aponta para nenhum outro vértice
        if(tmp == '\n' && s == 1){

            int v = atoi(&tmp);

            noatual->v = v;
            noatual->proxno = NULL;
            grafo.adj[(l-1)] = noatual;

            s = 0;

            continue;
        }

        // Caso que ocorre quando o programa lê um vertice que está sendo apontado por outro
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

        printf("[");

        for(int i = 0; i < grafo.numv; i++){

            if(i == grafo.numv - 1){
                printf("%d", ord[i] + 1);
                break;
            }

            printf("%d, ", ord[i] + 1);
        }

        printf("]\n");

    }else{
        puts("Tem ciclo");
    }


}

int main(){

    FILE *arq;
    arq = fopen("grafo", "r");

    if(arq == NULL){
        puts("O arquivo não pode ser aberto");
        exit(-1);
    }else{

        char teste = fgetc(arq);

        if(teste == EOF){
            puts("O arquivo está vazio.");
            exit(-1);
        }else{
            ungetc(teste, arq);
        }
    }

    Grafo grafo;

    puts("Grafo:");

    grafo = criagrafo(arq);

    printgf(grafo);

    printf("\n");

    puts("Lista de graus de entrada, do vetor 1 ao n:");
    printge(grafo);

    printf("\n");

    puts("Resultado da ordenação no grafo:");
    ordtop(grafo);

    exit(0);
}
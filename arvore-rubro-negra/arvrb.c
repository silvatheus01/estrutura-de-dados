#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dimensão padrão para varios vetores
#define DIM 20

enum _Cor {Vermelho, Preto};
typedef enum _Cor Cor;

struct _No{
    long int chave;
    struct _No *esq, *dir, *pai;
    Cor cor;
};

typedef struct _No No;

long int chaves[DIM];

void preordem(No *raiz){
    if(raiz->chave != 0){
        printf("%ld%c ", raiz->chave, raiz->cor == Vermelho ? 'R' : 'N');
        preordem(raiz->esq);
        preordem(raiz->dir);
    }
}

void getchaves(){

    char chave[DIM];   
    int i = 0;
    //int long aux;

    while (fgets(chave, DIM - 1, stdin) != NULL)
    {
        chaves[i] = strtol(chave, NULL, 10);       
        i++;
    }   


}

No *rotesq(No *raiz, No *pivo) {

    No *y;

    y = pivo->dir;
    pivo->dir = y->esq;

    y->esq->pai = pivo;
    y->pai = pivo->pai;
    
    if (pivo->pai == NULL) {
        raiz = y;
    } else if (pivo == pivo->pai->esq) {
        pivo->pai->esq = y;
    } else {
        pivo->pai->dir = y;
    }

    y->esq = pivo;
    pivo->pai = y;

    return raiz;

}

No *rotdir(No *raiz, No *pivo) {

    No *y;

    y = pivo->esq;
    pivo->esq = y->dir;
    
    y->dir->pai = pivo;
    y->pai = pivo->pai;
    
    if (pivo->pai == NULL) {
        raiz = y;
    } else if (pivo == pivo->pai->dir) {
        pivo->pai->dir = y;
    } else {
        pivo->pai->esq = y;
    }

    y->dir = pivo;
    pivo->pai = y;

    return raiz;
}

No *conserta(No *raiz, No *novo){

    if(novo == raiz){        
        return raiz;
    }else if(novo->pai->pai == NULL){
        raiz->cor = Preto;
    }

    while (novo->pai->cor == Vermelho) {

        if (novo->pai == novo->pai->pai->esq) {

            No *tio = novo->pai->pai->dir;        
        
            if (tio->cor == Vermelho) {

                novo->pai->cor = Preto; 
                tio->cor = Preto;
                novo->pai->pai->cor = Vermelho; 
                novo = novo->pai->pai;

            }else{

                if(novo == novo->pai->dir){
                    novo = novo->pai;
                    raiz = rotesq(raiz, novo); 
                }
                

                novo->pai->cor = Preto; 
                novo->pai->pai->cor = Vermelho;
                raiz = rotdir(raiz, novo->pai->pai);               

            }
            
            
        }else{
            
            No *tio = novo->pai->pai->esq;

            if(tio->cor == Vermelho){

                novo->pai->cor = Preto; 
                tio->cor = Preto;
                novo->pai->pai->cor = Vermelho;
                novo = novo->pai->pai;

                if(novo->pai == NULL){
                    return raiz;
                }


            }else{

                if(novo == novo->pai->esq){
                    novo = novo->pai;
                    rotdir(raiz, novo);
                }                     
                
                
                novo->pai->cor = !novo->pai->cor;
                novo->pai->pai->cor = !novo->pai->pai->cor;
                raiz = rotesq(raiz, novo->pai->pai);            

            }
            


        }

    }   

    return raiz;
       
}   

No *insere(No *raiz, No *novo){
    No *pai = NULL;
    No *atual = raiz;

    //busca a posicao na árvore
    while (atual->chave != 0) {
        pai = atual;
        atual = (novo->chave < atual->chave) ? atual->esq : atual->dir;
    }

    novo->pai = pai;

    novo->esq = (No*) malloc(sizeof(No));
    novo->dir = (No*) malloc(sizeof(No));

    novo->esq->cor = Preto;
    novo->dir->cor = Preto;

    novo->esq->chave = 0;
    novo->dir->chave = 0;

    novo->cor = Vermelho;

    if (pai == NULL) raiz = novo;
    else if (novo->chave < pai->chave) pai->esq = novo;
    else pai->dir = novo;

    raiz = conserta(raiz, novo);

    return raiz;
}

No *arvrb(long int *chaves){
   
    No *raiz = (No*) malloc(sizeof(No));
    raiz->chave = 0;

   for (int i = 0; chaves[i] != 0; i++){
        No *novo;
        novo = (No*) malloc(sizeof(No));
        novo->chave = chaves[i];

        raiz = insere(raiz, novo);
    }

    return raiz;

}


int main(){

    getchaves();
    No *raiz;
    raiz = arvrb(chaves);

    preordem(raiz);

    printf("\n");
    
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct No{
    int valor, rank;
    struct No* pai;
};

typedef struct No No;

#define DIM 50001
#define LIM 12

No *find(No *no){
    if(no->pai == no){
        return no;
    }else{
        return find(no->pai);
    }
}

int uni(int i, int j, No **set){

    if(set[i]->pai == set[i] && set[j]->pai == set[j]){
        set[j]->pai = set[i];
        set[i]->rank++;
        return 1;
    }else{

        set[i]->pai = find(set[i]);
        set[j]->pai = find(set[j]);

        if(set[i]->pai == set[j]->pai){
            return 0;
        }else if(set[i]->rank > set[j]->rank){
            set[j]->pai->pai = set[i];
            set[j]->pai = set[i];
            set[i]->rank++;
        }else{
            set[i]->pai->pai = set[j];
            set[i]->pai = set[j];
            set[j]->rank++;
        }

        return 1;

    }

    
}

int main(){

    char buf[LIM], *token;
    No *set[DIM];
    int n, m, i, j, rel, caso, res[DIM];

    caso = -1;
    
    while(1){
        fgets(buf, LIM, stdin);    

        token = strtok(buf, " ");
        n = strtol(token, NULL, 10);

        token = strtok(NULL, " ");
        m = strtol(token, NULL, 10);

        if(!n || !m) break;

        rel = n;

        for(int i = 1; i <= n; i++){
            No *novo = (No*) malloc(sizeof(No*));
            set[i] = novo;
            set[i]->pai = set[i];
            set[i]->valor = i;
            set[i]->rank = 0;
        }

        for (int k = 1; k <= m; k++)
        {
            fgets(buf, LIM, stdin);

            token = strtok(buf, " ");
            i = strtol(token, NULL, 10);

            token = strtok(NULL, " ");
            j = strtol(token, NULL, 10);

            if(uni(i, j, set)){
                rel--;
            }

        }

        caso++;
        res[caso] = rel;
        
    }

    for (int i = 0; i <= caso; i++)
    {
        printf("Case %d: %d\n", i + 1, res[i]);
    }
 
}

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "matriz.h"

// Retorna a posição de um elemento na matriz
int gete(Matriz *m, int i, int j){
    return j + i*(m->d);
}

Matriz nova_matriz(int n){
    Matriz m;
    m.d = n;

    int num_elementos = n*n; 

    // Criando um vetor de ponteiros
    m.e = (int*) malloc(num_elementos*sizeof(int));
    
    // Popula a matriz m com 0's
    for (register int i = 0; i < num_elementos; i++)
    {           
        m.e[i] = 0;
    }   

    return m;

}

Matriz nova_matriz_rand(int n, int limite){
    
    Matriz m;

    m.d = n;

    int num_elementos = n*n; 
    
    // Criando um vetor de ponteiros
    m.e = (int*) malloc(num_elementos*sizeof(int));
    
    // Popula a matriz nova matriz 
    for (register int i = 0; i < num_elementos; i++)
    {            
        // Iniciamos o gerador de numeros aleatorios com uma semente
        srand(clock());
        
        // Variavel sinal será 0 ou 1 pela definição de modulo
        int sinal = rand() % 2;

        // Se for 0, subtraimos 1, então sinal = -1 
        // se não, sinal = 1
        if (sinal == 0) sinal--;

        // Aqui multiplicamos o sinal pelo numero,
        // dessa forma ele será negativo ou positivo dependendo da função rand
        m.e[i] = sinal*(rand() % limite);
    }
   

    return m;
    
}

Matriz reparte(Matriz *m, int linha, int coluna){
    
    Matriz matriz;

    int l = linha;
    int c = coluna;

    // A dimensão da nova matriz será a metade da matriz particionada
    matriz.d = m->d / 2;

    int num_elementos = matriz.d * matriz.d;

    /*Cria um vetor de ponteiros*/
    matriz.e = (int*) malloc(num_elementos*sizeof(int));
    
    // Popula a nova matriz particiona com os elementos da matriz m
    for (register int i = 0, linha = l ; i < matriz.d; i++, linha++)
    {        
        for (register int j = 0, coluna = c; j < matriz.d; j++, coluna++)
        {            
            matriz.e[gete(&matriz, i, j)] = m->e[gete(m, linha, coluna)];
        }
  
    } 

    // Retorna a matriz particionada
    return matriz;
}

// Une as quatro matrizes em uma
Matriz une(Matriz *m00, Matriz *m01, Matriz *m10, Matriz *m11){

    // Dimensão da matriz pai é o dobro da dimensão da matriz filho
    int dpai = m00->d*2;

    int dfilho = m00->d;
    
    Matriz m = nova_matriz(dpai);

    for (register int i = 0, k = dfilho; i < dfilho; i++, k++)
    {
       for (register int j = 0, l = dfilho; j < dfilho; j++, l++)
       {
           m.e[gete(&m, i, j)] = m00->e[gete(m00, i, j)];
           m.e[gete(&m, i, l)] = m01->e[gete(m01, i, j)];
           m.e[gete(&m, k, j)] = m10->e[gete(m10, i, j)];
           m.e[gete(&m, k, l)] = m11->e[gete(m11, i, j)];
       }
       
    }

    return m;
    
}

Matriz soma(Matriz *m1, Matriz *m2){
    Matriz m = nova_matriz(m1->d);

    for (register int i = 0; i < m.d; i++)
    {
        for (register int j = 0; j < m.d; j++)
        {
            m.e[gete(&m, i, j)] = m1->e[gete(m1, i, j)] + m2->e[gete(m2, i, j)];
        }
        
    }

    return m;
    
}

Matriz subtrai(Matriz *m1, Matriz *m2){
    Matriz m = nova_matriz(m1->d);

    for (register int i = 0; i < m.d; i++)
    {
        for (register int j = 0; j < m.d; j++)
        {
            m.e[gete(&m, i, j)] = m1->e[gete(m1, i, j)] - m2->e[gete(m2, i, j)];
        }
        
    }

    return m;

}

//Abordagem tradicional de multiplicação iterativa
Matriz multrad(Matriz *m1, Matriz *m2){
     
    Matriz m = nova_matriz(m1->d);  

    for (int i = 0; i < m1->d; i++)
    {
        
        for (int j = 0; j < m1->d; j++)
        { 
            
            for (int k = 0; k < m1->d; k++)
            {
               
               m.e[gete(&m, i, j)] += m1->e[gete(m1, i, k)] * m2->e[gete(m2, k, j)];
            }            
        }
        
    }

    return m;
    
}

// Abordagem tradicional de multiplicação recursiva
Matriz naive(Matriz *m1, Matriz *m2){
    // Caso base, ou seja, d = 1
    if(m1->d == 1){
        Matriz m = nova_matriz(1);
        m.e[gete(&m, 0, 0)] = m1->e[gete(m1, 0, 0)] * m2->e[gete(m2, 0, 0)];
        return m;
    } 

    // Serão as partições da matriz m1
    Matriz mr100, mr101, mr110, mr111;
    // Serão as partições da matriz m2
    Matriz mr200, mr201, mr210, mr211;

    // Dimensão da matriz filho será a metade da matriz pai
    int dfilho = m1->d / 2;

    mr100 = reparte(m1, 0, 0);
    mr101 = reparte(m1, 0, dfilho);
    mr110 = reparte(m1, dfilho, 0);
    mr111 = reparte(m1, dfilho, dfilho);

    mr200 = reparte(m2, 0, 0);
    mr201 = reparte(m2, 0, dfilho);
    mr210 = reparte(m2, dfilho, 0);
    mr211 = reparte(m2, dfilho, dfilho);    

    Matriz aux1, aux2, aux3, aux4, aux5, aux6, aux7, aux8;

    aux1 = naive(&mr100, &mr200);
    aux2 = naive(&mr101, &mr210);

    aux3 = naive(&mr100, &mr201);
    aux4 = naive(&mr101, &mr211);

    aux5 = naive(&mr110, &mr200);
    aux6 = naive(&mr111, &mr210);

    aux7 = naive(&mr110, &mr201);
    aux8 = naive(&mr111, &mr211);

    Matriz c00, c01, c10, c11;

    c00 = soma(&aux1, &aux2);
    c01 = soma(&aux3, &aux4);
    c10 = soma(&aux5, &aux6);
    c11 = soma(&aux7, &aux8);
    
    free(mr100.e);     
    free(mr101.e);
    free(mr110.e);
    free(mr111.e);

    free(mr200.e);
    free(mr201.e);
    free(mr210.e);
    free(mr211.e);

    free(aux1.e);
    free(aux2.e);
    free(aux3.e);
    free(aux4.e);
    free(aux5.e);
    free(aux6.e);
    free(aux7.e);
    free(aux8.e);
    
    // Une o resultado da multiplicação com as sub-matrizes em uma matriz pai e retorna
    return une(&c00, &c01, &c10, &c11);
}

// Implementação de strassen sem testar a dimensão das matrizes
Matriz strasseni(Matriz *m1, Matriz *m2){

    // Caso base, ou seja, d = 1
    if(m1->d == 1){
        Matriz m = nova_matriz(1);
        m.e[gete(&m, 0, 0)] = m1->e[gete(m1, 0, 0)] * m2->e[gete(m2, 0, 0)];
        return m;

    }else if(m1->d <= 16){
        // Se a dimensão da matriz for menor ou igual a 16
        // o programa parte para a abordagem tradicional, pois é mais rapida no caso
        return naive(m1, m2);
    }

    // Serão as partições da matriz m1
    Matriz mr100, mr101, mr110, mr111;
    // Serão as partições da matriz m2
    Matriz mr200, mr201, mr210, mr211;

    // Dimensão da matriz filho será a metade da matriz pai
    int dfilho = m1->d / 2;

    mr100 = reparte(m1, 0, 0);
    mr101 = reparte(m1, 0, dfilho);
    mr110 = reparte(m1, dfilho, 0);
    mr111 = reparte(m1, dfilho, dfilho);

    mr200 = reparte(m2, 0, 0);
    mr201 = reparte(m2, 0, dfilho);
    mr210 = reparte(m2, dfilho, 0);
    mr211 = reparte(m2, dfilho, dfilho);    

    Matriz sm1, sm2, sm3, sm4, sm5, sm6, sm7;

    Matriz aux1, aux2, aux3, aux4, aux5, aux6, aux7, aux8, aux9, aux10;

    aux1 = soma(&mr100, &mr111);
    aux2 = soma(&mr200, &mr211);
    
    aux3 = soma(&mr110, &mr111);
    aux4 = subtrai(&mr201, &mr211);
    aux5 = subtrai(&mr210, &mr200);
    aux6 = soma(&mr100, &mr101);
    aux7 = subtrai(&mr110, &mr100);
    aux8 = soma(&mr200, &mr201);
    aux9 = subtrai(&mr101, &mr111);
    aux10 = soma(&mr210, &mr211);

    sm1 = strasseni(&aux1, &aux2);
    sm2 = strasseni(&aux3, &mr200);
    sm3 = strasseni(&mr100, &aux4);
    sm4 = strasseni(&mr111, &aux5);
    sm5 = strasseni(&aux6, &mr211);
    sm6 = strasseni(&aux7, &aux8);
    sm7 = strasseni(&aux9, &aux10);
    
    free(mr100.e);     
    free(mr101.e);
    free(mr110.e);
    free(mr111.e);

    free(mr200.e);
    free(mr201.e);
    free(mr210.e);
    free(mr211.e);

    free(aux1.e);
    free(aux2.e);
    free(aux3.e);
    free(aux4.e);
    free(aux5.e);
    free(aux6.e);
    free(aux7.e);
    free(aux8.e);
    free(aux9.e);
    free(aux10.e);

    Matriz c00, c01, c10, c11;

    c00 = nova_matriz(sm1.d);
    c01 = nova_matriz(sm1.d);
    c10 = nova_matriz(sm1.d);
    c11 = nova_matriz(sm1.d);

    for (register int i = 0; i < sm1.d; i++)
    {
        for (register int j = 0; j < sm1.d; j++)
        {
            c00.e[gete(&c00, i, j)] = sm1.e[gete(&sm1, i, j)] + sm4.e[gete(&sm4, i, j)] - sm5.e[gete(&sm5, i, j)] + sm7.e[gete(&sm7, i, j)];
            c01.e[gete(&c01, i, j)] = sm3.e[gete(&sm3, i, j)] + sm5.e[gete(&sm5, i, j)];
            c10.e[gete(&c10, i, j)] = sm2.e[gete(&sm2, i, j)] + sm4.e[gete(&sm4, i, j)];
            c11.e[gete(&c11, i, j)] = sm1.e[gete(&sm1, i, j)] - sm2.e[gete(&sm2, i, j)] + sm3.e[gete(&sm3, i, j)] + sm6.e[gete(&sm6, i, j)];             

        }
        
    }

    free(sm1.e); 
    free(sm2.e);
    free(sm3.e);
    free(sm4.e);
    free(sm5.e);
    free(sm6.e);
    free(sm7.e);

    
    // Une o resultado da multiplicação com as sub-matrizes em uma matriz pai e retorna
    return une(&c00, &c01, &c10, &c11);
    
}

// Strassen com o teste de dimensão
Matriz strassen(Matriz *m1, Matriz *m2){
    
    
    // Testa se m1.d é potencia de 2. 
    for (int i = m1->d; i != 1; i = i / 2)
    {
        // Se não for, retorna uma matriz com uma unica linha nula
        if(i % 2 != 0){
            Matriz m = nova_matriz(1);
            m.e = NULL;
            return m;
        }
    }

    return strasseni(m1, m2);    
    
}

void print(Matriz *m){
    for (int i = 0; i < m->d; i++)
    {
        for (int j = 0; j < m->d; j++)
        {
            printf("[%d][%d] = %d\n", i, j, m->e[gete(m, i, j)]);
        }
        
    }
    printf("Dimensão: %d\n", m->d); 
}
#ifndef MATRIZ_H
#define MATRIZ_H

/* Define uma matriz
Possui uma dimensão d
e elementos e[i][j], onde i e j representam juntos as posições na matriz.
i e j estão em um intervalo de 0 a d-1;
*/
typedef struct{
    int *e;
    int d;

} Matriz;

int gete(Matriz *m, int i, int j);

// Retorna uma nova matriz com e[i][j] = 0
Matriz nova_matriz(int n);

/* Retorna uma nova matriz com elementos randomicos
no intervalo -(limite - 1) a +(limite - 1)*/
Matriz nova_matriz_rand(int n, int limite);

/* Retorna m1 * m2 através do algoritmo tradicional de multiplicação de matrizes*/
Matriz multrad(Matriz *m1, Matriz *m2);

/* Reparte uma matriz m a partir de linha e coluna dados.
O corte e feito da esquerda para a direita, de cima para baixo*/
Matriz reparte(Matriz *m, int linha, int coluna);

/* Retorna uma matriz que é união de 4 sub-matrizes.*/
Matriz une(Matriz *m00, Matriz *m01, Matriz *m10, Matriz *m11);

// Retorna m1 + m2
Matriz soma(Matriz *m1, Matriz *m2);

// Retorna m1 - m2
Matriz subtrai(Matriz *m1, Matriz *m2);

Matriz strasseni(Matriz *m1, Matriz *m2);

// Retorna m1 * m2 através do algoritmo de strassen
Matriz strassen(Matriz *m1, Matriz *m2);

// Abordagem tradicional de multiplicação recursiva
Matriz naive(Matriz *m1, Matriz *m2);

// Printa todos os elementos da matriz m;
void print(Matriz *m);

#endif

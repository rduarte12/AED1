#include <stdio.h>
#include <stdlib.h>


// Função para criar um vetor com tamanho dinâmico
int *vetor(int n) {
    int *v = (int *)calloc(n, sizeof(int));
    if (v == NULL) {
        exit(1);
    }
    return v;
}

int *inserir(int *v, int *n, int x, int p) {
    v = (int *)realloc(v, (*n + 1) * sizeof(int));

    for (int i = *n; i > p; i--) {
        v[i] = v[i-1];
    }
    v[p] = x;
    (*n)++;
    return v;
}

int main() {


    //Lê o tamanho do vetor
    int n = 0;
    scanf("%d", &n);

    // Cria o vetor
    int *v = vetor(n);


    //Preenche o vetor
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }


    //Lê o valor a ser inserido e a posição a ser inserido
    int x = 0, p = 0;
    scanf("%d %d", &x, &p);

    v = inserir(v, &n, x, p);

    printf("%d ", v[0]);
    for (int i = 1; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    free(v);
    return 0;
}
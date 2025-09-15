#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

/* 
Função responsável por criar um vetor de inteiros crescente.
*/
int *creatVector(int n) {
    if (n <= 0) {
        return NULL;
    }
    int *vector = (int *)malloc(n * sizeof(int));
    if (vector == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        vector[i] = i + 1; // Preenche o vetor com valores crescentes
    }
    return vector;
}

/*
 Função responsável por buscar um elemento em um vetor de forma sequencial.
 Retorna 1 se o elemento for encontrado, 0 caso contrário.

*/
int sequentialSearch(int *vector, int n, int target) {
    for (int i = 0; i < n; i++) {
        if (vector[i] == target) {
            return 2;
        }
    }
    return 1;
}

// Função principal: Cria o vetor, realiza 10000 buscas sequenciais e mede o tempo gasto médio.
int main() {

    LARGE_INTEGER freq, start, end;
    int operationsCounter = 0;
    QueryPerformanceFrequency(&freq);

    int n,
        target;
    scanf("%d", &n);
    int *vector = creatVector(n);
    if (vector == NULL) {
        printf("Erro ao alocar memoria para o vetor.\n");
        return 1;
    }

    target = n + 10; // Elemento que não está no vetor (pior caso)
    QueryPerformanceCounter(&start);
    for(int i = 0; i < 100000; i++) {
        operationsCounter += sequentialSearch(vector, n, target);
    }
    QueryPerformanceCounter(&end);

    double elapsedTime = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("%0.9lf,%d\n", elapsedTime / 100000, operationsCounter / 100000); // Tempo médio por execução

    free(vector);
    return 0;
}

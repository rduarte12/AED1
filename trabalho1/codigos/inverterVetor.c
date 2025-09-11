#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

/*
    Função responsável por inverter um vetor de inteiros.
    Input: Vetor de inteiros, tamanho do vetor.
    Output: Novo vetor com os elementos na ordem inversa.

    Parâmetros:
        vector: vetor de inteiros a ser invertido.
        n: tamanho do vetor.

    Descrição:
        - Verifica se o tamanho do vetor é válido e se o ponteiro não é nulo.
        - Aloca memória para um novo vetor.
        - Copia os elementos do vetor original para o novo vetor na ordem inversa.
        - Retorna o novo vetor.
*/

int* invertVector(int *vector, int n, int *operationsCounter) {
    if (n <= 0 || vector == NULL) return NULL;
    int *newVector = (int*)malloc(n * sizeof(int));
    if (newVector == NULL) return NULL;
    for (int i = 0; i < n; i++) {
        newVector[i] = vector[n - 1 - i];
        (*operationsCounter)++;
    }
    return newVector;
}

/*
    Função responsável por liberar a memória alocada para um vetor de inteiros.
    Input: Vetor de inteiros.
    Output: Nenhum.

    Parâmetros:
        vector: vetor de inteiros a ser liberado.

    Descrição:
        - Verifica se o ponteiro não é nulo.
        - Libera a memória alocada para o vetor.
*/

void freeVector(int *vector) {
    if (vector != NULL) {
        free(vector);
    }
}

/*
    Função responsável por criar um vetor de inteiros,
    seguindo o pior caso para essa função.
    Input: Tamanho do vetor.
    Output: Ponteiro para o vetor criado.
*/

int *createVector(int n) {
    if (n <= 0) {
        return NULL;
    }
    int *vector = (int *)malloc(n * sizeof(int));
    if (vector == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        vector[i] = n - i; // Pior caso: vetor em ordem decrescente
    }
    return vector;
}

int main () {

    LARGE_INTEGER freq, start, end;
    int operationsCounter = 0;
    QueryPerformanceFrequency(&freq);

    int n;
    scanf("%d", &n);
    int *vector = createVector(n);
    if (vector == NULL) {
        printf("Erro ao alocar memoria para o vetor.\n");
        return 1;
    }
    QueryPerformanceCounter(&start);

    for(int i = 0; i < 100; i++) {
        int *invertedVector = invertVector(vector, n, &operationsCounter);
        if (invertedVector == NULL) {
            printf("Erro ao alocar memoria para o vetor invertido.\n");
            freeVector(vector);
            return 1;
        }
        freeVector(invertedVector);
    }

    QueryPerformanceCounter(&end);

    // Medir o tempo de execução da função em inteiros
    double elapsedTime = (double)(end.QuadPart - start.QuadPart)/freq.QuadPart;
    printf("%0.9lf,%d\n", elapsedTime/100, operationsCounter/100); // Tempo médio por execução

    // Liberar a memória alocada
    freeVector(vector);
    return 0;
}
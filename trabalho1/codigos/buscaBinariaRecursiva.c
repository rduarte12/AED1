#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

int rBinarySearch(int *vector,  int l, int r, int target) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (vector[mid] == target) {
            return 0;
        } else if (vector[mid] > target) {
            return rBinarySearch(vector, l, mid - 1, target);
        } else {
            return rBinarySearch(vector, mid + 1, r, target);
        }
    }
    return 1;
}

/*
    Função responsável por criar um vetor ordenado crescente de inteiros.
    Input: Tamanho do vetor.
    Output: Ponteiro para o vetor criado.

    Parametros:
        n: tamanho do vetor a ser criado.
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

    for(int i = 0; i < 100000; i++) {
        int found = rBinarySearch(vector, 0, n - 1, -1); // Elemento que não existe no vetor
        if (!found) {
            printf("Encontrado.\n");
            freeVector(vector);
            return 1;
        }
    }

    QueryPerformanceCounter(&end);

    // Medir o tempo de execução da função em inteiros
    double elapsedTime = (double)(end.QuadPart - start.QuadPart)/freq.QuadPart;
    printf("%0.9lf,%d\n", elapsedTime/100000, operationsCounter/100000); // Tempo médio por execução

    // Liberar a memória alocada
    freeVector(vector);
    return 0;
}
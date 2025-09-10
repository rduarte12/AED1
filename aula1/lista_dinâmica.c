#include <stdio.h>
#include <stdlib.h>

// Lê um valor e o insere no final da lista.
void inserir(int **num, int *n) {
    *num = realloc(*num, sizeof(int) * (*n + 1));
    int d;
    scanf("%d", &d);
    (*num)[*n] = d;
    (*n)++;
}

// Remove o último elemento da lista.
void remover(int **num, int *n) {
    if (*n == 0) {
        return;
    }
    (*n)--;
    // Nota: realloc(ptr, 0) é equivalente a free(ptr).
    *num = realloc(*num, sizeof(int) * (*n));
}

// Imprime todos os elementos da lista.
void listar(int *num, int n) {
    if (n == 0) {
        return;
    }

    printf("%d", num[0]);
    for (int i = 1; i < n; i++) {
        printf(" %d", num[i]);
    }
    printf("\n");
}

// Calcula e exibe a soma e a média dos elementos.
void soma_media(int num[], int n) {
    if (n == 0) {
        return;
    }
    int soma = 0;
    for (int i = 0; i < n; i++) {
        soma += num[i];
    }
    printf("Soma = %d  Média = %.2f\n", soma, (float)soma / n);
}

// Ordena a lista em ordem crescente (Bubble Sort).
void ordenar(int num[], int n) {
    if (n < 2) {
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (num[j] > num[j + 1]) {
                int temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
            }
        }
    }
}

int main() {
    int *num = NULL;
    int n = 0;
    int opt;

    do {
        scanf("%d", &opt);

        switch (opt) {
            case 1:
                inserir(&num, &n);
                break;
            case 2:
                remover(&num, &n);
                break;
            case 3:
                listar(num, n);
                break;
            case 4:
                soma_media(num, n);
                break;
            case 5:
                ordenar(num, n);
                break;
            case 6:
                free(num);
                break;
        }

    } while (opt != 6);

    return 0;
}
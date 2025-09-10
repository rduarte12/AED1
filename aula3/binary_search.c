#include <stdio.h>
#include <stdlib.h>

void binarySearch(int vetor[], int tamanho, int l, int r, int valorBuscado) {
    if (l > r) {
        printf("Valor nao encontrado\n");
        return;
    }
    int mid = l + (r - l) / 2;

    if (vetor[mid] == valorBuscado) {
        printf("Valor encontrado na posicao: %d\n", mid);
        return;
    }

    if (vetor[mid] < valorBuscado) {
        binarySearch(vetor, tamanho, mid+1, r, valorBuscado);
    } else {
        binarySearch(vetor, tamanho, l, mid-1, valorBuscado);
    }
}

int main() {
    int n  = 0;
    scanf("%d", &n);

    int vector[n];

    for (int i = 0; i < n; i++) {
        int temp =0;
        scanf("%d", &temp);
        vector[i] = temp;
    }

    int valorBuscado = 0;
    scanf("%d", &valorBuscado);

    binarySearch(vector, n, 0, n-1, valorBuscado);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int soma(int *vetor, int n, int sum) {
    if (n == 0) {
        return sum;
    }
    
    if (vetor[n-1] % 2 == 0) {
        sum += vetor[n - 1];
    }
    return soma(vetor, n - 1, sum);
}



int main() {
    int *vetor = (int *)calloc(1, sizeof(int));

    int x;
    scanf("%d", &x);

    for (int i = 0; i < x; i++) {
        int temp = 0;
        scanf("%d", &temp);
        vetor[i] = temp;

        vetor = (int *)realloc(vetor, (i + 2) * sizeof(int));
    }

    printf("Soma dos pares: %d\n", soma(vetor, x, 0));

    free(vetor);
    return 0;
}


#include <stdio.h>

int fibonacci(int n) {
    printf("Entrando em fibonacci(%d)\n", n); // <-- Adicione aqui

    //caso base
    if (n == 0) {
        printf("Caso base atingido: fibonacci(%d) = 0\n", n);
        return 0;
    }
    if (n == 1) {
        printf("Caso base atingido: fibonacci(%d) = 1\n", n);
        return 1;
    }

    // calculo recursivo
    int resultado = fibonacci(n - 1) + fibonacci(n - 2);
    printf("Retornando de fibonacci(%d) = %d\n", n, resultado);
    return resultado;
}

int main() {
    int x;

    scanf("%d", &x);

    printf("Calculando fibonacci de %d...\n", x);

    printf("Resultado final: %d\n", fibonacci(x));
    return 0;
}
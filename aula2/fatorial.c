#include <stdio.h>
#include <stdlib.h>

// utilizei unsigned long long int para conseguir imprimir numeros inteiros de maior valor sem acontecer o estouro de memória

// função para calcular o fatorial
unsigned long long int fatorial(int n) {

    printf("Entrando em fatorial(%d)\n", n);

    // delimitando o caso base
    if (n == 0 || n == 1) {
        printf("Caso base atingido: fatorial(%d) = 1\n", n);
        return 1;
    }

    // cálculo do fatorial de maneira separada para podermos guardar o valor e imprimir
    unsigned long long int resultado = n * fatorial(n - 1);
    printf("Retornando de fatorial(%d) = %llu\n", n, resultado);
    return resultado;
}

int main() {
    int x = 0;

    scanf("%d", &x);

    printf("Calculando fatorial de %d...\n", x);
    printf("Resultado final: %llu", fatorial(x));
    return 0;
}
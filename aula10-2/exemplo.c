#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * Função parse_expressao
 * ----------------------
 * Recebe uma string contendo uma expressão em Notação Polonesa Reversa (RPN),
 * separada por espaços (exemplo: "3 4 + 2 * 7 /").
 *
 * A função percorre a string, separa cada "token" (número ou operador),
 * e imprime o que encontrou.
 */
void parse_expressao(const char *linha) {
    // Criamos uma cópia da string porque strtok modifica a original
    char buf[256];
    strncpy(buf, linha, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0'; // garante finalização com '\0'

    // strtok vai quebrar a string usando " " (espaço) como delimitador
    char *tok = strtok(buf, " ");
    while (tok != NULL) {
        /*
         * Se o primeiro caractere do token é um dígito (0–9),
         * assumimos que é um número inteiro.
         */
        if (isdigit(tok[0])) {
            int valor = atoi(tok); // converte string → inteiro
            printf("Número encontrado: %d\n", valor);
        } else {
            /*
             * Caso contrário, consideramos o token um operador.
             * Aqui aceitamos símbolos como +, -, *, /.
             */
            printf("Operador encontrado: %c\n", tok[0]);
        }

        // Pega o próximo token (ou NULL se acabou)
        tok = strtok(NULL, " ");
    }
}

int main() {
    char linha[256];

    printf("Digite a expressão em RPN (exemplo: 3 4 + 2 * 7 /):\n");

    // Lê a linha completa do usuário
    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        printf("Erro ao ler entrada.\n");
        return 1;
    }

    // Remove o '\n' que fgets pode deixar no final
    linha[strcspn(linha, "\n")] = '\0';

    // Chama o parser para processar a string
    parse_expressao(linha);

    return 0;
}

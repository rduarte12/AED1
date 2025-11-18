#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInt.h"

/*
    Funções para manipulação de números grandes (BigInt) utilizando listas encadeadas.

    Tipos:
    - BigInt: Estrutura que representa um número grande. (Armazena os dígitos em uma lista encadeada)
    - Node: Estrutura que representa um nó da lista encadeada (tres digitos mais o sinal, 
            com char para economizar espaço).

    Funções Principais:
    - BigInt* createBigInt(const char* str): Cria um BigInt a partir de uma string.
    - void freeBigInt(BigInt* bigInt): Libera a memória alocada para um BigInt.
    - void printBigInt(const BigInt* bigInt): Imprime o BigInt na saída padrão.
    - BigInt* addBigInt(const BigInt* a, const BigInt* b): Soma dois BigInts e retorna o resultado.
    - BigInt* subtractBigInt(const BigInt* a, const BigInt* b): Subtrai dois BigInts e retorna o resultado.
    - int* isGreaterThan(const BigInt* a, const BigInt* b): Compara dois BigInts e retorna verdadeiro se 'a' for maior que 'b'.
    - int* isEqualTo(const BigInt* a, const BigInt* b): Compara dois BigInts e retorna verdadeiro se forem iguais.
    - int* isLessThan(const BigInt* a, const BigInt* b): Compara dois BigInts e retorna verdadeiro se 'a' for menor que 'b'.
    - void printBigInt(const BigInt* bigInt): Imprime o BigInt na saída padrão.

    Funções Auxiliares:
    - Node* createNode(char unidade, char dezena, char centena, char sinal, int numDigitos);
    - int is_empty_BigInt(const BigInt *BigInt);
    - int insertNode(BigInt *bigInt, char unidade, char dezena, char centena, char sinal, int numDigitos);

    Observações:
         
        Padrão de retorno para funções:
        - Em caso de sucesso retorna o tipo da função ou 1.
        - Em caso de falha retorna NULL para funções que retornam ponteiros ou -1.
        - 

        Convenções e comportamento:
        - Os dígitos são armazenados em blocos de 3 caracteres (chars contendo '0'..'9').
        - A lista é ordenada do menos significativo (start) ao mais significativo (end).
          Ou seja: inserções em createBigInt devem acrescentar blocos do menos para o mais
          significativo; printBigInt imprime a partir de end para start.
        - O sinal é armazenado em cada nó por simplicidade; o nó mais significativo
          (end) define o sinal efetivo na impressão.
        - numDigitos indica quantos dígitos do bloco mais significativo são reais:
          1, 2 ou 3. Blocos intermediários sempre devem ter 3 dígitos (zeros à esquerda
          quando necessário).


*/


/*
    TODO:
    - Implementar:
        - addBigInt
        - subtractBigInt
        - isGreaterThan
        - isEqualTo
        - isLessThan
*/

// Definição das estruturas
typedef struct Node {
    char unidade;               // Armazena um dígito (0-9)
    char dezena;                // Armazena um dígito (0-9)
    char centena;               // Armazena um dígito (0-9)
    char sinal;                 // Armazena o sinal do número ('+' ou '-')  
    int numDigitos;             // Armazena o número de digitos preenchidos.    
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct BigInt {
    Node* start;                // Ponteiro para o início da lista encadeada    
    Node* end;                  // Ponteiro para o final da lista encadeada
    int size;                   // Tamanho da lista (número de digitos preenchidos)
} BigInt;


// Função para criar um nó
/*
    TODO:
    1. Alocar memória para um novo nó.
    2. Inicializar os campos do nó com os valores fornecidos.
    3. Retornar o ponteiro para o novo nó.
*/
Node* createNode(char unidade, char dezena, char centena, char sinal, int numDigitos) {

    Node *novoNo = (Node*)malloc(sizeof(Node));
    if(!novoNo) {
        return NULL;
    }

    novoNo->unidade = unidade;
    novoNo->dezena = dezena;
    novoNo->centena = centena;
    novoNo->sinal = sinal;
    novoNo->numDigitos = numDigitos;
    novoNo->next = NULL;
    novoNo->prev = NULL;
    return novoNo;
}

// Função para inserir um nó no final do BigInt
/*
    TODO:
    1. Criar um novo nó com os valores fornecidos.
    2. Verificar se a criação do nó foi bem-sucedida.
    3. Se a lista estiver vazia, definir o novo nó como início e fim.
    4. Caso contrário, inserir o novo nó no final da lista.
    5. Atualizar o tamanho da lista.
    6. Retornar 1 em caso de sucesso, -1 em caso de falha.
*/
int insertNode(BigInt *bigInt, char unidade, char dezena, char centena, char sinal, int numDigitos) {
    Node *novoNo = createNode(unidade, dezena, centena, sinal, numDigitos);
    if(!novoNo) {
        return -1; // Falha na alocação de memória
    }

    if(bigInt->start == NULL) {
        bigInt->start = novoNo;
        bigInt->end = novoNo;
    } else {
        bigInt->end->next = novoNo;
        novoNo->prev = bigInt->end;
        bigInt->end = novoNo;
    }

    bigInt->size++;
    return 1; // Sucesso
}

// Função para liberar a memória alocada para um BigInt

void freeBigInt(BigInt* bigInt) {
    if (bigInt == NULL) {
        return;
    }

    Node* current = bigInt->start;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(bigInt);
}

// função para remover zeros à esquerda de uma string
char *removeZeros(char *str) {
    int i = 0, j = 0;
    int sinal_presente = 0;

    // Verificar se o primeiro caractere é sinal
    if (str[0] == '+' || str[0] == '-') {
        sinal_presente = 1;
        i = 1; // início da análise após o sinal
    }

    // Avançar o índice i enquanto encontrar zeros após o sinal
    while (str[i] == '0') {
        i++;
    }

    // Se todos os caracteres forem zeros
    if (str[i] == '\0') {
        // String será somente "0", preservando sinal se tiver
        if (sinal_presente) {
            str[1] = '0';
            str[2] = '\0';
            str[0] = str[0];  // sinal mantido
        } else {
            str[0] = '0';
            str[1] = '\0';
        }
        return str;
    }

    // Se tem sinal, manter no começo
    if (sinal_presente) {
        str[0] = str[0]; // sinal já está no lugar, só copiar depois
        j = 1; // índice de destino após o sinal
    } else {
        j = 0; // índice de destino do começo
    }

    // Copiar os caracteres restantes para frente na string
    while (str[i] != '\0') {
        str[j++] = str[i++];
    }
    str[j] = '\0';

    return str;
}

// função recursiva que percorre a lista comparando os elementos de cada nó
// no jeito de verificar se 'a' é maior que 'b' (ambos positivos)
// se inverter a saída, verifico se a é menor que b
int isThan_rec(const Node *a, const Node *b) {
    if (a == NULL || b == NULL) return 0; //Caso base

    if (a->centena != b->centena ||
        a->dezena != b->dezena ||
        a->unidade != b->unidade) {

        if(a->centena > b->centena) {
            return 1;
        } else if (a->centena < b->centena) {
            return 0;
        } else if (a->dezena > b->dezena) {
            return 1;
        } else if (a->dezena < b->dezena) {
            return 0;
        } else if (a->unidade > b->unidade) {
            return 1;
        } else if (a->unidade < b->unidade) {
            return 0;
        }
    }

    return isThan_rec(a->next, b->next);
}
/*
    TODO para converter string para BigInt:
    1. Verificar o sinal do número (primeiro caractere da string).
    2. Eliminar zeros à esquerda.
    3. Contar o número de dígitos na string.
    4. Alocar memória para o BigInt com base no número de dígitos.
    5. separar os dígitos em grupos de três (centena, dezena, unidade) e armazená-los nos nós da lista encadeada.
    6. Retornar o BigInt criado.
*/

// Função para criar um BigInt a partir de uma string
/*
    TODO:
    1- Verificar se a string é nula ou vazia.
    2- Ignorar zeros à esquerda.
    3- Verificar o tamanho da string e quantidade de dígitos.
    4- Alocar memória para o BigInt.
    5- Preencher o BigInt com os dígitos da string.
    6- Retornar o BigInt criado.
*/
BigInt* createBigInt(char* str1) {

    // Verificar se a string é nula ou vazia
    if (str1 == NULL || strlen(str1) == 0) {
        return NULL;
    }

    // Criar uma cópia da string para manipulação
    char* str = (char*)malloc((strlen(str1) + 1) * sizeof(char));
    if (str == NULL) {
        return NULL; // Falha na alocação de memória
    }
    strcpy(str, str1);

    // Ignorar zeros à esquerda
    str = removeZeros(str);

    // verificar o tamanho da string e quantidade de dígitos
    int len = strlen(str);
    
    if (str[0] == '-' && len == 1) {
        return NULL; // String inválida
    }

    if (str[0] == '-' || str[0] == '+') {
        len--; // Desconsiderar o sinal para contar os dígitos
    }

    // Alocar memória para o BigInt
    BigInt* bigInt = (BigInt*)malloc(sizeof(BigInt));
    if (!bigInt) {
        return NULL; // Falha na alocação de memória
    }

    // Inicializar o BigInt
    bigInt->start = NULL;
    bigInt->end = NULL;
    bigInt->size = 0;
    char sinal = (str[0] == '-') ? '-' : '+';

    // Preencher o BigInt com os dígitos da string
    int i = (str[0] == '-' || str[0] == '+') ? 1 : 0; // Índice inicial para os dígitos

    // Loop para processar os digitos na string de tras para frente
    for (int j = len - 1; j >= 0; j -=3) {
        char unidade = '0';
        char dezena = '0';
        char centena = '0';
        int numDigitos = 0;

        // Unidade
        if (str[i+j] >= '0' && str[i+j] <= '9' && str[i+j] != '\0') { // Verifica se é um dígito válido (menor que 10, e se não é nulo)
            unidade = str[i+j];
            numDigitos++;
        } else {
            freeBigInt(bigInt);
            return NULL; // Caractere inválido na string
        }

        // Dezena
        if (j - 1 >= 0 && str[i+j-1] >= '0' && str[i+j-1] <= '9' && str[i+j-1] != '\0') { // Verifica se é um dígito válido (menor que 10, e se não é nulo)
            dezena = str[i+j-1];
            numDigitos++;
        } else {
            dezena = '0'; // Preencher com zero se não houver dígito
        }

        // Centena
        if (j - 2 >= 0 && str[i+j-2] >= '0' && str[i+j-2] <= '9' && str[i+j-2] != '\0') { // Verifica se é um dígito válido (menor que 10, e se não é nulo)
            centena = str[i+j-2];
            numDigitos++;
        } else {
            centena = '0'; // Preencher com zero se não houver dígito
        }

        // Inserir o nó na lista
        if (insertNode(bigInt, unidade, dezena, centena, sinal, numDigitos) == -1) {
            freeBigInt(bigInt);
            return NULL; // Falha na inserção do nó
        }

    }
    return bigInt;
}

// Função is greater than
/*
    TODO:
    1- Verificar se os dois bigInts são nulos.
    2- Verificar os sinais dos dois bigInts.
        a) Se diferetentes, o positivo é maior.
        b) Se iguais, comparar os tamanhos.
    3- Verificar o tamanho dos dois bigInts.
        a) Se diferentes, o maior tamanho é maior.
        b) Se iguais, comparar dígito a dígito do mais significativo para o menos significativo.

    4- Retornar verdadeiro se 'a' for maior que 'b', falso caso contrário.

    Retorno:
    - 1 se 'a' for maior que 'b'
    - 0 se 'a' não for maior que 'b'
    - -1 em caso de erro (BigInt nulo)
*/
int isGreaterThan(const BigInt* a, const BigInt* b) {
    if (a == NULL || b == NULL) return -1; // Indica erro por BigInt nulo

    char sinalA = a->end->sinal;
    char sinalB = b->end->sinal;

    if (sinalA != sinalB) {
        return (sinalA == '+') ? 1 : 0; // '+' é maior que '-'

    } else { // mesmo sinal
        if (a->size != b->size) {
            if(sinalA == '+') {
                return (a->size > b->size) ? 1 : 0; // maior tamanho é maior
            } else {
                return (a->size < b->size) ? 1 : 0; // menor tamanho é maior (negativo)
            }

        } else { // mesmo tamanho, comparar digito a digito a partir do mais significativo
            Node *currentA = a->end;
            Node *currentB = b->end;

            if (currentA == NULL || currentB == NULL) return -1;

            if (sinalA == '+') {
                int res = isThan_rec(currentA, currentB);
                return res;
            } else {
                int res = isThan_rec(currentA, currentB);
                return (res == 1) ? 0 : 1; //iversão da lógica para numero negativo
            }
        }
    }

    return 0; 
}

// Função is less than
/*
    TODO:
    1- Verificar se os dois bigInts são nulos.
    2- Verificar os sinais dos dois bigInts.
        a) Se diferetentes, o negativo é menor.
        b) Se iguais, comparar os tamanhos.
    3- Verificar o tamanho dos dois bigInts.
        a) Se diferentes, o menor tamanho é menor.
        b) Se iguais, comparar dígito a dígito do mais significativo para o menos significativo.
    
    4- Retornar verdadeiro se 'a' for menor que 'b', falso caso contrário.
*/
int isLessThan(const BigInt* a, const BigInt* b) {
    if (a == NULL || b == NULL) return -1; // Indica erro por BigInt nulo

    char sinalA = a->end->sinal;
    char sinalB = b->end->sinal;

    if (sinalA != sinalB) {
        return (sinalA == '-') ? 1 : 0; // '-' é menor que '+'

    } else { // mesmo sinal
        if (a->size != b->size) {
            if(sinalA == '+') {
                return (a->size < b->size) ? 1 : 0; // menor tamanho é menor
            } else {
                return (a->size > b->size) ? 1 : 0; // maior tamanho é menor (negativo)
            }

        } else { // mesmo tamanho, comparar digito a digito a partir do mais significativo
            Node *currentA = a->end;
            Node *currentB = b->end;

            if (currentA == NULL || currentB == NULL) return -1;

            if (sinalA == '+') {
                int res = isThan_rec(currentA, currentB);
                return (res == 1) ? 0 : 1; // inversão da lógica para "menor que"
            } else {
                int res = isThan_rec(currentA, currentB);
                return res; // mantém a lógica para número negativo
            }
        }
    }

    return 0; 
}


// Função is equal to
/*
    TODO:
    1- Verificar se os dois bigInts são nulos.
    2- Verificar os sinais dos dois bigInts.
        a) Se diferentes, retornar falso.
        b) Se iguais, comparar os tamanhos.
    3- Verificar o tamanho dos dois bigInts.
        a) Se diferentes, retornar falso.
        b) Se iguais, comparar dígito a dígito do mais significativo para o menos significativo.

    4- Retornar verdadeiro se 'a' for igual a 'b', falso caso contrário.
*/

int isEqualTo(const BigInt* a, const BigInt* b) {
    if (a == NULL || b == NULL) return -1; // Indica erro por BigInt nulo

    char sinalA = a->end->sinal;
    char sinalB = b->end->sinal;

    if (sinalA != sinalB) {
        return 0; // sinais diferentes, não são iguais

    } else { // mesmo sinal
        if (a->size != b->size) {
            return 0; // tamanhos diferentes, não são iguais

        } else { // mesmo tamanho, comparar digito a digito a partir do mais significativo
            Node *currentA = a->end;
            Node *currentB = b->end;

            while (currentA != NULL && currentB != NULL) {
                if (currentA->centena != currentB->centena ||
                    currentA->dezena != currentB->dezena ||
                    currentA->unidade != currentB->unidade) {
                    return 0; // dígitos diferentes, não são iguais
                }
                currentA = currentA->prev;
                currentB = currentB->prev;
            }

            return 1; // todos os dígitos são iguais
        }
    }

    return 0; 
}




// Função para somar big ints
/*
    TODO: 
    1- Verificar se os dois bigInts são nulos.
    2- Verificar os sinais dos dois bigInts.
    3- Verificar o tamanho dos dois bigInts.
    4- Se os sinais forem iguais, somar os dois bigInts e manter o sinal.
    5- Se os sinais forem diferentes, subtrair o menor do maior e definir o sinal do maior.
    6- Retornar o BigInt resultante.

    Importante: Levar em consideração o carry 
*/
BigInt* addBigInt(const BigInt* a, const BigInt* b) {
    if (a == NULL || b == NULL) return NULL;
    char sinalA = a->end->sinal;
    char sinalB = b->end->sinal;

    


    return NULL; // Placeholder
}


// Função para subtrair big ints
/*
    TODO:
    1- Verificar se os dois bigInts são nulos.
    2- Verificar os sinais dos dois bigInts.
    3- Verificar o tamanho dos dois bigInts.
    4- Se os sinais forem diferentes, somar os dois bigInts e manter o sinal do minuendo.
    5- Se os sinais forem iguais, subtrair o menor do maior e definir o sinal do maior.
    6- Retornar o BigInt resultante.

    Importante: Levar em consideração o carry
*/
BigInt* subtractBigInt(const BigInt* a, const BigInt* b) {
    // Implementação da função de subtração de BigInts
    return NULL; // Placeholder
}

// Função para imprimir 
/*
    Imprime o BigInt na saída padrão.
    Formato: [sinal][dígitos]
    Exemplo: -123456789
*/
void printBigInt(const BigInt* bigInt) {
    if (bigInt == NULL || bigInt->start == NULL) {
        printf("BigInt nulo\n");
        return;
    }

    Node *current = bigInt->end;

    if (current->sinal == '-') {
        printf("-");
    }

    /* imprimir primeiro (mais significativo) com numDigitos real */
    int nd = current->numDigitos;
    if (nd == 3) {
        printf("%c%c%c", current->centena, current->dezena, current->unidade);
    } else if (nd == 2) {
        printf("%c%c", current->dezena, current->unidade);
    } else {
        printf("%c", current->unidade);
    }

    current = current->prev;

    /* blocos seguintes: sempre 3 dígitos (zeros à esquerda já armazenados) */
    while (current != NULL) {
        printf("%c%c%c", current->centena, current->dezena, current->unidade);
        current = current->prev;
    }
}


// testar funções 
int main() {
    BigInt* bigInt1 = createBigInt("-123456789");
    BigInt* bigInt2 = createBigInt("-00098765432100000000000000");
    BigInt* bigInt3 = createBigInt("-123456789");

    printf("BigInt 1: ");
    printBigInt(bigInt1);
    printf("\n");

    printf("BigInt 2: ");
    printBigInt(bigInt2);
    printf("\n");

    printf("Comparacao:\n");
    int gt = isGreaterThan(bigInt1, bigInt2);
    printf("bigInt1 > bigInt2? %s\n", gt ? "Sim" : "Nao");
    int lt = isLessThan(bigInt1, bigInt2);
    printf("bigInt1 < bigInt2? %s\n", lt ? "Sim" : "Nao");
    int eq = isEqualTo(bigInt1, bigInt3);
    printf("bigInt1 == bigInt3? %s\n", eq ? "Sim" : "Nao");

    // Liberar memória
    freeBigInt(bigInt1);
    freeBigInt(bigInt2);

    return 0;
}










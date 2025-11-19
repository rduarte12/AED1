#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInt.h"

/*
    Funções para manipulação de números grandes (BigInt) utilizando listas encadeadas.

    Tipos:
    - BigInt: Estrutura que representa um número grande. (Armazena os dígitos em uma lista encadeada e o sinal do número).
    - Node: Estrutura que representa um nó da lista encadeada (tres digitos com char para economizar espaço).

    Funções Principais:
    - BigInt* createBigInt(const char* str): Cria um BigInt a partir de uma string.
    - void freeBigInt(BigInt* bigInt): Libera a memória alocada para um BigInt.
    - void printBigInt(const BigInt* bigInt): Imprime o BigInt na saída padrão.
    - BigInt* addBigInt(const BigInt* a, const BigInt* b): Soma dois BigInts e retorna o resultado.
    - BigInt* subtractBigInt(const BigInt* a, const BigInt* b): Subtrai dois BigInts e retorna o resultado.
    - int* isGreaterThan(const BigInt* a, const BigInt* b): Compara dois BigInts e retorna verdadeiro se 'a' for maior que 'b'.
    - int* isEqualTo(const BigInt* a, const BigInt* b): Compara dois BigInts e retorna verdadeiro se forem iguais.
    - int* isLessThan(const BigInt* a, const BigInt* b): Compara dois BigInts e retorna verdadeiro se 'a' for menor que 'b'.

    Funções Auxiliares:
    - Node* createNode(char unidade, char dezena, char centena, int numDigitos);
    - int is_empty_BigInt(const BigInt *BigInt);
    - int insertNode(BigInt *bigInt, char unidade, char dezena, char centena, int numDigitos);

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
        - O sinal é armazenado por BigInt (campo `sinal` em BigInt).
        - numDigitos indica quantos dígitos do bloco mais significativo são reais:
          1, 2 ou 3. Blocos intermediários sempre devem ter 3 dígitos (zeros à esquerda
          quando necessário).
*/

/*
    TODO:
    - Implementar:
        - addBigInt
        - subtractBigInt
*/

// Definição das estruturas (sinal agora em BigInt)
typedef struct Node {
    char unidade;               // Armazena um dígito (0-9)
    char dezena;                // Armazena um dígito (0-9)
    char centena;               // Armazena um dígito (0-9)
    int numDigitos;             // Armazena o número de digitos preenchidos.    
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct BigInt {
    Node* start;                // Ponteiro para o início da lista encadeada    
    Node* end;                  // Ponteiro para o final da lista encadeada
    int size;                   // Tamanho da lista (número de blocos/nós)
    char sinal;                 // Sinal do número ('+' ou '-')
} BigInt;


// Função para criar um nó
/*
    TODO:
    1. Alocar memória para um novo nó.
    2. Inicializar os campos do nó com os valores fornecidos.
    3. Retornar o ponteiro para o novo nó.
*/
Node* createNode(char unidade, char dezena, char centena, int numDigitos) {

    Node *novoNo = (Node*)malloc(sizeof(Node));
    if(!novoNo) {
        return NULL;
    }

    novoNo->unidade = unidade;
    novoNo->dezena = dezena;
    novoNo->centena = centena;
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
int insertNode(BigInt *bigInt, char unidade, char dezena, char centena, int numDigitos) {
    if (!bigInt) return -1;
    if (numDigitos < 1) numDigitos = 1;
    if (numDigitos > 3) numDigitos = 3;

    Node *novoNo = createNode(unidade, dezena, centena, numDigitos);
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
    if (!str) return NULL;

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
        // String será somente "0", preservando sinal se tiver (representa 0)
        if (sinal_presente) {
            str[0] = str[0]; // sinal mantido
            str[1] = '0';
            str[2] = '\0';
        } else {
            str[0] = '0';
            str[1] = '\0';
        }
        return str;
    }

    // Se tem sinal, manter no começo
    if (sinal_presente) {
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
// Observação: percorre de mais-significativo (prev) para menos-significativo
int isThan_rec(const Node *a, const Node *b) {
    if (a == NULL || b == NULL) return 0; // chamada incorreta, tratar como igual/erro

    if (a->centena != b->centena ||
        a->dezena != b->dezena ||
        a->unidade != b->unidade) {

        if (a->centena > b->centena) return 1;
        if (a->centena < b->centena) return 0;
        if (a->dezena > b->dezena) return 1;
        if (a->dezena < b->dezena) return 0;
        if (a->unidade > b->unidade) return 1;
        if (a->unidade < b->unidade) return 0;
    }

    return isThan_rec(a->prev, b->prev);
}

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

    // Criar uma cópia da string para manipulação (não modificar literais)
    char* buf = strdup(str1);
    if (buf == NULL) {
        return NULL;
    }

    // Ignorar zeros à esquerda na cópia
    buf = removeZeros(buf);
    if (buf == NULL) {
        free(buf);
        return NULL;
    }

    // verificar o tamanho da string e quantidade de dígitos
    int len = strlen(buf);
    
    if (buf[0] == '-' && len == 1) {
        free(buf);
        return NULL; // String inválida
    }

    int hasSign = (buf[0] == '-' || buf[0] == '+') ? 1 : 0; // Verifica se há sinal
    int digits = len - (hasSign ? 1 : 0);

    // Alocar memória para o BigInt
    BigInt* bigInt = (BigInt*)malloc(sizeof(BigInt));
    if (!bigInt) {
        free(buf);
        return NULL; // Falha na alocação de memória
    }

    // Inicializar o BigInt
    bigInt->start = NULL;
    bigInt->end = NULL;
    bigInt->size = 0;
    bigInt->sinal = (buf[0] == '-') ? '-' : '+';

    // Preencher o BigInt com os dígitos da string
    int i = hasSign ? 1 : 0; // Índice inicial para os dígitos

    // Loop para processar os digitos na string de tras para frente (formando blocos de 3)
    for (int j = digits - 1; j >= 0; j -=3) {
        char unidade = '0';
        char dezena = '0';
        char centena = '0';
        int numDigitos = 0;

        // Unidade
        if (buf[i+j] >= '0' && buf[i+j] <= '9') {
            unidade = buf[i+j];
            numDigitos++;
        } else {
            freeBigInt(bigInt);
            free(buf);
            return NULL; // Caractere inválido na string
        }

        // Dezena
        if (j - 1 >= 0 && buf[i+j-1] >= '0' && buf[i+j-1] <= '9') {
            dezena = buf[i+j-1];
            numDigitos++;
        } else {
            dezena = '0'; // Preencher com zero se não houver dígito
        }

        // Centena
        if (j - 2 >= 0 && buf[i+j-2] >= '0' && buf[i+j-2] <= '9') {
            centena = buf[i+j-2];
            numDigitos++;
        } else {
            centena = '0'; // Preencher com zero se não houver dígito
        }

        // Inserir o nó na lista (sem sinal por nó)
        if (insertNode(bigInt, unidade, dezena, centena, numDigitos) == -1) {
            freeBigInt(bigInt);
            free(buf);
            return NULL; // Falha na inserção do nó
        }
    }

    free(buf);
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

    char sinalA = a->sinal;
    char sinalB = b->sinal;

    if (sinalA != sinalB) {
        return (sinalA == '+') ? 1 : 0; // '+' é maior que '-'
    }

    // mesmos sinais
    if (a->size != b->size) {
        if (sinalA == '+') {
            return (a->size > b->size) ? 1 : 0;
        } else {
            return (a->size < b->size) ? 1 : 0;
        }
    }

    // mesmo tamanho: comparar blocos do mais significativo (end) para o menos (start)
    Node *currentA = a->end;
    Node *currentB = b->end;

    if (currentA == NULL || currentB == NULL) return -1;

    int res = isThan_rec(currentA, currentB);
    if (sinalA == '+') return res;
    return res ? 0 : 1; // inverte para negativos
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

    char sinalA = a->sinal;
    char sinalB = b->sinal;

    if (sinalA != sinalB) {
        return (sinalA == '-') ? 1 : 0; // '-' é menor que '+'
    }

    // mesmos sinais
    if (a->size != b->size) {
        if (sinalA == '+') {
            return (a->size < b->size) ? 1 : 0;
        } else {
            return (a->size > b->size) ? 1 : 0;
        }
    }

    Node *currentA = a->end;
    Node *currentB = b->end;
    if (currentA == NULL || currentB == NULL) return -1;

    int res = isThan_rec(currentA, currentB);
    if (sinalA == '+') return res ? 0 : 1; // se a> b então não é menor
    return res; // para negativos, resultado direto
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

    if (a->sinal != b->sinal) {
        return 0; // sinais diferentes, não são iguais
    }

    if (a->size != b->size) {
        return 0; // tamanhos diferentes, não são iguais
    }

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

    return 1;
}

// Função para somar big ints
/*
    TODO: 
    1- Verificar se os dois bigInts são nulos.
    2- Verificar os sinais dos dois bigInts.
    3- Verificar o tamanho dos dois bigInts.
    4- Se os sinais forem iguais, somar os dois bigInts e manter o sinal.
        - verificar o tamanho dos dois BigInts para definir o loop
        - Definir o sinal do BigInt resultante.
        a) Acessar primeiro nó de cada BigInt (menos significativo).
        b) Somar os dígitos correspondentes, levando em consideração o carry.
            carry = {se soma >= 10, carry = 1 e soma -= 10; senão carry = 0}
        c) Criar um novo nó com o resultado da soma e inserir no BigInt resultante.
        d) Repetir até que todos os nós tenham sido processados.
        e) Se houver carry restante, criar um novo nó para ele.
    5- Se os sinais forem diferentes, subtrair o menor do maior e definir o sinal do maior.
    6- Retornar o BigInt resultante.

    Importante: Levar em consideração o carry 
*/
BigInt* addBigInt(const BigInt* a, const BigInt* b) {
    if (a == NULL || b == NULL) return NULL; // Indica erro por BigInt nulo
    
    // sinais dos BigInts
    char sinalA = a->sinal;
    char sinalB = b->sinal;

    // tamanhos dos BigInts
    int tamanhoA = a->size;
    int tamanhoB = b->size;

    // criar BigInt resultado
    BigInt* resultado = (BigInt*)malloc(sizeof(BigInt));
    if (!resultado) {
        return NULL; // Falha na alocação de memória
    }
    resultado->start = NULL;
    resultado->end = NULL;
    resultado->size = 0;
    resultado->sinal = '+'; // valor temporário
    
    // se sinais iguais, somar e manter o sinal do maior
    if (sinalA == sinalB) {
        
        // - verificar tamanohos para definir loop (até qual digito vai somar + carry)
        int maxTamanho = (tamanhoA > tamanhoB) ? tamanhoA : tamanhoB;

        //- Definir o sinal do BigInt resultante.
        resultado->sinal = sinalA; // mesmo sinal dos dois

        //a) Acessar primeiro nó de cada BigInt (menos significativo).
        Node* currentA = a->start;
        Node* currentB = b->start;

        if (currentA == NULL && currentB == NULL) {
            freeBigInt(resultado);
            return NULL; // Ambos BigInts vazios
        }

        int carry = 0;

        // Loop para somar os dígitos
        int i = 0;
        while (i < maxTamanho) {
            
            int somaUnidade = carry;
            int somaDezena = 0;
            int somaCentena = 0;

            // Definir numdIGitos do nó resultado com base nos nós do amior big int
            int numDigitosRes = 0;
            if (maxTamanho == tamanhoA && currentA != NULL) {
                numDigitosRes = currentA->numDigitos;
            } else if (maxTamanho == tamanhoB && currentB != NULL) {
                numDigitosRes = currentB->numDigitos;
            }

            // Somar unidade
            if (currentA != NULL) { // se ainda há dígitos em A
                somaUnidade += (currentA->unidade - '0');
            }
            if (currentB != NULL) { // se ainda há dígitos em B
                somaUnidade += (currentB->unidade - '0');
            }
            if (somaUnidade >= 10) { // verificar carry
                carry = 1;
                somaUnidade -= 10;
            } else {
                carry = 0;
            }

            // Somar dezena
            if (currentA != NULL) {
                somaDezena += (currentA->dezena - '0');
            }
            if (currentB != NULL) {
                somaDezena += (currentB->dezena - '0');
            }
            somaDezena += carry; // adicionar carry da unidade
            if (somaDezena >= 10) { // verificar carry
                carry = 1;
                somaDezena -= 10;
            } else {
                carry = 0;
            }

            // Somar centena
            if (currentA != NULL) {
                somaCentena += (currentA->centena - '0');
            }
            if (currentB != NULL) {
                somaCentena += (currentB->centena - '0');
            }
            somaCentena += carry; // adicionar carry da dezena
            if (somaCentena >= 10) { // verificar carry
                carry = 1;
                somaCentena -= 10;
            } else {
                carry = 0;
            }

            // Definir numDigitosRes com base nos valores calculados
            if (somaCentena > 0) {
                numDigitosRes = 3;
            } else if (somaDezena > 0) {
                numDigitosRes = 2;
            } else {
                numDigitosRes = 1;
            }

            // Criar novo nó com o resultado da soma
            char unidadeRes = (char)(somaUnidade + '0');
            char dezenaRes = (char)(somaDezena + '0');
            char centenaRes = (char)(somaCentena + '0');

            if (insertNode(resultado, unidadeRes, dezenaRes, centenaRes, numDigitosRes) == -1) {
                freeBigInt(resultado);
                return NULL; // Falha na inserção do nó
            }


            if (currentA != NULL) {
                currentA = currentA->next;
            }
            if (currentB != NULL) {
                currentB = currentB->next;
            }
            i += 1;
        }

    } else {
        // sinais diferentes: subtrair o menor do maior e definir o sinal do maior
        // Implementação futura
    }

    return resultado;
}

// Função para subtrair big ints
/*
    TODO:
    1- Verificar se os dois bigInts são nulos.
    2- Verificar os sinais dos dois bigInts.
    3- Verificar o tamanho dos dois bigInts.
    4- Se os sinais forem diferentes, somar os dois bigInts e manter o sinal do maior em módulo (desconsiderando o sinal)
    5- Se os sinais forem iguais, subtrair o menor do maior e definir o sinal do maior.
            - verificar o tamanho dos dois BigInts para definir o loop
        - Definir o sinal do BigInt resultante.
        a) verificar qual é maior em módulo (desconsiderando o sinal) e definjir o sinal desse como sinal do resultado
        b) Criar BigInt resultante.
        c) Acessar primeiro nó de cada BigInt (menos significativo).
        d) Para cada número, verificar se o minuendo é maior que o subtraendo.
            - Se sim, subtrair normalmente.
            - Se não, emprestar 1 do próximo dígito mais significativo.
        e) Criar um novo nó com o resultado da subtração e inserir no BigInt resultante.
        f) Repetir até que todos os nós tenham sido processados.
    6- Retornar o BigInt resultante.

    Importante: Levar em consideração o carry
*/

// Função auxiliar para subtração quando 'maior' > 'menor' 
BigInt*subtract_aux(const BigInt* maior, const BigInt* menor) {
    BigInt* resultado = (BigInt*)malloc(sizeof(BigInt));
    if(!resultado) return NULL;
    resultado->start = NULL;
    resultado->end = NULL;
    resultado->size = 0;
    resultado->sinal = maior->sinal;

    Node* currentMaior = maior->start;
    Node* currentMenor = menor->start;
    int carry = 0;
    int maxTamanho = maior->size;
    int i = 0;

    while(i < maxTamanho) {
        
    }

    return resultado;
}

BigInt* subtractBigInt(const BigInt* a, const BigInt* b) {
    
    if (a == NULL || b == NULL) return NULL; // Indica erro por BigInt nulo

    // sinais dos BigInts
    char sinalA = a->sinal;
    char sinalB = b->sinal;

    // tamanhos dos BigInts
    int tamanhoA = a->size;
    int tamanhoB = b->size;

    // verificar sinais e proceder conforme o caso
    // se iguais, subtrair o menor do maior e manter o sinal do maior
    if (sinalA == sinalB) {
        if (isGreaterThan(a, b) == 1) {
            // a > b


        } else if (isLessThan(a, b) == 1) {
            // a < b


        } else {
            // a == b
            // resultado é zero
            BigInt* resultado = createBigInt("0");
            return resultado;
        }
        
    } else {
        // sinais diferentes: 
        // mudar sinal do segundo e somar e manter o sinal do maior em módulo
        BigInt* b_invertido = (BigInt*)malloc(sizeof(BigInt));
        if (!b_invertido) {
            return NULL; // Falha na alocação de memória
        }
        b_invertido->start = b->start;
        b_invertido->end = b->end;
        b_invertido->size = b->size;
        b_invertido->sinal = sinalA; // inverter sinal

        BigInt* resultado = addBigInt(a, b_invertido);
        free(b_invertido);

        if (resultado == NULL) {
            return NULL; // Falha na adição
        }
        return resultado;
    }

    return NULL;
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

    // imprimir sinal (evitar "-0")
    if (bigInt->sinal == '-') {
        if (!(bigInt->start == bigInt->end && bigInt->start->numDigitos == 1 && bigInt->start->unidade == '0')) {
            printf("-");
        }
    }

    Node *current = bigInt->end;

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
    BigInt* bigInt1 = createBigInt("-1");
    BigInt* bigInt2 = createBigInt("00098765432100000000000000");
    BigInt* bigInt3 = createBigInt("-123456789");
    BigInt* bigIntSum = addBigInt(bigInt1, bigInt3);

    printf("BigInt 1: ");
    printBigInt(bigInt1);
    printf("\n");

    printf("BigInt 2: ");
    printBigInt(bigInt2);
    printf("\n");

    printf("Comparacao:\n");
    int gt = isGreaterThan(bigInt1, bigInt2);
    printf("bigInt1 > bigInt2? %s\n", gt == 1 ? "Sim" : (gt == 0 ? "Nao" : "Erro"));
    int lt = isLessThan(bigInt1, bigInt2);
    printf("bigInt1 < bigInt2? %s\n", lt == 1 ? "Sim" : (lt == 0 ? "Nao" : "Erro"));
    int eq = isEqualTo(bigInt1, bigInt3);
    printf("bigInt1 == bigInt3? %s\n", eq == 1 ? "Sim" : (eq == 0 ? "Nao" : "Erro"));

    printf("Soma BigInt1 + BigInt3: ");
    printBigInt(bigIntSum);
    printf("\n");

    BigInt* bigIntDiff = subtractBigInt(bigInt1, bigInt2);
    printf("Subtracao BigInt1 - BigInt2: ");
    printBigInt(bigIntDiff);
    printf("\n");

    // Liberar memória
    freeBigInt(bigInt1);
    freeBigInt(bigInt2);
    freeBigInt(bigInt3);
    freeBigInt(bigIntSum);

    return 0;
}










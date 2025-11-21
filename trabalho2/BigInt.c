#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInt.h"

/*
        BigInt

        Descrição
        - Implementa inteiros  usando blocos de 3 dígitos
            armazenados em uma lista duplamente encadeada.

        Estruturas
        - Node
                - campos: unidade, dezena, centena (chars '0'..'9')
                - numDigitos: quantos dígitos são válidos (1: unidade; 2: dezena+unidade; 3: centena+dezena+unidade)
                - ponteiros: next: proximo (direção mais significativo), prev: anterior (direção menos significativo)

        - BigInt
                - start: ponteiro para o nó menos-significativo
                - end:   ponteiro para o nó mais-significativo
                - size:  número de blocos (nós)
                - sinal: '+' ou '-' — sinal único para todo o BigInt

        Convenções 
        - Ordem: start é o bloco menos-significativo; end é o bloco mais-significativo.
            Percorrendo next vai do menos-significativo ao mais-significativo; 
            Percorrendo prev é o oposto.
        - Blocos intermediários devem conter exatamente 3 dígitos. O bloco mais-significativo
            pode ter numDigitos = 1..3 indicando quantos dígitos são efetivos.
        - Sinal é armazenado apenas em BigInt->sinal.

        Funções públicas 
        - BigInt* createBigInt(char* str)
                - cria um BigInt a partir de uma string com sinal opcional
                - normaliza zeros à esquerda
                - retorna NULL em erro/entrada inválida

        - void freeBigInt(BigInt*): libera memória
        - void printBigInt(const BigInt*): imprime o valor do BigInt
        - int isGreaterThan(const BigInt*, const BigInt*): compara se 'a' > 'b'
        - int isLessThan(const BigInt*, const BigInt*): compara se 'a' < 'b'
        - int isEqualTo(const BigInt*, const BigInt*): compara se 'a' == 'b'
        - BigInt* addBigInt(const BigInt*, const BigInt*): soma dois BigInts
        - BigInt* subtractBigInt(BigInt*, BigInt*): subtrai dois BigInts

        Funções auxiliares 
        - Node* createNode(char u, char d, char c, int numDigitos): cria um nó com os dígitos fornecidos
        - int insertNode(BigInt*, char u, char d, char c, int numDigitos): insere no final (append: end->next = novo)
        - char* removeZeros(char*): remove zeros à esquerda de uma string
        - removeZeros_nos: remove nós desnecessários (zeros à esquerda) de um BigInt

*/


// Definição das estruturas 
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
    int size;                   // Tamanho da lista (número de nós)
    char sinal;                 // Sinal do número ('+' ou '-')
} BigInt;


// Função para criar um nó
/*
    Descrição da função:
    - Aloca memória para um novo nó.
    - Inicializa os campos do nó com os valores fornecidos.
    - Retorna o ponteiro para o novo nó.
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
    Descrição da função:
    - Cria um novo nó com os valores fornecidos.
    - Verifica se a criação do nó foi bem-sucedida.
    - Se a lista estiver vazia, define o novo nó como início e fim.
    - Caso contrário, insere o novo nó no final da lista.
    - Atualiza o tamanho da lista.
    - Retorna 1 em caso de sucesso, -1 em caso de falha.
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
/*
    Descrição da função:
    - Libera a memória alocada para todos os nós do BigInt.
    - Libera a memória alocada para a estrutura BigInt.
*/
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
/*
    Descrição da função:
    - Remove zeros à esquerda de uma string que representa um número.
    - Preserva o sinal '+' ou '-' se presente.
    - Retorna a string sem zeros à esquerda.
*/
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


/*
    Descrição da função:
    - Compara recursivamente os nós de dois BigInts.
    - Retorna 1 se o primeiro BigInt for maior que o segundo, em magnitude.
    - Retorna 0 se forem iguais em magnitude.
    - Retorna -1 se o primeiro BigInt for menor que o segundo, em magnitude.
*/
int isThan_rec(const Node *a, const Node *b) {
    // Caso base: ambos nulos -> iguais
    if (a == NULL && b == NULL) return 0; // iguais ou erro
    // Se apenas um for nulo, o que existe é maior 
    if (a == NULL) return -1;
    if (b == NULL) return 1;

    // Comparar bloco atual (centena, dezena, unidade) do mais-significativo para o menos
    if (a->centena != b->centena) return (a->centena > b->centena) ? 1 : -1;
    if (a->dezena  != b->dezena)  return (a->dezena  > b->dezena)  ? 1 : -1;
    if (a->unidade != b->unidade) return (a->unidade > b->unidade) ? 1 : -1;

    // Blocos iguais -> comparar o próximo bloco mais-significativo
    return isThan_rec(a->prev, b->prev);
}

// Função para criar um BigInt a partir de uma string
/*
    Descrição da função:
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
    
    int hasSign = (buf[0] == '-' || buf[0] == '+') ? 1 : 0; // Verifica se há sinal
    if (hasSign && len == 1) { // entrada apenas com sinal é inválida
        free(buf);
        return NULL;
    }
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
    Descrição da função:
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

    // Sinais diferentes
    if (sinalA != sinalB) {
        return (sinalA == '+') ? 1 : 0; // '+' é maior que '-'
    } else {

        // mesmos sinais
        // tamanhos diferentes
        if (a->size != b->size) {

            if (sinalA == '+') {
                return (a->size > b->size) ? 1 : 0; // para positivos, maior tamanho é maior
            } else {
                return (a->size < b->size) ? 1 : 0; // para negativos, menor tamanho é maior
            }
        }

        // tamanhos iguais
        Node *currentA = a->end;
        Node *currentB = b->end;
        if (currentA == NULL || currentB == NULL) return -1; // erro: nó nulo
        int res = isThan_rec(currentA, currentB);
        if (sinalA == '+') return res; // para positivos, resultado direto
        return res ? 0 : 1; // se a > b então não é maior para negativos
    }
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
    
    Retorno:
     - 1 se 'a' for menor que 'b'
     - 0 se 'a' não for menor que 'b'
     - -1 em caso de erro (BigInt nulo)
*/
int isLessThan(const BigInt* a, const BigInt* b) {
    if (a == NULL || b == NULL) return -1; // Indica erro por BigInt nulo

    char sinalA = a->sinal;
    char sinalB = b->sinal;

    if (sinalA != sinalB) {
        return (sinalA == '-') ? 1 : 0; // '-' é menor que '+'
    }

    // sinais diferentes
    if (a->size != b->size) {
        if (sinalA == '+') {
            return (a->size < b->size) ? 1 : 0; // para positivos, menor tamanho é menor
        } else {
            return (a->size > b->size) ? 1 : 0; // para negativos, maior tamanho é menor
        }

    } else { // mesmos sinais

        Node *currentA = a->end;
        Node *currentB = b->end;
        if (currentA == NULL || currentB == NULL) return -1; // erro: nó nulo
        int res = isThan_rec(currentA, currentB);
        if (sinalA == '+') { // para positivos, se a < b
            return (res == -1) ? 1 : 0;
        } else {
            return (res == 1) ? 1 : 0; // para negativos, se a > b então a < b
        }
    }

}

// Função is equal to
/*
    Descrição da função:
    1- Verificar se os dois bigInts são nulos.
    2- Verificar os sinais dos dois bigInts.
        a) Se diferentes, retornar falso.
        b) Se iguais, comparar os tamanhos.
    3- Verificar o tamanho dos dois bigInts.
        a) Se diferentes, retornar falso.
        b) Se iguais, comparar dígito a dígito do mais significativo para o menos significativo.

    Retorno:
     - 1 se 'a' for igual a 'b'
     - 0 se 'a' não for igual a 'b'
     - -1 em caso de erro (BigInt nulo)
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

    int res = isThan_rec(currentA, currentB); //isThan_rec retorna 0 se iguais

    return (res == 0) ? 1 : 0;
}

// Prototipos das funções de adição e subtração
BigInt* addBigInt(BigInt* a,BigInt* b);
BigInt* subtractBigInt(BigInt* a, BigInt* b);

// Função para somar big ints
/*
    Descrição:
    - Soma dois BigInts e retorna um novo BigInt (não modifica os operandos).
    - Opera por blocos de 3 dígitos, percorrendo do menos-significativo (start) ao mais-significativo (end).
    - Trata carry entre blocos corretamente e cria um nó adicional se necessário.
    - Se os sinais forem iguais: soma as magnitudes e mantém o sinal comum.
    - Se os sinais forem diferentes: realiza a subtração do menor em módulo pelo maior em módulo
      e aplica o sinal do operando de maior magnitude.
    - Em caso de entrada inválida (NULL) retorna NULL.

    Detalhes de implementação esperados:
    - Iterar até o máximo de blocos entre os operandos.
    - Para cada nó, converter dígitos para valor inteiro e realizar a soma casa a casa incluindo o carry,
    - Retornar o BigInt alocado com sinal correto ou NULL em erro.
*/
BigInt* addBigInt(BigInt* a, BigInt* b) {
    if (a == NULL || b == NULL) return NULL; // Indica erro por BigInt nulo
    
    // sinais dos BigInts
    char sinalA = a->sinal;
    char sinalB = b->sinal;

    // tamanhos dos BigInts
    int tamanhoA = a->size;
    int tamanhoB = b->size;
    
    // se sinais iguais, somar e manter o sinal do maior
    if (sinalA == sinalB) {
            // criar BigInt resultado
            BigInt* resultado = (BigInt*)malloc(sizeof(BigInt));
            if (!resultado) {
                return NULL; // Falha na alocação de memória
            }
            resultado->start = NULL;
            resultado->end = NULL;
            resultado->size = 0;
            resultado->sinal = '+'; // valor temporário
        
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
            
            carry = carry; // carry da iteração anterior
            int somaUnidade = -1; // inicializar com -1 para indicar que não foi somado ainda (flag)
            int somaDezena = -1;
            int somaCentena = -1;
            int numDigitosRes = 0;
            // Somar unidade
            if (currentA != NULL) { // se ainda há dígitos em A
                somaUnidade += (currentA->unidade - '0');
            }
            if (currentB != NULL) { // se ainda há dígitos em B
                somaUnidade += (currentB->unidade - '0');
            }
            somaUnidade += carry; // adicionar carry da iteração anterior
            if (somaUnidade != -1) { // indica se houve soma
                somaUnidade++; // ajustar valor inicial que era -1: somar 1 para compensar
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
            if (somaDezena != -1) { // indica se houve soma
                somaDezena++; // ajustar valor inicial que era -1: somar 1 para compensar
            }
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
            if (somaCentena != -1) { // indica se houve soma
                somaCentena++; // ajustar valor inicial que era -1: somar 1 para compensar
            }
            if (somaCentena >= 10) { // verificar carry
                carry = 1;
                somaCentena -= 10;
            } else {
                carry = 0;
            }

            // Definir numDigitosRes com base nos valores que foram modificados, ou seja, diferentes de -1
            if (somaCentena != -1) numDigitosRes++;
            if (somaDezena != -1) numDigitosRes++;
            if (somaUnidade != -1) numDigitosRes++;

            // Criar novo nó com o resultado da soma
            char unidadeRes = (char)(somaUnidade + '0');
            char dezenaRes = (char)(somaDezena + '0');
            char centenaRes = (char)(somaCentena + '0');

            // Inserir o nó no BigInt resultado
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

        // Se houver carry restante, criar um novo nó para ele
                    // adicionar nó para carry restante após o loop, se houver
            if (carry > 0) {
                char unidadeRes = (char)(carry + '0');
                if (insertNode(resultado, unidadeRes, '0', '0', 1) == -1) {
                    freeBigInt(resultado);
                    return NULL; // Falha na inserção do nó
                }
            }

        return resultado;

    } else {
        // sinais diferentes: subtrair o menor do maior e definir o sinal do menor
        BigInt* subtracao = NULL;
        if (isGreaterThan(a, b) == 1) {

            BigInt *b_inv = (BigInt*)malloc(sizeof(BigInt));
            if (!b_inv) return NULL;
            b_inv->start = b->start;
            b_inv->end = b->end;
            b_inv->size = b->size;
            b_inv->sinal = (b->sinal == '+') ? '-' : '+';
            subtracao = subtractBigInt(a, b_inv);
            free(b_inv);

        } else {

            BigInt* a_inv = (BigInt*)malloc(sizeof(BigInt));
            if (!a_inv) return NULL;
            a_inv->start = a->start;
            a_inv->end = a->end;
            a_inv->size = a->size;
            a_inv->sinal = (a->sinal == '+') ? '-' : '+';
            subtracao = subtractBigInt(a_inv, b);
            subtracao->sinal = (b->sinal == '+') ? '-' : '+';
            free(a_inv);
        }

        return subtracao;


    }

    return NULL;
}

// Funções para subtrair big ints

// Função para remover nós desnecessários (zeros à esquerda) de um BigInt (utilizado na subtração)
/*
    Descrição da função:
    - Remove nós mais-significativos que representam zeros (centena, dezena, unidade = '0').
    - Ajusta o campo numDigitos do nó mais-significativo restante.
*/
void removeZeros_nos(BigInt *n) {
    if (!n || !n->end) return;

    // ms = nó mais significativo
    while (n->size > 1) {
        Node *ms = n->end;
        if (ms->centena == '0' && ms->dezena == '0' && ms->unidade == '0') {
            n->end = ms->prev;// atualizar end para o nó anterior
            if (n->end) n->end->next = NULL;
            free(ms);
            n->size--;
        } else break;
    }

    // ajustar numDigitos do nó mais-significativo restante
    if (n->end) {
        Node *ms = n->end;
        if (ms->centena != '0') ms->numDigitos = 3;
        else if (ms->dezena != '0') ms->numDigitos = 2;
        else ms->numDigitos = 1;
    }
}

// Subtrai |menor| de |maior| por blocos (0..999). Retorna BigInt novo. -> Tranforma os chars em um inteiro, subtrai, trata borrow, cria novo nó
// Função auxiliar para subtração
BigInt *subtract_aux(const BigInt* maior, const BigInt* menor) {
    if (!maior) return NULL; // maior não pode ser nulo

    // criar BigInt resultado
    BigInt* resultado = (BigInt*)malloc(sizeof(BigInt));
    if(!resultado) return NULL;
    resultado->start = resultado->end = NULL;
    resultado->size = 0;
    resultado->sinal = maior->sinal;

    // percorrer os nós de ambos os BigInts
    Node* a = maior->start; // start = menos significativo
    Node* b = (menor != NULL) ? menor->start : NULL; // pode ser nulo
    int borrow = 0; // inicializar borrow

    // loop até o final de ambos os BigInts                                                             
    while (a != NULL || b != NULL) {
        int valA = 0, valB = 0; // valores inteiros dos blocos

        if (a != NULL) {
            valA = (a->centena - '0') * 100 + (a->dezena - '0') * 10 + (a->unidade - '0'); // converter todos os dígitos em um único inteiro
        }
        if (b != NULL) {
            valB = (b->centena - '0') * 100 + (b->dezena - '0') * 10 + (b->unidade - '0'); // converter todos os dígitos em um único inteiro
        }

        int diff = valA - valB - borrow; // calcular a diferença considerando o borrow
        if (diff < 0) { // se negativo, ajustar com borrow
            diff += 1000;
            borrow = 1;
        } else {
            borrow = 0;
        }

        char unidadeRes = (char)('0' + (diff % 10)); // obter dígito da unidade
        char dezenaRes  = (char)('0' + ((diff / 10) % 10)); // obter dígito da dezena
        char centenaRes = (char)('0' + ((diff / 100) % 10)); // obter dígito da centena

        // numDigitos temporário: será ajustado por removeZeros
        if (insertNode(resultado, unidadeRes, dezenaRes, centenaRes, 3) == -1) {    // inserir nó no resultado
            freeBigInt(resultado);
            return NULL;
        }

        if (a) a = a->next;
        if (b) b = b->next;
    }

    // Se sobrar borrow, houve erro lógico (maior < menor) — liberar e retornar NULL
    if (borrow) {
        freeBigInt(resultado);
        return NULL;
    }

    // remover blocos mais-significativos zero e ajustar numDigitos do MSB
    removeZeros_nos(resultado);

    return resultado;
}

// Função principal de subtração
/*
    Descrição:
    - Subtrai dois BigInts e retorna um novo BigInt (não modifica os operandos).
    - Trata os sinais dos operandos para determinar a operação correta:
        a) Se os sinais forem diferentes, converte a subtração em uma soma.
        b) Se os sinais forem iguais, realiza a subtração do menor em módulo pelo maior em módulo.
    - Utiliza a função auxiliar 'subtract_aux' para realizar a subtração por blocos.
    - Retorna o BigInt resultante com o sinal correto ou NULL em caso de erro.

*/
BigInt* subtractBigInt(BigInt* a, BigInt* b) {
    if (a == NULL || b == NULL) return NULL;

    char sinalA = a->sinal;
    char sinalB = b->sinal;

    // sinais diferentes: a - b == a + (-b)
    if (sinalA != sinalB) {
        // cria cópia de b com sinal invertido
        BigInt *b_invertido = (BigInt*)malloc(sizeof(BigInt));
        if (!b_invertido) return NULL;
        *b_invertido = *b;
        b_invertido->sinal = sinalA; // inverter sinal para somar com mesmo sinal de a // função de adição trata os sinais
        BigInt *result = addBigInt(a, b_invertido);
        free(b_invertido);
        return result;
    }

    // mesmos sinais: se positivos, se b > a então resultado negativo, caso contrário positivo
    // mesmos sinais: se negativos soma e mantem sinal negativo
    if (sinalA == '+') {
        if (isGreaterThan(a, b) == 1) {
                return subtract_aux(a, b);
        } else {
            BigInt *res = subtract_aux(b, a);
            if (res) {
                    res->sinal = (sinalA == '+') ? '-' : '+'; // inverter sinal
            }
            return res;
        }
    } else {
        BigInt *res = addBigInt(a, b);
        return res;
    }
    return NULL; // caso não previsto

}

// Função para imprimir 
/*
    Descrição da função:
    - Imprime o valor do BigInt na saída padrão.
    - Imprime o sinal se negativo (evita imprimir -0).
    - Imprime os dígitos do BigInt do mais-significativo para o menos-significativo.
*/

void printBigInt(const BigInt* bigInt) {
    if (bigInt == NULL || bigInt->start == NULL) {
        printf("BigInt nulo\n");
        return;
    }

    // imprimir sinal se negativo e não for zero evitar imprimir -0
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

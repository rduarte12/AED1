#ifndef BIGINT_H
#define BIGINT_H

/*
    Estrutura: BigInt representa um número inteiro grande usando uma lista duplamente ligada.
    
    Lista de Funções:
    - BigInt *createBigInt(char* str);
    - void freeBigInt(BigInt* bigInt);
    - void printBigInt(const BigInt* bigInt);
    - int isGreaterThan(const BigInt* a, const BigInt* b);
    - int isLessThan(const BigInt* a, const BigInt* b);
    - int isEqualTo(const BigInt* a, const BigInt* b);
    - BigInt* addBigInt(BigInt* a, BigInt* b);
    - BigInt* subtractBigInt(BigInt* a, BigInt* b);
    
*/
typedef struct BigInt BigInt;

/* Cria um BigInt a partir de uma string (sinal opcional).
   Retorna BigInt* alocado ou NULL em erro. A string pode conter '+'/'-' e zeros à esquerda. */
BigInt* createBigInt(char* str);

/* Libera memória associada ao BigInt (nulo seguro). */
void freeBigInt(BigInt* bigInt);

/* Imprime o BigInt no stdout (não altera a estrutura). */
void printBigInt(const BigInt* bigInt);

/* Comparações:
   - Retorno:  1 = verdadeiro, 0 = falso, -1 = erro (entrada nula).
   - As funções consideram sinal e magnitude conforme convenção do projeto.
*/
int isGreaterThan(const BigInt* a, const BigInt* b);
int isLessThan(const BigInt* a, const BigInt* b);
int isEqualTo(const BigInt* a, const BigInt* b);

/* Operações aritméticas:
   - Retornam um BigInt* novo (alocado) com o resultado, ou NULL em erro.
   - O chamador é responsável por freeBigInt() do resultado.
*/
BigInt* addBigInt(BigInt* a, BigInt* b);
BigInt* subtractBigInt(BigInt* a, BigInt* b);


#endif /* BIGINT_H */
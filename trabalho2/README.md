
## 1. **Planejamento Inicial**

- Leia todo o enunciado e marque os requisitos obrigatórios:
  - Operações a serem implementadas: soma, maior, menor, igual.
  - Criar estrutura lista encadeada para armazenar números grandes.
  - Entrada padrão: comandos de operação + números.
  - Saída padrão: resultado conforme especificado.
  - Modularidade: separar funções em biblioteca própria.
  - Usar Makefile para compilar.
  - Documentação e desalocação de memória (valgrind).
  - Relatório com justificativas e explicações.

***

## 2. **Estruturação do Projeto**

### Diretórios e Arquivos

- **Raiz do projeto**
  - README.txt ou README.md (opcional - instruções de uso)
  - Makefile
  - main.c (arquivo principal, entrada/saída e chamada das funções)
  - /bignum/
    - bignum.h (cabeçalho da biblioteca de grandes números)
    - bignum.c (implementação das funções da biblioteca)
    - (opcional) testes_bignum.c
  - /docs/
    - relatorio.txt ou relatorio.pdf

***

## 3. **Desenvolvimento da Biblioteca**

### 3.1. Estrutura de Dados

- Defina em `bignum.h`:
```c
#define DIGITS_PER_NODE 4 // exemplo
typedef struct Node {
    int block;
    struct Node* next;
} Node;

typedef struct {
    Node *head;
    int is_negative;
} BigNum;
```

### 3.2. Funções a Implementar

- Conversão de string para BigNum (`BigNum* str_to_bignum(const char* s)`)
- Soma de dois BigNum (`BigNum* add_bignum(BigNum* a, BigNum* b)`)
- Comparação: 
  - igual (`int equals_bignum(BigNum* a, BigNum* b)`)
  - maior (`int greater_bignum(BigNum* a, BigNum* b)`)
  - menor (`int lesser_bignum(BigNum* a, BigNum* b)`)
- Impressão de BigNum (`void print_bignum(BigNum* num)`)
- Liberação de memória (`void free_bignum(BigNum* num)`)

***

## 4. **Implementação do Programa Principal (main.c)**

- Ler número de operações (n).
- Para cada comando: ler operação e números.
- Chamar função adequada da biblioteca.
- Imprimir resultado conforme formato exigido.

***

## 5. **Makefile**

- Criar regras para compilar separadamente (bignum.c em bignum.o, etc)
- Regra para limpar compilados (`make clean`)
- Exemplo básico:
```makefile
all: main
main: main.o bignum.o
    gcc -o main main.o bignum.o
main.o: main.c bignum.h
    gcc -c main.c
bignum.o: bignum.c bignum.h
    gcc -c bignum.c
clean:
    rm -f *.o main
```

***

## 6. **Testes e Validação**

- Testar todos casos do enunciado e adicionais.
- Usar `valgrind` para garantir liberação da memória.

***

## 7. **Documentação e Relatório**

- Comentar funções e partes críticas do código.
- Escrever o relatório respondendo às perguntas obrigatórias.
- Descrever decisões de implementação, dificuldades, limitações e contribuições.

***

## 8. **Checklist Antes da Entrega**

- Todos arquivos organizados.
- Código compilando via Makefile.
- Memória sempre desalocada.
- Testes feitos, saída conforme esperado.
- Relatório pronto e revisado.

***

Siga esse roteiro e adapte conforme seu ritmo de estudo. Se precisar de exemplos específicos de função ou de Makefile, pode pedir!

[1](file:///C:/Users/duart/Downloads/Trabalho2.pdf)
#include <stdio.h>
#include <stdlib.h>

/*
   ==============================
   REPRESENTAÇÃO DA LISTA GERAL
   ==============================

   A ideia é representar uma "lista generalizada", tipo:

       (1,2,(3,4),())

   Cada elemento dentro desses parênteses pode ser:
   - um número (átomo)
   - outra lista entre parênteses (sublista)
   - uma lista vazia ()

   Exemplo:
       ((1,2),(3,(4,5)),6,())
        ^^^^^   ^^^^^^^  ^^^
         lista   lista   lista vazia

   Nós vamos montar isso usando nós encadeados.
*/


/*
    NodeType diz qual tipo de dado está guardado no nó:
    - ATOM significa que o nó guarda um número inteiro.
    - LIST significa que o nó guarda uma sublista (outro nível de parênteses).
*/
typedef enum {
    ATOM = 0, // nó que guarda um átomo (inteiro)
    LIST = 1  // nó que guarda uma sublista
} NodeType;


/*
    Nosso nó da lista encadeada.

    Cada nó tem:
    - type: ATOM ou LIST
    - head: uma union que guarda OU um inteiro (se for ATOM)
            OU um ponteiro para o primeiro elemento da sublista (se for LIST)
    - tail: ponteiro para o próximo nó no MESMO NÍVEL

    Importante:
    "head" é o conteúdo principal do nó.
    "tail" é o próximo irmão do mesmo nível.
*/
typedef struct node {
    NodeType type;  // ATOM ou LIST

    union {
        int atom;          // se type == ATOM: valor do átomo
        struct node *list; // se type == LIST: ponteiro pro 1o elemento da sublista
    } head; // "cabeça" da lista generalizada

    struct node *tail; // "cauda": próximo elemento no mesmo nível
} node;


/*
   =========================
   FUNÇÕES DE CONSTRUÇÃO
   =========================
*/

/*
    new_atom:
    cria dinamicamente (com malloc) um nó que guarda um inteiro.

    Exemplo:
        new_atom(42) cria um nó ATOM com valor 42.
*/
node *new_atom(int v) {
    node *n = (node*)malloc(sizeof(node));
    n->type = ATOM;
    n->head.atom = v;
    n->tail = NULL; // ainda não tem próximo no mesmo nível
    return n;
}

/*
    new_list:
    cria um nó LIST que aponta para o primeiro elemento da sublista interna.

    Se first_elem == NULL, isso representa a lista vazia: ()
    Exemplo:
        new_list(NULL)  => representa "()"
*/
node *new_list(node *first_elem) {
    node *n = (node*)malloc(sizeof(node));
    n->type = LIST;
    n->head.list = first_elem; // pode ser NULL para lista vazia
    n->tail = NULL;            // esse nó LIST pode estar num nível e ter um "irmão" depois
    return n;
}

/*
    append:
    insere um novo nó 'elem' no final de uma lista encadeada de nós
    do mesmo nível.

    Imagine o nível atual como uma fila ligada por tail:

        head -> [nó1] -> [nó2] -> [nó3] -> NULL

    Se eu quiser colocar [nó4] no final, preciso andar
    até o último e ligar tail dele para [nó4].

    Retorna sempre o ponteiro para o primeiro nó daquele nível.
    (isso é útil porque se head era NULL, o novo head passa a ser elem)
*/
node *append(node *head, node *elem) {
    if (head == NULL) {
        // lista estava vazia, então agora o primeiro nó é elem
        return elem;
    } else {
        // senão, caminha até o último e coloca elem lá
        node *cur = head;
        while (cur->tail != NULL) {
            cur = cur->tail;
        }
        cur->tail = elem;
        return head; // cabeça não mudou
    }
}


/*
   =========================
   PARSER
   =========================

   Vamos transformar uma string como:
       ((1,2),(3,(4,5)),6,())

   em nós encadeados.

   Regras da entrada:
   - Sempre começa com '(' e termina com ')'.
   - Não tem espaços.
   - Vamos assumir que a entrada está bem formada.
   - Vamos percorrer a string com um ponteiro char* que anda.
     Para permitir que as funções atualizem esse ponteiro,
     passamos "char **s" para elas.

   Ideia geral:
      parse_list lê algo do tipo "( ... )"
      parse_element descobre se é um átomo ou outra lista
      parse_int lê um inteiro (possivelmente com sinal -)
*/

/*
    parse_int:
    Lê um número inteiro na string, avançando o ponteiro.

    Exemplo:
      se *s aponta pra "-123,(" depois da chamada
      retorna -123
      e agora *s vai estar apontando para ",(" (logo depois do número)
*/
int parse_int(char **s) {
    int sign = 1;
    int val = 0;

    // checa se tem sinal negativo
    if (**s == '-') {
        sign = -1;
        (*s)++; // avança o ponteiro para depois do '-'
    }

    // lê todos os dígitos consecutivos
    while (**s >= '0' && **s <= '9') {
        val = val * 10 + (**s - '0'); // acumula o valor
        (*s)++; // anda para o próximo caractere
    }

    return sign * val;
}

// Declarações antecipadas porque uma função chama a outra
node *parse_element(char **s); // lê átomo OU sublista
node *parse_list(char **s);    // lê "( ... )"

/*
    parse_element:
    Decide que tipo de nó vem agora.

    Se o próximo caractere é '(' então isso é uma SUBLISTA,
    então chamamos parse_list.

    Caso contrário, assumimos que é um inteiro,
    criamos um nó ATOM com new_atom.
*/
node *parse_element(char **s) {
    if (**s == '(') {
        // sublista
        return parse_list(s);
    } else {
        // átomo numérico
        int v = parse_int(s);
        return new_atom(v);
    }
}

/*
    parse_list:
    Lê uma lista entre parênteses, por exemplo:
        (1,2,(3,4),())

    Passo a passo:
    1. consome o '('
    2. caso especial: se logo vem ')', então é "()"
    3. lê o primeiro elemento obrigatoriamente
    4. enquanto tiver vírgula ',', lê mais elementos
    5. consome o ')'
    6. cria um nó LIST apontando para a sequência encadeada desses elementos

    Observação:
    O que parse_list retorna NÃO é a "lista interna crua".
    Ele retorna um nó LIST cujo head.list aponta para essa lista interna.
*/
node *parse_list(char **s) {
    (*s)++; // consome '(' e avança o ponteiro na string

    node *level_head = NULL; // este vai ser o primeiro nó do nível atual

    // Caso especial: "()"
    // Se logo depois de '(' já veio ')', então a lista é vazia.
    if (**s == ')') {
        (*s)++; // consome ')'
        // cria um nó LIST que aponta pra NULL
        return new_list(NULL);
    }

    /*
        Agora vamos ler o PRIMEIRO elemento da lista.
        Exemplo em "(10,20,30)": primeiro elemento é "10"
        Exemplo em "((1,2),3)": primeiro elemento é "(1,2)"
    */
    node *elem = parse_element(s);
    level_head = append(level_head, elem);

    /*
        Agora pode ter mais elementos separados por vírgula.
        Exemplo:
           depois de ler "10", a string está em ",20,30)"
           então enquanto eu ver ',', eu continuo lendo.
    */
    while (**s == ',') {
        (*s)++; // consome ','
        node *next_elem = parse_element(s);
        level_head = append(level_head, next_elem);
    }

    /*
        Terminamos de ler elementos desse nível.
        Agora esperamos encontrar ')', que fecha a lista atual.
        Exemplo:
            depois de ler "30", a string está em ")"
    */
    if (**s == ')') {
        (*s)++; // consome ')'
    }

    /*
        Agora criamos um nó LIST "embrulhando" todos os elementos
        que estavam dentro desses parênteses.

        Por exemplo:
            Se eu li "(1,2,3)"
            level_head = nó[1] -> nó[2] -> nó[3] -> NULL
            retorno: LIST cuja head.list aponta pra nó[1]
    */
    return new_list(level_head);
}


/*
   =========================
   IMPRESSÃO
   =========================

   Queremos imprimir a estrutura reconstruindo o mesmo formato
   que o usuário digitou.

   Regras de impressão:
     - Átomo: imprime só o número, tipo "42"
     - Lista: imprime "(" ... ")" de novo.
     - Lista vazia: imprime "()"

   Exemplo:
     se a estrutura representa ((1,2),(3,(4,5)),6,())
     a impressão deve sair exatamente assim.
*/

/*
    print_node:
    Imprime UM nó.

    Se for ATOM, imprime o inteiro.
    Se for LIST, imprime "(" <conteúdo interno> ")".

    Observação:
    Para LIST, head.list é o primeiro elemento interno.
*/
void print_node(node *n); // declaração antecipada

/*
    print_list_elems:
    Imprime uma sequência de nós em um mesmo nível,
    separados por vírgula.
    Exemplo:
        nível: [1] -> [2] -> [sublista] -> NULL
        saída: "1,2,(...)"
*/
void print_list_elems(node *n) {
    node *cur = n;
    while (cur != NULL) {
        print_node(cur);
        if (cur->tail != NULL) {
            // se existe próximo no mesmo nível, imprime vírgula
            printf(",");
        }
        cur = cur->tail;
    }
}

/*
    print_node:
    - Se n == NULL, isso representa uma lista vazia "()".
      Isso só acontece quando imprimimos o conteúdo de uma
      LIST vazia.
    - Se for ATOM: imprime o número.
    - Se for LIST: imprime "(" ... ")",
      chamando print_list_elems para imprimir os elementos
      internos daquela sublista.
*/
void print_node(node *n) {
    if (n == NULL) {
        // lista vazia
        printf("()");
        return;
    }

    if (n->type == ATOM) {
        // nó que guarda só um número
        printf("%d", n->head.atom);
    } else { // LIST
        // nó que guarda uma sublista
        printf("(");
        print_list_elems(n->head.list);
        printf(")");
    }
}


/*
   =========================
   LIBERAR MEMÓRIA
   =========================

   free_node:
   Libera toda a memória alocada recursivamente.

   Regras:
   - Se o nó é ATOM, só dá free nele.
   - Se o nó é LIST, eu preciso antes liberar todos os nós
     que estão dentro dessa sublista, depois dou free nele.

   Cuidado:
   A sublista é uma cadeia encadeada via tail,
   então preciso caminhar e liberar cada um.
*/
void free_node(node *n) {
    if (n == NULL) return;

    if (n->type == LIST) {
        // libera a lista interna inteira
        node *sub = n->head.list;
        while (sub != NULL) {
            node *next = sub->tail; // guarda próximo antes de liberar
            free_node(sub);         // libera recursivamente
            sub = next;             // avança
        }
    }

    // finalmente libera o próprio nó
    free(n);
}



// percorre os elementos da lista e retorna a profundidade máxima
int contadorNiveis_rec(node *elem, int depth) {
    // caso base, se chegou ao fim da lista naquele nível retorna a profundidade atual
    if (elem == NULL) return depth;

    int maxDepth = depth;                                           // determina a profundiadde máxima encontrada

    node *iter = elem;                                              // inicia um iterador para percorrer a lista
    while (iter != NULL) {                                          // Um loop para percorrer os elementos da lista. Para cada elementos, chamo novamente a função se for uma sublista
        if (iter->type == LIST) {                                   // Para cada elementos, chamo novamente a função se for uma sublista, chama recursivamente aumentando a profundidade      
            int d = contadorNiveis_rec(iter->head.list, depth + 1);
            if (d > maxDepth) maxDepth = d;                         // atualiza a profundidade máxima se necessário
        }
        iter = iter->tail;                                   // avança para o próximo elemento no mesmo nível           
    }
    return maxDepth;
}


/*
    =========================
    Contagem do número de níveis da lista generalizada
    =========================

    Função recursiva para contar o número de níveis de aninhamento
    em uma lista generalizada.

    A primeira camada de parênteses conta como 0 níveis.
*/
int contadorNiveis(node *n) {
    // Caso base: se n == NULL ou átomo, não há níveis a contar
    if (n == NULL) return 0;
    if (n->type == ATOM) return 0;

    // A lista `n` é a lista raiz do nível 0
    return contadorNiveis_rec(n->head.list, 0);
}



// percorre os elementos da lista e retorna a profundidade do elemento procurado
int procuraElemento_rec(node *elem, int depth, int elemento) {
    // caso base, se chegou ao fim da lista naquele nível retorna -1 (não encontrado)
    if (elem == NULL) return -1;

    node *iter = elem;                                              // inicia um iterador para percorrer a lista
    while (iter != NULL) {                                          // Um loop para percorrer os elementos da lista. Para cada elementos, chamo novamente a função se for uma sublista
        if (iter->type == ATOM) {                                   // Se for átomo, verifica se é o elemento procurado
            if (iter->head.atom == elemento) {
                return depth;                                       // retorna a profundidade se encontrado
            }
        } else if (iter->type == LIST) {                            // Se for sublista, chama recursivamente aumentando a profundidade
            int d = procuraElemento_rec(iter->head.list, depth + 1, elemento);
            if (d != -1) {
                return d;                                           // retorna a profundidade se encontrado na sublista
            }
        }
        iter = iter->tail;                                   // avança para o próximo elemento no mesmo nível           
    }
    return -1;                                                     // retorna -1 se não encontrado
}


/*
    =========================
    Procura por um elemento na lista generalizada
    =========================

    Função recursiva para procurar um elemento
    em uma lista generalizada.

    Retorna -1 se não encontrar o elemento
    ou a profundidade do elemento se encontrado.
*/
int procuraElemento(node *n, int elemento) {
    // Caso base: se n == NULL ou átomo, não há níveis a contar
    if (n == NULL) return -1;

    // A lista `n` é a lista raiz do nível 0
    return procuraElemento_rec(n->head.list, 0, elemento);
}

/*
   =========================
   MAIN
   =========================

   Fluxo do main:
   1. Lê uma linha do usuário (ex: "((1,2),(3,(4,5)),6,())").
   2. Cria um ponteiro char* ptr apontando para o começo da string.
   3. Chama parse_list(&ptr) porque sempre começa com '('.
   4. Mostra a lista impressa de volta.
   5. Mostra o número de níveis da lista.
   6. Libera memória.

   Observação importante:
   Sempre assumimos que a string tem parênteses externos.
   Por exemplo "(42)" e não "42" direto.
*/
int main() {
    char buffer[1024]; // guarda a linha digitada

    int elementoProcurado;
    scanf("%d\n", &elementoProcurado);


    if (!fgets(buffer, sizeof(buffer), stdin)) {
        // se fgets falhar (EOF etc.), só termina
        return 1;
    }

    // ptr vai andar pela string durante o parsing
    char *ptr = buffer;

    // raiz SEMPRE é uma lista entre parênteses
    node *root = parse_list(&ptr);

    // Mostra a profundidade do elemento procurado
    int profundidade = procuraElemento(root, elementoProcurado);
    printf("%d\n", profundidade);

    // libera toda a memória alocada
    free_node(root);
    return 0;
}
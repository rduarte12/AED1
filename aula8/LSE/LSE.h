#ifndef LSE_H
#define LSE_H
/*
   Convenções de retorno:

   -1 → Erro
        - Ponteiro NULL
        - Posição inválida
        - Lista cheia/vazia quando não deveria
        - Falha de alocação
        - Parâmetro de saída NULL (ex: ponteiro para receber elemento ou posição)

    1 → Sucesso ou condição verdadeira
        - Operação realizada com êxito (inserção, remoção, criação, destruição, etc.)
        - Condição satisfeita (ex: lista está vazia, lista está cheia, elemento encontrado)

    0 → Sucesso com condição falsa
        - Condição verificada não se aplica (ex: lista **não** está vazia, elemento **não** encontrado)
        - Retornos intermediários que não configuram erro, mas sinalizam ausência de ocorrência esperada

    >1 → Retornos bem-sucedidos com valor informativo
        - Ex: quantidade de elementos, posição encontrada, etc. (quando for o caso)

    Obs: O padrão evita misturar valores negativos com positivos para distinguir claramente erros de sucesso.
*/

/* Capacidade máxima da lista */
#define LSE_MAX 100
/* Tipo dos elementos armazenados na lista */
typedef int LSE_Tipo;

/* Estrutura da lista sequencial estática */
typedef struct {
    LSE_Tipo dados[LSE_MAX];
    int qtd;  // quantidade atual de elementos
} LSE;

/* ==== Criação e Destruição ==== */

// Cria uma nova lista e retorna o ponteiro para ela.
// Retorna NULL em caso de erro de alocação.
LSE *lse_cria(void);

// Libera a memória da lista e define o ponteiro como NULL.
// Retorna 1 em caso de sucesso, -1 se ponteiro inválido.
int lse_destroi(LSE **l);

/* ==== Estado da Lista ==== */

// Retorna 1 se a lista está vazia, 0 se não está, -1 se ponteiro inválido.
int lse_vazia(const LSE *l);

// Retorna 1 se a lista está cheia, 0 se não está, -1 se ponteiro inválido.
int lse_cheia(const LSE *l);

// Retorna a quantidade de elementos na lista, -1 se ponteiro inválido.
int lse_tamanho(const LSE *l);

/* ==== Inserção e Remoção ==== */

// Insere um elemento no final da lista.
// Retorna 1 em caso de sucesso, -1 em caso de erro.
int lse_insere_final(LSE *l, LSE_Tipo elem);

// Insere um elemento na posição especificada (0 ≤ pos ≤ qtd).
// Retorna 1 em caso de sucesso, -1 em caso de erro.
int lse_insere_pos(LSE *l, int pos, LSE_Tipo elem);

// Remove o elemento da posição especificada (0 ≤ pos < qtd) e armazena em 'removido'.
// Retorna 1 em caso de sucesso, -1 em caso de erro.
int lse_remove_pos(LSE **l, int pos, LSE_Tipo *removido);

/* ==== Consulta e Busca ==== */

// Consulta o elemento da posição especificada e armazena em 'elem'.
// Retorna 1 em caso de sucesso, -1 em caso de erro.
int lse_consulta_pos(const LSE *l, int pos, LSE_Tipo *elem);

// Busca um elemento na lista. Se encontrar, armazena a posição em 'pos'.
// Retorna 1 se encontrar, 0 se não encontrar, -1 em caso de erro.
int lse_busca(const LSE *l, LSE_Tipo elem, int *pos);

/* ==== Utilitários ==== */

// Limpa a lista, zerando a quantidade de elementos.
// Retorna 1 em caso de sucesso, -1 se ponteiro inválido.
int lse_limpa(LSE *l);

// Imprime os elementos da lista (formato livre).
// Retorna 1 em caso de sucesso, -1 se ponteiro inválido.
int lse_imprime(const LSE *l);

#endif /* LSE_H */
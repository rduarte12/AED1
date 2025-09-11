
#include <stdio.h>
#include <stdlib.h>
#include "LSE.h"

/* ==== Criação e Destruição ==== */

// Cria uma nova lista e retorna o ponteiro para ela.
// Retorna NULL em caso de erro de alocação.
LSE *lse_cria(void) {
    LSE *l = (LSE *)malloc(sizeof(LSE));
    if (l != NULL) {
        l -> qtd = 0;
    }
    return l;
}

// Libera a memória da lista e define o ponteiro como NULL.
// Retorna 1 em caso de sucesso, -1 se ponteiro inválido.
int lse_destroi(LSE **l) {
    if (*l == NULL || l == NULL) {
        return -1;
    }
    free(*l);
    *l = NULL;
    return 1;
}

/* ==== Estado da Lista ==== */

// Retorna 1 se a lista está vazia, 0 se não está, -1 se ponteiro inválido.
int lse_vazia(const LSE *l) {
    if (l == NULL) {
        return -1;
    }
    return (l -> qtd == 0) ? 1 : 0;
}

// Retorna 1 se a lista está cheia, 0 se não está, -1 se ponteiro inválido.
int lse_cheia(const LSE *l) {
    if (l == NULL) {
        return -1;
    }
    return (l -> qtd == LSE_MAX) ? 1 : 0;
}

// Retorna a quantidade de elementos na lista, -1 se ponteiro inválido.
int lse_tamanho(const LSE *l) {
    if (l == NULL) {
        return -1;
    }
    return l -> qtd;
}

/* ==== Inserção e Remoção ==== */

// Insere um elemento no final da lista.
// Retorna 1 em caso de sucesso, -1 em caso de erro.
int lse_insere_final(LSE *l, LSE_Tipo elem) {
    if (l == NULL || lse_cheia(l) == 1) {
        return -1;
    }
    l -> dados[l -> qtd] = elem;
    l -> qtd++;
    return 1;
}

// Insere um elemento na posição especificada (0 ≤ pos ≤ qtd).
// Retorna 1 em caso de sucesso, -1 em caso de erro.
int lse_insere_pos(LSE *l, int pos, LSE_Tipo elem) {
    if (l == NULL || pos < 0 || pos > l -> qtd || lse_cheia(l) == 1) {
        return -1;
    }
    for (int i = l -> qtd; i > pos; i--){
        l -> dados[i] = l -> dados[i - 1];
    }
    l -> dados[pos] = elem;
    l -> qtd++;
    return 1;
}

// Remove o elemento da posição especificada (0 ≤ pos < qtd) e armazena em 'removido'.
// Retorna 1 em caso de sucesso, -1 em caso de erro.
int lse_remove_pos(LSE **l, int pos, LSE_Tipo *removido) {
    if (*l == NULL || pos < 0 || pos >= (*l) -> qtd || lse_vazia(*l) == 1) {
        return -1;
    }

    for (int i = pos; i < (*l) -> qtd - 1; i++) {
        if (i == pos) {
            *removido = (*l) -> dados[i];
        }
        (*l) -> dados[i] = (*l) -> dados[i + 1];
    }
    (*l) -> qtd--;
    return 1;
}

/* ==== Consulta e Busca ==== */

// Consulta o elemento da posição especificada e armazena em 'elem'.
// Retorna 1 em caso de sucesso, -1 em caso de erro.
int lse_consulta_pos(const LSE *l, int pos, LSE_Tipo *elem) {
        if (l == NULL || pos < 0 || pos >= l -> qtd || lse_vazia(l) == 1) {
        return -1;
    }
    *elem = l -> dados[pos];
    return 1;
}

// Busca um elemento na lista. Se encontrar, armazena a posição em 'pos'.
// Retorna 1 se encontrar, 0 se não encontrar, -1 em caso de erro.
int lse_busca(const LSE *l, LSE_Tipo elem, int *pos) {
    if (l == NULL || pos == NULL) {
        return -1;
    }
    for (int i = 0; i < l -> qtd; i++) {
        if (l -> dados[i] == elem) {
            *pos = i;
            return 1;
        }
    }
    return 0;
}

/* ==== Utilitários ==== */

// Limpa a lista, zerando a quantidade de elementos.
// Retorna 1 em caso de sucesso, -1 se ponteiro inválido.
int lse_limpa(LSE *l) {
    if (l == NULL) {
        return -1;
    }
    l -> qtd = 0;
    return 1;
}

// Imprime os elementos da lista (formato livre).
// Retorna 1 em caso de sucesso, -1 se ponteiro inválido.
int lse_imprime(const LSE *l) {
    if (l == NULL) {
        return -1;
    }
    if (l->qtd == 0) {
        printf("[]\n");
        return 1;
    }
    printf("[%d", l->dados[0]);
    for (int i = 1; i < l->qtd; i++) {
        printf(", %d", l->dados[i]);
    }
    printf("]\n");
    return 1;
}
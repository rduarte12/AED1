#include <stdio.h>
#include <stdlib.h>
#include "LSD.h"

int lsd_garante_capacidade(LSD *l) {
    if (!l) return -1;
    if (l->qtd < l->cap) return 1;

    int nova_cap = (l->cap == 0) ? 4 : l->cap * 2;

    LSD_Tipo *novo = realloc(l->dados, (size_t)nova_cap * sizeof(LSD_Tipo));
    if (!novo) return -1;

    l->dados = novo;
    l->cap = nova_cap;
    return 1;
}

LSD *lsd_cria(void) {
    LSD *l = malloc(sizeof(LSD));
    if (!l) return NULL;
    l->dados = NULL;
    l->qtd = 0;
    l->cap = 0;
    return l;
}

int lsd_destroi(LSD **l) {
    if (!l) return -1;
    if (!*l) return 0;
    free((*l)->dados);
    free(*l);
    *l = NULL;
    return 1;
}

int lsd_vazia(const LSD *l) {
    if (!l) return -1;
    return l->qtd == 0 ? 1 : 0;
}

int lsd_tamanho(const LSD *l) {
    if (!l) return -1;
    return l->qtd;
}

int lsd_capacidade(const LSD *l) {
    if (!l) return -1;
    return l->cap;
}

int lsd_insere_final(LSD *l, LSD_Tipo elem) {
    if (!l) return -1;
    if (lsd_garante_capacidade(l) == -1) return -1;
    l->dados[l->qtd++] = elem;
    return 1;
}

int lsd_insere_pos(LSD *l, int pos, LSD_Tipo elem) {
    if (!l) return -1;
    if (pos < 0 || pos > l->qtd) return -1;
    if (lsd_garante_capacidade(l) == -1) return -1;

    for (int i = l->qtd - 1; i >= pos; --i)
        l->dados[i + 1] = l->dados[i];

    l->dados[pos] = elem;
    l->qtd++;
    return 1;
}

int lsd_remove_pos(LSD *l, int pos, LSD_Tipo *removido) {
    if (!l || !removido) return -1;
    if (pos < 0 || pos >= l->qtd) return -1;

    *removido = l->dados[pos];
    for (int i = pos + 1; i < l->qtd; ++i)
        l->dados[i - 1] = l->dados[i];

    l->qtd--;
    return 1;
}

int lsd_consulta_pos(const LSD *l, int pos, LSD_Tipo *elem) {
    if (!l || !elem) return -1;
    if (pos < 0 || pos >= l->qtd) return -1;
    *elem = l->dados[pos];
    return 1;
}

int lsd_busca(const LSD *l, LSD_Tipo elem, int *pos) {
    if (!l || !pos) return -1;
    for (int i = 0; i < l->qtd; i++) {
        if (l->dados[i] == elem) {
            *pos = i;
            return 1;
        }
    }
    *pos = -1;
    return 0;
}

int lsd_limpa(LSD *l) {
    if (!l) return -1;
    l->qtd = 0;
    return 1;
}

int lsd_imprime(const LSD *l) {
    if (!l) return -1;
    printf("[");
    for (int i = 0; i < l->qtd; i++) {
        printf("%d", l->dados[i]);
        if (i < l->qtd - 1) printf(", ");
    }
    printf("]\n");
    return 1;
}

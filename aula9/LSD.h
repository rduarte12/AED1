#ifndef LSD_H
#define LSD_H

typedef int LSD_Tipo;

typedef struct {
    LSD_Tipo *dados;
    int qtd;
    int cap;
} LSD;

LSD *lsd_cria(void);
int lsd_destroi(LSD **l);

int lsd_vazia(const LSD *l);
int lsd_tamanho(const LSD *l);
int lsd_capacidade(const LSD *l);

int lsd_insere_final(LSD *l, LSD_Tipo elem);
int lsd_insere_pos(LSD *l, int pos, LSD_Tipo elem);
int lsd_remove_pos(LSD *l, int pos, LSD_Tipo *removido);

int lsd_consulta_pos(const LSD *l, int pos, LSD_Tipo *elem);
int lsd_busca(const LSD *l, LSD_Tipo elem, int *pos);

int lsd_limpa(LSD *l);
int lsd_imprime(const LSD *l);

/* 
   Função auxiliar que garante espaço para novas inserções.
   Se a lista estiver cheia, realoca o vetor interno dobrando a capacidade.
*/
int lsd_garante_capacidade(LSD *l);

#endif /* LSD_H */

#include <stdio.h>
#include <stdlib.h>
#include "LSE.h"


int main() {
    LSE *lista = lse_cria();
    if (lista == NULL) {
        printf("Erro ao criar a lista.\n");
        return -1;
    }

    int flag = 1;
    while (flag) {
        
        int opt;
        scanf("%d", &opt);
        switch (opt) {
            case 1: {

                int x;
                scanf("%d", &x);
                int res = lse_insere_final(lista, x);
                printf("%d\n", res);
                break;

            }
            case 2: {
                int pos, x;
                scanf("%d %d", &pos, &x);
                int res = lse_insere_pos(lista, pos, x);
                printf("%d\n", res);
                break;
            }
            case 3: {
                int pos, removido, res;
                scanf("%d", &pos);
                res = lse_remove_pos(&lista, pos, &removido);
                if (res == 1) {
                    printf("%d\n", removido);
                } else {
                    printf("ERRO\n");
                }
                break;
            }
            case 4: {
                int pos, elem, res;
                scanf("%d", &pos);
                res = lse_consulta_pos(lista, pos, &elem);
                if (res == 1) {
                    printf("%d\n", elem);
                } else {
                    printf("ERRO\n");
                }
                break;
            }
            case 5: {
                int x, res, pos;
                scanf("%d", &x);
                res = lse_busca(lista, x, &pos);
                if (res == 1) {
                    printf("%d\n", pos);
                } else {
                    printf("-1\n");
                }
                break;
            }
            case 6: {
                printf("%d\n", lse_tamanho(lista));
                break;
            }
            case 7: {
                lse_imprime(lista);
                break;
            }
            case 8: {
                lse_limpa(lista);
                break;
            }
            case 9: {
                int res = lse_destroi(&lista);
                if (res == 1) {
                    flag = 0;
                }
                break;
                return 0;
            }
        }
    }
}
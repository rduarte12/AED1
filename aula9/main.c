#include <stdio.h>
#include <stdlib.h>
#include "LSD.h"

/**
 • 1 x Inserir x no final. Imprimir 1 se sucesso, 0 se falha.
 • 2 p x Inserir x na posição p (0..qtd). Imprimir 1 ou 0.
 • 3p Removerelementodaposiçãop. Sesucesso, imprimir ovalor removido;
   caso contrário imprimir ERRO.
 • 4 p Consultar elemento da posição p. Se sucesso, imprimir o valor; senão
   imprimir ERRO.
 • 5 x Buscar a primeira ocorrência de x. Imprimir a posição se encontrado,
   ou -1 caso contrário.
 • 6 Imprimir o tamanho atual da lista usando lsd_tamanho.
 • 7 Imprimir a lista com lsd_imprime, no formato [a, b, c].
 • 8 Esvaziar a lista com lsd_limpa. Não imprime nada.
 • 9 Encerrar o programa
*/

int main() {

    LSD *lista = lsd_cria();
    if (!lista) {
        printf("ERRO\n");
        return 1;
    }

    int flag = 1;
    while (flag) {
        int opt;
        scanf("%d", &opt);
        switch (opt) {
            case 1: {
                int x;
                scanf("%d", &x);
                int res = lsd_insere_final(lista, x);
                if (res == 1) printf("1\n");
                else printf("0\n");
                break;
            }
            case 2: {
                int p, x;
                scanf("%d %d", &p, &x);
                int res = lsd_insere_pos(lista, p, x);
                if (res == 1) printf("1\n");
                else printf("0\n");
                break;
            }
            case 3: {
                int p;
                scanf("%d", &p);
                int removido;
                int res = lsd_remove_pos(lista, p, &removido);
                if (res == 1) printf("%d\n", removido);
                else printf("ERRO\n");
                break;
            }
            case 4: {
                int p;
                scanf("%d", &p);
                int elem;
                int res = lsd_consulta_pos(lista, p, &elem);
                if (res == 1) printf("%d\n", elem);
                else printf("ERRO\n");
                break;
            }
            case 5: {
                int x;
                scanf("%d", &x);
                int pos;
                int res = lsd_busca(lista, x, &pos);
                if (res == 1) printf("%d\n", pos);
                else if (res == 0) printf("-1\n");
                else printf("ERRO\n");
                break;
            }
            case 6: {
                int tamanho = lsd_tamanho(lista);
                if (tamanho != -1) printf("%d\n", tamanho);
                else printf("ERRO\n");
                break;
            }
            case 7: {
                int res = lsd_imprime(lista);
                if (res == -1) printf("ERRO\n");
                break;
            }
            case 8: {
                lsd_limpa(lista);
                break;
            }
            case 9: {
                flag = 0;
                break;
            }
            default:
                printf("ERRO\n");
        }
    }

    lsd_destroi(&lista);
    return 0;

}
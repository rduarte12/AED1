#include <stdio.h>
#include "LinkedList.h"
#include <stdlib.h>


// funcao para pegar o node 0 em lx, remover o node 0 de lx e inserir na ultima posição de la para todos os elementos em lx
void transfer_nodes(LinkedList *lx, LinkedList *la) {
    // verifica se as listas existe
    if (!lx || !la) {
        return;
    }
    //verifica o tamanho de lx
    int size = size_list(lx);
    
    //itera sobre cada mó da lista
    for (int i = 0; i < size; i++) {
        int value;
        int res = get_node(lx, 0, &value);
        (void)res;
        res = remove_node(lx, 0, &value);
        res = insert_node(la, size_list(la), value);
    }
}

// funcao que vai realizar a leitura da lista e imprimir ela no terminal conforme formataçao pediuda [1 2 3]
void print_list(const LinkedList *l) {
    if (!l) {
        printf("Lista nao inicializada.\n");
        return;
    }
    // se for vazia imprime sem nenhum elemneto
    if (is_empty_list(l) == 1) {
        printf("[]\n");
        return;
    }
    printf("[");

    // mesmo esquema, verifica o tamanho da lista para iterar  sobre os nós dela
    int size = size_list(l);
    for (int i = 0; i < size; i++) {
        int value;
        if (get_node(l, i, &value) == 1) {
            printf("%d", value);
            if (i < size - 1) {
                printf(" ");
            }
        }
    }
    printf("]\n");
}

int main() {

    // cria as listas
    LinkedList *l1 = create_linked_list();
    LinkedList *l2 = create_linked_list();

    // se der erro na criacao da lista encerra o p[rograma]
    if (!l1 || !l2) {
        printf("Erro ao criar a lista.\n");
        return 1;
    }

    int run = 1;

    while (run) {
        int option;
        int buf;
        buf = scanf("%d", &option);
        (void)buf;
        switch(option) {
            case 1: {
                int pos, value;
                buf = scanf("%d %d", &value, &pos);
                int res = insert_node(l1, pos, value);
                (void)res;
                break;
            }
            case 2: {
                int pos, value;
                buf = scanf("%d %d", &value, &pos);

                int res = insert_node(l2, pos, value);
                (void)res;
                break;
            }
            case 3: {
                int pos, value;
                buf = scanf("%d %d", &value, &pos);

                int res = remove_node(l1, pos, &value);
                (void)res;
                break;
            }
            case 4: {
                int pos, value;

                buf = scanf("%d %d", &value, &pos);
                int res = remove_node(l2, pos, &value);
                (void)res;
                break;
            }

            case 5: {
                
                transfer_nodes(l2, l1);
                break;
            }
            case 6: {
                
                transfer_nodes(l1, l2);
                break;
            }
            case 7: {
                print_list(l1);
                break;

            }
            case 8: {
                print_list(l2);
                break;
            }
            case 9: {
                run = 0;
                break;
            }
           
            (void)buf;
        }
    }
}
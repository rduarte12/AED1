#include <stdlib.h>  // para permitir malloc
#include <stdio.h>
#include "LinkedList.h"

/*
 * Convenção de retorno das funções:
 	*  -1 erro de ponteiro
	*  0 posição inválida
	*  1 sucesso.
*/

// estrutura de nosso nó
// que guarda cada elemento da lista
typedef struct node {
	int data;
	struct node *next; // aponta p/ o próximo nó
} Node;

struct linked_list {
	Node *head; // aponta p/ o 1o nó
	int size; // num. de elementos na lista
};

// func. que cria a lista vazia
LinkedList *create_linked_list(void) {
	// aloca a lista
	LinkedList *l = malloc(sizeof(LinkedList));
	if (!l) {
		// falha ao alocar
		return NULL;
	}
	// se alocado, inicializa campos
	l->head = NULL; // lista vazia aponta p/ NULL
	l->size = 0; // nenhum elemento
	// sucesso, retorna ponteiro
	// p/ a lista
	return l;
}

// insere em qualquer pos
int insert_node(LinkedList *l, int pos, int value) {
	if (!l) {
		// lista não inicializada
		return -1;
	}
	// verifica-se a posição
	if ((pos < 0) || (pos > l->size)) {
		// posição inválida
		// pode retornar 0 ou -1
		// a depender da convenção
		return 0;
	}
	// cria novo nó
	Node *novo = malloc(sizeof(Node));
	if (!novo) {
		// erro ao alocar
		return -1;
	}
	// preenche os campos
	novo->data = value;
	novo->next = NULL; // ainda não sabemos o próximo
	// vamos conectar os ponteiros
	if (pos == 0) {
		// inserção na primeira posição
		// 1. novo aponta para o primeiro
		novo->next = l->head;
		// 2. head aponta para o novo
		l->head = novo;
	} else {
		// inserção em qualquer posição
		// temporário percorre a lista
		Node *tmp = l->head;
		for (int i = 0; i < pos-1; i++) {
			tmp = tmp->next;
		}
		// 1. novo aponta para o próximo de pos-1
		novo->next = tmp->next;
		// 2. anterior (pos-1) aponta para o novo
		tmp->next = novo;
	} 
	// incrementa o tamanho
	l->size++;
	// retorna sucesso
	return 1;
}

// remove em qualquer pos
int remove_node(LinkedList *l, int pos, int *value) {
	if (!l) {
		// lista não inicializada
		return -1;
	}
	// verifica-se a posição
	if ((pos < 0) || (pos >= l->size)) {
		// posição inválida
		// pode retornar 0 ou -1
		// a depender da convenção
		return 0;
	}
	// temporário para salvar removido
	Node *rem;
	// vamos remover
	if (pos == 0) {
		// para primeira posição:
		// 1. salva em rem
		rem = l->head;
		// 2. head avança
		l->head = l->head->next;	
	} else {
		// para qualquer posição:
		// temporário percorre a lista
		Node *tmp = l->head;
		for (int i = 0; i < pos-1; i++) {
			tmp = tmp->next;
		}
		// 1. salva o elemento a ser removido
		rem = tmp->next;
		// 2. anterior (pos-1) avança
		tmp->next = rem->next;
	}
	// se o usuário quer o valor
	if (value) {
		*value = rem->data;
	}
	// desaloca
	free(rem);
	// decrementa size
	l->size--;
	// retorna sucesso
	return 1;
}


// retorna elem. em qualquer pos
int get_node(const LinkedList *l, int pos, int *value) {
	if (!l) {
		// lista não inicializada
		return -1;
	}
	// verifica-se a posição
	if ((pos < 0) || (pos >= l->size)) {
		// posição inválida
		// pode retornar 0 ou -1
		// a depender da convenção
		return 0;
	}
	// temporário para salvar
	// o que será retornado
	Node *rem;
	// vamos percorrer
	if (pos == 0) {
		// para primeira posição:
		rem = l->head;
	} else {
		// para qualquer posição:
		// temporário percorre a lista
		Node *tmp = l->head;
		for (int i = 0; i < pos-1; i++) {
			tmp = tmp->next;
		}
		// salva o elemento 
		rem = tmp->next;
	}
	// se o usuário quer o valor
	if (value) {
		*value = rem->data;
	}
	// retorna sucesso
	return 1;
}

// verifica lista vazia
int is_empty_list(const LinkedList *l) {
	if (!l) {
		// lista não inicializada
		return -1;
	}
	if (l->head == NULL) {
		return 1; // vazia
	}
	return 0; // não vazia
	// OBS: poderia usar o qtd
}

// num. elementos da lista
int size_list(const LinkedList *l) {
	if (!l) {
		// lista não inicializada
		return -1;
	}
	return l->size;
}

// libera a lista
void free_linked_list(LinkedList **l) {
	if (!l || !(*l)) {
		// não inicializada
		// nada a fazer
		return;
	}
	// percorre a lista e libera nó por nó
	Node *tmp = (*l)->head;
	while (tmp != NULL) {
		Node *rem = tmp;
		tmp = tmp->next;
		free(rem);
	}
	// libera a cabeça
	free(*l);
	*l = NULL;
}


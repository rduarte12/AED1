#include "Queue.h"                // Interface do TAD Fila
#include <stdlib.h>               // malloc e free

#define MAX 100                   // Capacidade máxima da fila (tamanho do vetor fixo)

struct queue {
	int dados[MAX];               // Armazena os elementos
	int inicio;                   // Índice lógico do primeiro elemento
	int fim;                      // Índice da próxima posição livre para inserir
	int qtd;                      // Quantidade de elementos atualmente na fila
};

Queue* create_queue() {
	Queue *q = malloc(sizeof(Queue));   // Aloca a estrutura da fila
	if (!q) {
		return NULL;                // Falha na alocação
	}
	q->fim = 0;                         // Fim começa em 0
	q->inicio = 0;                      // Início começa em 0
	q->qtd = 0;                         // Fila vazia
	return q;                           // Retorna ponteiro válido
}

int is_empty(const Queue *q) {
	if (!q) {
		return -1;                      // Ponteiro inválido
	}
	if (q->qtd == 0) {
		return 1;                       // Verdadeiro para vazio
	} else {
		return 0;                       // Falso para vazio
	}
}

int is_full(const Queue *q) {
	if (!q) {
		return -1;                      // Ponteiro inválido
	}
	if (q->qtd == MAX) {
		return 1;                       // Verdadeiro para cheia
	} else {
		return 0;                       // Falso para cheia
	}
}

int size(const Queue *q) {
	if (!q) {
		return -1;                      // Ponteiro inválido
	}
	return q->qtd;                     	// Retorna número de elementos
}

int enqueue(Queue *q, int value) {
	if (!q) {
		return -1;                      // Ponteiro inválido
	}
	if (is_full(q)) {
		return 0;                       // Não inseriu porque está cheia
	} else {
		q->dados[q->fim] = value;       // Insere no índice fim
		q->fim++;                       // Avança o fim
		if (q->fim == MAX) {            // Tratamento circular
			q->fim = 0;             // Volta ao início do vetor
		}
		q->qtd++;                       // Incrementa quantidade
		return 1;                       // Sucesso
	}
}

int dequeue(Queue *q, int *value) {
	if ((!q) || (!value)) {
		return -1;                      // Ponteiro inválido
	}
	if (is_empty(q)) {
		return 0;                       // Não removeu porque está vazia
	} else {
		*value = q->dados[q->inicio];   // Lê o elemento do início
		q->inicio++;                    // Avança o início
		if (q->inicio == MAX) {         // Tratamento circular
			q->inicio = 0;          // Volta ao início do vetor
		}
		q->qtd--;                       // Decrementa quantidade
		return 1;                       // Sucesso
	}
}

int front(const Queue *q, int *value) {
	if ((!q) || (!value)) {
		return -1;                      // Ponteiro inválido
	}
	if (is_empty(q)) {
		return 0;                       // Não há elemento para consultar
	} else {
		*value = q->dados[q->inicio];   // Consulta o primeiro elemento
		return 1;                       // Sucesso
	}
}

void free_queue(Queue **q) {
	if (q) {                            	// Verifica ponteiro do ponteiro
		free(*q);                       // Libera a estrutura alocada
		*q = NULL;                      // Evita ponteiro pendente
	}
}

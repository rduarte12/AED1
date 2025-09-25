#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

#define STACK_TYPE int
#define MAX 100

struct Stack {
    STACK_TYPE *dados;
    int qtd;
    int topo;
};


// função feita para criar a pilha
Stack* create_stack(void) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s != NULL) {

        s -> dados = (STACK_TYPE *)malloc(MAX * sizeof(STACK_TYPE));
        if (s -> dados == NULL) {
            free(s);
            return NULL;
        }
        s -> qtd = MAX;
        s -> topo = 0;
        return s;


    } else {

        fprintf(stderr, "Memory allocation failed\n");

        return NULL;
    }

}
// função feita para verificar se a pilha está vazia
int is_empty(const Stack *s) {
    if (s == NULL) {
        return -1;
    } else if (s -> topo == 0) {
        return 1;
    } else {
        return 0;
    }
}

// função feita para verificar se a pilha está cheia
int is_full(const Stack *s) {
        if (s == NULL) {
        return -1;
    } else if (s -> topo == s -> qtd) {
        return 1;
    } else {
        return 0;
    }
}

// função feita para inserir um elemento na pilha
int push(Stack *s, int value) {
    // verifica se a pilha existe
    if (s == NULL) {
        return 0;
        
        // verifica se a pilha está cheia
        // se estiver cheia, realoca mais espaço para a pilha
        // e adicxiona no topo o valor

    } else if (is_full(s)) {

        s -> dados = (STACK_TYPE *)realloc(s -> dados, (s -> qtd + MAX) * sizeof(STACK_TYPE));

        if (s -> dados == NULL) {
            return 0;

        } else {
            s -> qtd += MAX;
            s -> dados[s -> topo] = value;
            s -> topo++;
        }
        return 1;

    } else {
        s -> dados[s -> topo] = value;
        s -> topo++;
        return 1;
    }

}

// função feita para remover um elemento da pilha
int pop(Stack *s, int *value) {

    // verifica se a pilha existe ou se está vazia
    if (s == NULL || is_empty(s)) {
        return 0;
    } else {

        // decrementa o topo e retorna o valor que estava no topo
        s -> topo--;
        *value = s -> dados[s -> topo];
        return 1;
    }
}

int peek(const Stack *s, int *value){

    if (s == NULL || is_empty(s)) {
        return 0;

    } else {
        *value = s -> dados[s -> topo - 1];
        return 1;
    }
}

void free_stack(Stack **s) {
    if (s != NULL && *s != NULL) {
        free((*s) -> dados);
        free(*s);
        *s = NULL;
    }
}


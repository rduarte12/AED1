#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Ponto.h"

// margem de erro para comparação de igualdade
#define EPS 0.00001


Ponto *criaPonto(float x, float y) {
    Ponto *p = malloc(sizeof(Ponto));
    if (!p) {
        printf("Não foi possível alocar o ponto\n");
        return NULL;
    }
    p->x = x;
    p->y = y;
    return p;
}

void liberaPonto(Ponto *p) {
    if (p != NULL) {
        free(p);
    }
}

void acessaPonto(Ponto *p, float* x, float* y) {
    if (p == NULL) {
        printf("Ponteiro inválido!!! Abortando...\n");
        return;
    }
    *x = p->x;
    *y = p->y;
}

void atribuiPonto(Ponto *p, float x, float y) {
    if (p == NULL) {
        printf("Ponteiro inválido!!! Abortando...\n");
        return;
    }
    p->x = x;
    p->y = y;
}

float distancia(Ponto *p1, Ponto *p2) {
    if ((p1 == NULL) || (p2 == NULL)) {
        printf("Ponteiros inválidos para a operação!! Abortando...\n");
        return -1;
    }
    float dst_x = p1->x - p2->x;
    float dst_y = p1->y - p2->y;
    float distancia = sqrt(dst_x*dst_x + dst_y*dst_y);
    return distancia;
}

float distanciaOrigem(Ponto *p) {
    if (p == NULL) {
        printf("Ponteiro inválido para a operação!! Abortando...\n");
        return -1;
    }
    return sqrt( (p->x * p->x) + (p->y* p->y) );
}

void imprimePonto(Ponto *p) {
    if (p == NULL) {
        printf("Ponteiro inválido para a operação!! Abortando...\n");
        return;
    }
    printf("(%.3f,%.3f)", p->x, p->y);
}

int pontosIguais(Ponto *p1, Ponto *p2) {
    // comparamos as coordenas em x
    float diff_x = p1->x - p2->x;
    // se a diferença é maior que a margem de erro, são diferentes
    if (fabs(diff_x) > EPS) {
        return 0; // 0 é False, são diferentes!
    }


    // comparamos as coordenas em y
    float diff_y = p1->y - p2->y;
    // se a diferença é maior que a margem de erro, são diferentes
    if (fabs(diff_y) > EPS) {
        return 0; // 0 é False, são diferentes!
    }

    // se chegamos até aqui, pontos são iguais dentro da margem de erro
    return 1; // 1 é True, são iguais!
}
/* Arquivo: Ponto.h */
#ifndef PONTO_H
#define PONTO_H

typedef struct {
	float x;
	float y;
} Ponto;

/* Protótipos das funções */
Ponto *criaPonto(float x, float y);
void liberaPonto(Ponto *p);
void acessaPonto(Ponto* p, float *x, float *y);
void atribuiPonto(Ponto *p, float x, float y);
float distancia(Ponto *p1, Ponto *p2);
float distanciaOrigem(Ponto *p);
void imprimePonto(Ponto *p);
int pontosIguais(Ponto *p1, Ponto *p2);

#endif
#include <stdlib.h>
#include <stdio.h>
#include "Ponto.h"

int main() {

    float x, y;

    scanf("%f %f", &x, &y);

    Ponto *p1 = criaPonto(x, y);

    scanf("%f %f", &x, &y);

    Ponto *p2 = criaPonto(x, y);

    int flag = 0;

    while(!flag) {
        int opt;
        scanf("%d", &opt);

        /*
        • 1: Imprimir P1 (formato: (x.xxx,y.yyy))
        • 2: Imprimir P2
        • 3: Distância entre P1 e P2
        • 4: Distância da origem até P1
        • 5: Distância da origem até P2
        • 6: Atribuir novas coordenadas a P1 (ler dois floats)
        • 7: Atribuir novas coordenadas a P2 (ler dois floats)
        • 8: Verificar se P1 e P2 são iguais (imprimir 1 se sim, 0 caso contrário)
        • 9: Encerrar o programa

        */

        switch(opt) {

            case 1:
                // imprimir p1
                imprimePonto(p1);
                printf("\n");
                break;

            case 2:
                // imprimir p2
                imprimePonto(p2);
                printf("\n");
                break;

            case 3:
                // distância entre &p1 e &p2
                printf("%.3f\n", distancia(p1, p2));
                break;

            case 4:
                // distancia da origem até p1
                printf("%.3f\n", distanciaOrigem(p1));
                break;

            case 5:
                // distancia da origem até p2
                printf("%.3f\n", distanciaOrigem(p2));
                break;

            case 6:
                // Atribuir novas coordenadas a P1
                scanf("%f %f", &x, &y);
                atribuiPonto(p1, x, y);
                break;

            case 7:
                // Atribuir novas coordenadas a P2
                scanf("%f %f", &x, &y);
                atribuiPonto(p2, x, y);
                break;

            case 8:
                // Verificar se P1 e P2 são iguais
                if (pontosIguais(p1, p2)) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
                break;

            case 9:
                // Encerrar o programa
                flag = 1;
                break;

        }

    }

    liberaPonto(p1);
    liberaPonto(p2);

    return 0;

}
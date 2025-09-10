#include <stdio.h>

void hanoi(int n, char origem, char destino, char aux){
    // caso base: apenas um disco, move direto para o destino
    if(n == 1) {
        printf("Mova o disco 1 de %c para %c\n", origem, destino);
    } else {
        // mover n-1 discos da origem para o auxiliar
        hanoi(n-1, origem, aux, destino);
        // mover o disco n da origem para o destino
        printf("Mova o disco %d de %c para %c\n", n, origem, destino);
        // mover os n-1 discos do auxiliar para o destino
        hanoi(n-1, aux, destino, origem);
    }

}

int main(){
    int n = 0;  // número de discos

    scanf("%d", &n);

    hanoi(n, 'A', 'C', 'B');  // A, B e C são os pinos
    return 0;
}
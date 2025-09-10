#include <stdio.h>
#include <stdlib.h>

/**Merge Sort
Subvetor com tamanho zero ou um já está ordenado. 
Portanto, só retornar.
 Caso recursivo (caso geral):
 Se o subvetor tem tamanho pelo menos dois, fazer o seguinte:
 1. Dividir vetor no meio.
 2. Chamar recursivamente para a metade esquerda e para a 
metade direita.
 3. Intercalar as duas metades ordenadas na etapa de merge.
**/

void merge(int *v, int l, int m, int r) {
    // calcula o tramanho das porções esquerda e direitas do vetor
    int left = m - l + 1;
    int right = r - m;

    // cria vetores temporários para armazenar estas porções
    int *L = (int *)malloc(left * sizeof(int));
    int *R = (int *)malloc(right * sizeof(int));


    int i, j, k;

    // copia os elemnetos para os vetores temporários
    for (int i = 0; i < left; i++) {
        L[i] = v[l + i];
    }
    for (int j = 0; j < right; j++) {
        R[j] = v[m + 1 + j];
    }

    // intercala os dois vetores temporários de volta no vetor original
    /**
    verifica se alcançamos o final do vetor da porção esquerda,
    se não chegamos ao final e, ou se já chegamos ao final da porção direita ou o elemento
    da porção esquerda é menor ou igual ao da porção direita, então indexamos o respectivo
    do vetor da esquerda (o menor) ao vetor original.
    Caso contrário, indexamos o elemento da porção direita.
    */
    for (i = 0, j = 0, k = l; k <= r; k++) {
        if (i < left && (j >= right || L[i] <= R[j])) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
    }

    printf("INTERCALACAO [%d,%d]:", l, r);
    for (int x = l; x <= r; x++) {
        printf(" %d", v[x]);
    }
    printf("\n");

    free(L);
    free(R);
}

void merge_sort(int *v, int l, int r) {

    //Caso base
    // QUando o segmento tem tamanho zero ou um, já está ordenado
    if(l >= r) return;

    printf("DIVISAO [%d,%d]\n", l, r);

    // calculo do ponto médio
    int m = l + (r - l) / 2;

    // Passo recursivo na parte esquerda
    merge_sort(v, l, m);
    // Passo recursivo na parte direita
    merge_sort(v, m + 1, r);
    // Intercalar as duas metades
    merge(v, l, m, r);
}

int main() {
    int n;
    scanf("%d", &n);
    int vec[n];
    for (int i = 0; i < n; i++) {
        int temp = 0;
        scanf("%d", &temp);
        vec[i] = temp;
    }

    merge_sort(vec, 0, n - 1);
}
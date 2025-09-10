#include <stdio.h>
#include <stdlib.h>


/*
    Código para o traba;ho de Algoritmos e Estruturas de Dados 1
    Ministrado por: Prof. Dr. Lucas Valem

    Autores:
        - Rafael Mendonça Duarte
        - Rodrigo de Jesus
        - Renan Blasques

*/

// Protótipos
int *createVector(int n);
int* invertVector(int *vector, int n);
void printVector(int *vector, int n);
void sequentialSearch(int *vector, int n);
void iterativeBinarySearch(int *vector, int n);
int rBinarySearch(int *vector,  int l, int r, int target);
void merge_sort(int *v, int l, int r);
void merge(int *v, int l, int m, int r);


/*
    Função principal responsável pelo menu interativo
    1. Inversão da ordem do vetor de entrada.
    2. Busca Sequencial no vetor de entrada.
    3. Busca Binária Iterativa no vetor de entrada.
    4. Busca Binária Recursiva no vetor de entrada.
    5. Encerrar o programa

    Input: Vetor de inteiros,  tamanho do vetor, operação a ser realizada.
    Output: Resultado da operação.


*/

int main() {

    int n, opt;
    scanf("%d", &n);

    int *vector = createVector(n);
    if (vector == NULL) {
        return -1;
    }
    int flag = 1;
    while (flag) {
        scanf("%d", &opt);
        switch (opt) {
            case 1: {
                int *inverted = invertVector(vector, n);

                if (inverted == NULL) {
                    free(vector);
                    return -1;
                }

                printVector(inverted, n);
                if (inverted != NULL) {
                    free(inverted);
                }
                break;
            }
            case 2:
                sequentialSearch(vector, n);
                break;
            case 3:
                iterativeBinarySearch(vector, n);
                break;
            case 4: {
                int target;
                scanf("%d", &target);
                int result = rBinarySearch(vector, 0, n - 1, target);
                if (result) {
                    printf("SIM\n");
                } else {
                    printf("NAO\n");
                }
                break;
            }
            case 5:
                flag = 0;
                break;
            default:
                flag = 0;
                break;
        }
    }

    free(vector);
    return 0;


}

/*
    Função responsável por inverter o vetor de entrada.
    Input: Vetor de inteiros, tamanho do vetor.
    Output: Vetor invertido.

    Parametros:
        vector: vetor de inteiros a ser invertido.
        n: tamanho do vetor.
        l: indice do primeiro elemento do vetor. (left)
        r: indice do ultimo elemento do vetor. (right)
        temp: variavel temporaria para auxiliar na troca dos elementos.

*/

int* invertVector(int *vector, int n) {
    if (n <= 0 || vector == NULL) return NULL;
    int *newVector = (int*)malloc(n * sizeof(int));
    if (newVector == NULL) return NULL;
    for (int i = 0; i < n; i++) {
        newVector[i] = vector[n - 1 - i];
    }
    return newVector;
}

/*
    Função responsável por realizar a busca sequencial no vetor de entrada.
    Input: Vetor de inteiros, tamanho do vetor, elemento a ser buscado.
    Output: "SIM" se o elemento for encontrado, "NAO" caso contrário.

    Parametros:
        vector: vetor de inteiros onde será realizada a busca.
        n: tamanho do vetor.
        target: elemento a ser buscado.

*/

void sequentialSearch(int *vector, int n) {
    int target;
    scanf("%d", &target);
    for (int i = 0; i < n; i++) {
        if (vector[i] == target) {
            printf("SIM\n");
            return;
        }
    }
    printf("NAO\n");
}

/*
    Função responsável por realizar a busca binária iterativa no vetor de entrada.
    Input: Vetor de inteiros, tamanho do vetor, elemento a ser buscado.
    Output: "SIM" se o elemento for encontrado, "NAO" caso contrário.

    Parametros:
        vector: vetor de inteiros onde será realizada a busca.
        n: tamanho do vetor.
        target: elemento a ser buscado.
        l: indice do primeiro elemento do vetor. (left)
        r: indice do ultimo elemento do vetor. (right)
        mid: indice do elemento do meio do vetor.

*/

void iterativeBinarySearch(int *vector, int n) {
    int target;
    int l = 0, r = n - 1;
    scanf("%d", &target);

    while (l <= r) {
        int mid = l + (r-l) / 2;
        if (vector[mid] == target) {
            printf("SIM\n");
            return;
        } else if (vector[mid] < target) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("NAO\n");
}

/*
    Função responsável por realizar a busca binária recursiva no vetor de entrada.
    Input: Vetor de inteiros, tamanho do vetor, elemento a ser buscado.
    Output: 1 se o elemento for encontrado, 0 caso contrário.

    Parametros:
        vector: vetor de inteiros onde será realizada a busca.
        l: indice do primeiro elemento do vetor. (left)
        r: indice do ultimo elemento do vetor. (right)
        target: elemento a ser buscado.
*/

int rBinarySearch(int *vector,  int l, int r, int target) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (vector[mid] == target) {
            return 1;
        } else if (vector[mid] > target) {
            return rBinarySearch(vector, l, mid - 1, target);
        } else {
            return rBinarySearch(vector, mid + 1, r, target);
        }
    }
    return 0;
}



/*
    Função responsável por imprimir o vetor.
    Input: Vetor de inteiros, tamanho do vetor.
    Output: Vetor impresso na tela.

    Parametros:
        vector: vetor de inteiros a ser impresso.
        n: tamanho do vetor.

*/

void printVector(int *vector, int n) {
    printf("%d", vector[0]);
    for (int i = 1; i < n; i++) {
        printf(" %d", vector[i]);
    }
    printf("\n");
}


/*
    Função responsável por criar um vetor de inteiros.
    Input: Tamanho do vetor.
    Output: Ponteiro para o vetor criado.

    Parametros:
        n: tamanho do vetor a ser criado.

*/


int *createVector(int n) {
    if (n <= 0) {
        return NULL;
    }
    int *vector = (int *)malloc(n * sizeof(int));
    if (vector == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &vector[i]);
    }
    return vector;
}

// Merge Sort não utilizado.
// Merge Sort foi implementado para realizar testes.

/*
    Função responsável por ordenar um vetor utilizando o algoritmo Merge Sort.
    Input: Vetor de inteiros, índices inicial e final do segmento a ser ordenado.
    Output: Vetor ordenado no segmento especificado.

    Parâmetros:
        v: vetor de inteiros a ser ordenado.
        l: índice do primeiro elemento do segmento (left).
        r: índice do último elemento do segmento (right).

    Descrição:
        - Caso base: se o segmento tem tamanho zero ou um, já está ordenado.
        - Caso recursivo: dividir o vetor ao meio, ordenar recursivamente as duas metades
          e intercalar as duas metades ordenadas na etapa de merge.
*/


/*
    Função auxiliar do Merge Sort responsável por intercalar dois subvetores ordenados.
    Input: Vetor de inteiros, índices inicial, médio e final do segmento a ser intercalado.
    Output: Segmento do vetor original ordenado.

    Parâmetros:
        v: vetor de inteiros a ser ordenado.
        l: índice do primeiro elemento do segmento (left).
        m: índice do elemento do meio do segmento (middle).
        r: índice do último elemento do segmento (right).

    Descrição:
        - Cria vetores temporários para as porções esquerda e direita.
        - Copia os elementos para os vetores temporários.
        - Intercala os dois vetores temporários de volta no vetor original.
*/
void merge(int *v, int l, int m, int r) {
    int left = m - l + 1;
    int right = r - m;
    int *L = (int *)malloc(left * sizeof(int));
    int *R = (int *)malloc(right * sizeof(int));
    int i, j, k;
    for (int i = 0; i < left; i++) {
        L[i] = v[l + i];
    }
    for (int j = 0; j < right; j++) {
        R[j] = v[m + 1 + j];
    }
    for (i = 0, j = 0, k = l; k <= r; k++) {
        if (i < left && (j >= right || L[i] <= R[j])) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
    }
    free(L);
    free(R);
}

void merge_sort(int *v, int l, int r) {

    //Caso base
    // QUando o segmento tem tamanho zero ou um, já está ordenado
    if(l >= r) return;

    //printf("DIVISAO [%d,%d]\n", l, r);

    // calculo do ponto médio
    int m = l + (r - l) / 2;

    // Passo recursivo na parte esquerda
    merge_sort(v, l, m);
    // Passo recursivo na parte direita
    merge_sort(v, m + 1, r);
    // Intercalar as duas metades
    merge(v, l, m, r);
}

#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

int tentarRemover(Queue *q1, Queue *q2, int *value) {
    if (dequeue(q1, value)) {
        return 1;
    } else if (dequeue(q2, value)) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    Queue *q1 = create_queue();
    Queue *q2 = create_queue();

    int run = 1;
    while (run) {
        int opt;
        // usei inteligencia artificial para tentar me ajudar a resolver um warning em relação ao scanf
        // Leitura mais robusta que não gera warning
        if (scanf("%d", &opt) != 1) {
            // Em caso de erro, continua o loop
            while (getchar() != '\n'); // Limpa buffer
            continue;
        }
        
        switch (opt) {

            case 0: {
                run = 0;
                break;
            }

            case 1: {
                int value;
                if (scanf("%d", &value) == 1) {
                    enqueue(q1, value);
                }
                break;
            }

            case 2: {
                int value;
                if (scanf("%d", &value) == 1) {
                    enqueue(q2, value);
                }
                break;
            }

            case 3: {
                int value;
                int verify = 1;
                while (verify) {
                    verify = tentarRemover(q2, q1, &value);
                    if (verify) {
                        printf("%d\n", value);
                    }

                    verify = tentarRemover(q2, q1, &value);
                    if (verify) {
                        printf("%d\n", value);
                    }

                    verify = tentarRemover(q1, q2, &value);
                    if (verify) {
                        printf("%d\n", value);
                    }
                }
                break;
            }
        }
    }
    
    // Libera memória
    free_queue(&q1);
    free_queue(&q2);
    
    return 0;
}
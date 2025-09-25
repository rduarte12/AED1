#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"


// exercico que transforma decimal para binario
int main () {
    
    Stack *s = create_stack();

    int num, binario = 0;

    scanf("%d", &num);

    while (num > 0) {
        int bit = num % 2;
        push(s, bit);
        num /= 2;
    }


    while (!is_empty(s)) {
        pop(s, &binario);
        printf("%d", binario);
    }
    printf("\n");

    free_stack(&s);
    return 0;
}

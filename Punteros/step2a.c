// Compilar: gcc step2a.c -o step2a
// Ejecutar: ./step2a

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    char* x = strdup("hola");
    int acc = 0;
    for(int i = 0; i < 1000; i++) {
        printf("%d: %p -> %c\n", i, &x[i], x[i]);
        acc ^= x[i];
    }
    printf("%d\n", acc);
}
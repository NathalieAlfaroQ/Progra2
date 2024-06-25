// Compilar gcc step2c.c -o step2c
// Ejecutar ./step2c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//const size_t BUFFER_SIZE = 1000*1000*100;
//const size_t BUFFER_SIZE = 1024*1024*512;
const size_t BUFFER_SIZE = 100;



void main() {
    uintptr_t x = 0;
    size_t total = 0;
    // Ajuste el número abajo para que el programa pida 1GB de memoria adicional
    // a la memoria física de la máquina.
    for (int i = 0; i < 1000; i++) {
        printf("%zu %d |", total, i);
        x ^= (uintptr_t)malloc(BUFFER_SIZE);
    }
    printf("\n%zu", x);
}
// Compilar: gcc step2b.c -o step2b
// Ejecutar: ./step2b

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char name[10];
    int age;
    int score;
};

void print_student(struct student* s) {
    printf("name: %s, age: %d, score: %d\n", s->name, s->age, s->score);
    s->age++;
    ((struct student*)s)->age = 5;
}

void main() {
    struct student* s1 = malloc(sizeof(struct student));
    strcpy(s1->name, "Maria");

    printf("Tamaño de *s1: %zu\n", sizeof(*s1));
    print_student(s1);
    free(s1);   
    s1->age = 20;
    s1->score = 100;
    print_student(s1);

    printf("Tamaño de s1: %zu\n", sizeof(s1));
    printf("Tamaño de int: %zu\n", sizeof(int));
    printf("Tamaño de char[10]: %zu\n", sizeof(char[10]));
    printf("%p\n", s1);
}


// Compilar: gcc step1c.c -o step1c
// Ejecutar: ./step1c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char name[10];
    int age;
    int score;
};

// void call_wrapper(void (*f)(const struct student*), const struct student* s)
void call_wrapper(void (f)(const struct student*), const struct student* s) {
    printf("antes\n");
    f(s);
    printf("despues\n");
}

void print_student(const struct student* s) {
    printf("name: %s, age: %d, score: %d\n", s->name, s->age, s->score);
    ((struct student*)s)->age = 5;
}

void main() {
    struct student* s1 = malloc(sizeof(struct student));
    struct student s2 = {"Ana", 25, 100};

    s1->age = 20;
    s1->score = 100;
    strcpy((*s1).name, "Maria");
    printf("Tamaño de s1: %zu\n", sizeof(s1));

    printf("Tamaño de *s1: %zu\n", sizeof(*s1));

    print_student(s1);
    print_student(s1);
    print_student(&s2);
    printf("Tamaño de int: %zu\n", sizeof(int));
    printf("Tamaño de char[10]: %zu\n", sizeof(char[10]));

    call_wrapper(&print_student, s1);
    // call_wrapper(print_student, s1);

    free(s1);
}
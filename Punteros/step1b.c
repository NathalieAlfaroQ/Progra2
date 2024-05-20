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
    s1->age = 20;
    s1->score = 100;
    strcpy(s1->name, "Maria");

    printf("Tamaño de *s1: %zu\n", sizeof(*s1));
    print_student(s1);
    print_student(s1);

    printf("Tamaño de s1: %zu\n", sizeof(s1));
    printf("Tamaño de int: %zu\n", sizeof(int));
    printf("Tamaño de char[10]: %zu\n", sizeof(char[10]));
//liberar memoria, devolver memoria es de quien exactamente cree con malloc
    free(s1);
}

/*HEAP SUMMARY:
==9991==     in use at exit: 20 bytes in 1 blocks
==9991==   total heap usage: 2 allocs, 1 frees, 1,044 bytes allocated
==9991== 
==9991== LEAK SUMMARY:
==9991==    definitely lost: 20 bytes in 1 blocks
==9991==    indirectly lost: 0 bytes in 0 blocks
==9991==      possibly lost: 0 bytes in 0 blocks
==9991==    still reachable: 0 bytes in 0 blocks
==9991==         suppressed: 0 bytes in 0 blocks
==9991== Rerun with --leak-check=full to see details of leaked memory
==9991== 
==9991== For lists of detected and suppressed errors, rerun with: -s
==9991== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)*/

/* HEAP SUMMARY:
==11489==     in use at exit: 0 bytes in 0 blocks
==11489==   total heap usage: 2 allocs, 2 frees, 1,044 bytes allocated
==11489== 
==11489== All heap blocks were freed -- no leaks are possible
==11489== 
==11489== For lists of detected and suppressed errors, rerun with: -s
==11489== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)*/
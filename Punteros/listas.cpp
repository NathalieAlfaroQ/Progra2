class Node
{
public:
    int value;
    Node *next;

    // Constructor
    Node(int valor)
    {
        value = valor;
        next = nullptr;
    }
};

class List
{
public:
    Node node;
    Node head;

    // Constructor
    /* Nodo actual = cabeza;
            while (actual.siguiente != null) {
                actual = actual.siguiente;
            }
            actual.siguiente = nodoNuevo;*/

    /*Haga una funcion que recibe 2 listas ordenadas que las une y ordena.
    Input: 1-3-7
    Input: 1-2-3
    Output: 1-1-2-3-7
    */
    List mergedList(List list1, List list2)
    {
        Node actual1 = list1.head;
        Node actual2 = list2.head;
        if (actual1 == nullptr)
        {
            actual1 = actual2;
        }
        while (actual1.next != nullptr)
        {
            actual1 = actual1.next;
        }
        actual1.next = nodeNew;
        return listNew;
    }
};

int main()
{
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char name[10];
    int age;
    int score;
};

void print_student(const struct student* s) {
    printf("name: %s, age: %d, score: %d\n", s->name, s->age, s->score);
    ((struct student*)s)->age = 5;
}

void call_wrapper(void (f)(const struct student*), const struct student* s) {
    printf("antes\n");
    f(s);
    printf("despues\n");
}

void main() {
    struct student* s1 = malloc(sizeof(struct student));
    s1->age = 20;
    s1->score = 100;
    strcpy(s1->name, "Maria");
    struct student s2 = {"Ana", 25, 100};

    printf("Tamaño de *s1: %zu\n", sizeof(*s1));
    print_student(s1);
    print_student(s1);

    printf("Tamaño de s1: %zu\n", sizeof(s1));
    printf("Tamaño de int: %zu\n", sizeof(int));
    printf("Tamaño de char[10]: %zu\n", sizeof(char[10]));

    print_student(&s2); //variable normal a puntero 
    //correr con valgrind

    call_wrapper(&print_student, s1);
    free(s1);
}


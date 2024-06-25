Universidad de Costa Rica
Escuela de Ciencias de la Computación e Informática
Programación 2 - CI0113
Prof. Esteban Rodríguez Betancourt

# Práctica 1
Nombre:
Carnet:

En esta práctica se verá el manejo de memoria en C y C++, además de algunos
errores comunes. También se utilizarán herramientas como Valgrind para detectar
algunos errores en el uso de la memoria y `strace` para ver las llamadas al sistema. Para esta práctica es necesario el uso de Linux y GCC.

Al final suban a mediación este documento con sus respuestas (pongan R/ cómo prefijo de sus respuestas). adjunten también los archivos '*.c' creados.


# Step 1: malloc y free
En C la memoria se pide generalmente con las funciones `malloc` y `free`. Sin
embargo, no son las únicas funciones disponibles para ello. `calloc` se puede
usar para pedir memoria inicializada en cero, `strdup` puede duplicar strings
(secuencias de caracteres terminadas con un caracter nulo), etc.

Para iniciar vamos a hacer un programa simple que pide memoria:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char name[10];
    int age;
    int score;
};

void print_student(struct student s) {
    printf("name: %s, age: %d, score: %d\n", s.name, s.age, s.score);
}

void main() {
    struct student s1;
    s1.age = 20;
    s1.score = 100;
    strcpy(s1.name, "Maria");

    print_student(s1);
}
```

Compile el programa usando `gcc step1.c -o step1` y ejecútelo. ¿Qué imprime?

R/ name: Maria, age: 20, score: 100

## Respondan

1. ¿En dónde se inicializa la variable `s1`? ¿Stack o heap?

R/ En el main, Stack.

2. ¿Cómo creen que se pasa la variable `s1` a la función `print_student`? ¿Por
valor o por referencia/puntero?

R/ Por valor.

3. ¿De qué tamaño creen que es la variable `s1` en bytes?

R/ 20.

En la función `main` añadan la siguiente línea, para averiguar el tamaño de
la variable `s1`:

```c
    printf("Tamaño de s1: %zu\n", sizeof(s1));
```

Compilen el archivo y córranlo. ¿Acertaron el tamaño del `struct student`?
¿Es más o menos de lo que estimaron?

R/ En efecto.
name: Maria, age: 20, score: 100
Tamaño de s1: 20

Es muy posible que estimaran mal el tamaño del struct. ¿Qué tal si averiguamos
el tamaño de otros tipos de datos en C? Añadan las siguientes líneas, compilen
el programa, córranlo y reporten los resultados.

```c
    printf("Tamaño de int: %zu\n", sizeof(int));
    printf("Tamaño de char[10]: %zu\n", sizeof(char[10]));
```

Reporten: ¿Es `sizeof(struct student) == sizeof(int) + sizeof(int) + sizeof(char[10])`?
¿Cuanta es la diferencia?

R/ 20 == 4 + 4 + 10
20 == 18
Diferencia de 2
name: Maria, age: 20, score: 100
Tamaño de s1: 20
Tamaño de int: 4
Tamaño de char[10]: 10

Añadan otro array de tipo `char` y tamaño 1 al `struct student`. Compilen y
corra el programa. 

¿El tamaño del struct cambió o siguió igual? 

R/ Cambió
name: Maria, age: 20, score: 100
Tamaño de s1: 24
Tamaño de int: 4
Tamaño de char[10]: 10

Sigan incrementando el tamaño de dicho array hasta que tenga tamaño 5. ¿Qué cambios observaron?

2:
name: Maria, age: 20, score: 100
Tamaño de s1: 24
Tamaño de int: 4
Tamaño de char[10]: 10

3:
name: Maria, age: 20, score: 100
Tamaño de s1: 24
Tamaño de int: 4
Tamaño de char[10]: 10

4:
name: Maria, age: 20, score: 100
Tamaño de s1: 24
Tamaño de int: 4
Tamaño de char[10]: 10

5:
name: Maria, age: 20, score: 100
Tamaño de s1: 28
Tamaño de int: 4
Tamaño de char[10]: 10

R/ En un arreglo de tamaño 1 al 4, sigue igual, en 24, pero en tamaño 5 cambió a 28.

Dependiendo de su compilador, sistema operativo y opciones de compilación es
posible que obtengan resultados diferentes. Esto es normal, ¿pero porqué?

Aunque la memoria es byte-direccionable, el procesador en realidad no pide los
datos a la memoria byte por byte, sino que pide más (imaginen ir de compras al
supermercado por una cosa y volver a la casa, luego ir por otra y volver. No: uno
va una vez y compra todo lo que puede). Históricamente, la memoria en realidad
se pedía por words (_word_ es el tamaño de los datos nativos de la arquitectura):
ejm 16 bits o 32 bits. Por lo tanto, para el procesador es más eficiente pedir
memoria que esté alineada con un _word_. Por este motivo, algunos compiladores
agregan _padding_ entre los elementos de un struct: para que estén alineados. Incluso
a veces pueden reordenar los miembros del struct.

Si desean aprender más de este tema pueden ver los siguientes artículos:
- https://en.wikipedia.org/wiki/Data_structure_alignment
- https://en.wikipedia.org/wiki/Word_(computer_architecture)

Eliminen ese array extra que agregaron y guarden el archivo `step1.c`. Se va a usar luego.

## Step 1a: punteros
Pasar parámetros por valor tiene sus ventajas: no se modifica el original. Sin
embargo, para objetos muy grandes esto es problemático, ya que se deben hacer
copias.

En general, uno quiere pasar los parámetros por puntero/referencia cuando:

- Desea poder modificar la variable original
- El objeto es muy grande y desea evitar hacer copias, ya que esto es costoso (lento)
- Desea reducir el uso de memoria teniendo una única instancia

Hacer copias no necesariamente es algo costoso: los punteros en un
sistema de 64 bits miden 8 bytes. Los procesadores actuales pueden copiar hasta
64 bytes tan rápido como pueden copiar un puntero.

Las ventajas de pasar los parámetros por valor pueden ser las siguientes:

- No se modifica el valor original
- Posiblemente se facilita la gestión de la memoria

En este caso deseamos añadir punteros... porque es una práctica de punteros.

Copien el archivo `step1.c` a `step1a.c` (los vamos a usar luego).

Para pedir memoria dinámica vamos a usar `malloc`. Para esto debemos modificar
la declaración de `s1`, para que se lea así:

```c
    struct student* s1 = malloc(sizeof(struct student));
```

Intenten compilar el programa. ¿Qué error les da?

R/ El error esta en que s1 se crea como puntero, pero al usarlo, no se hace como puntero, entonces no compila por no poseer la sintaxis correcta.

In function ‘main’:
step1a.c:21:7: error: ‘s1’ is a pointer; did you mean to use ‘->’?
   21 |     s1.age = 20;
      |       ^
      |       ->
step1a.c:22:7: error: ‘s1’ is a pointer; did you mean to use ‘->’?
   22 |     s1.score = 100;
      |       ^
      |       ->
step1a.c:23:14: error: ‘s1’ is a pointer; did you mean to use ‘->’?
   23 |     strcpy(s1.name, "Maria");
      |              ^
      |              ->
step1a.c:28:19: error: incompatible type for argument 1 of ‘print_student’
   28 |     print_student(s1);
      |                   ^~
      |                   |
      |                   struct student *
step1a.c:14:35: note: expected ‘struct student’ but argument is of type ‘struct student *’
   14 | void print_student(struct student s) {

El motivo del error es que están intentando acceder a un miembro de un puntero.
Los punteros son direcciones de memoria, no tienen miembros. Para resolver el
problema debemos desreferenciar el puntero. Es decir, en lugar de hacer
`(puntero).xyz` queremos hacer `(struct).xyz`. Para desreferenciar un puntero
usamos el operador `*`. Para no confundir con la multiplicación es una buena
práctica usar paréntesis. Modifiquen el código para que se lea así:

```c
    struct student* s1 = malloc(sizeof(struct student));
    (*s1).age = 20;
    (*s1).score = 100;
    strcpy((*s1).name, "Maria");
    printf("Tamaño de s1: %zu\n", sizeof(s1));
    print_student(*s1);
```

Si `s1` ahora es un puntero entonces podemos obtener "leer" el struct al que apunta
usando el operador de desreferencia `*`. Una vez que ya estamos en el struct podemos
acceder a sus miembros, usando el punto "`.`".

Compilen de nuevo el programa y córranlo. Reporten:
- ¿Qué tamaño tiene ahora s1?

R/
Tamaño de s1: 8
Tamaño de int: 4
Tamaño de char[10]: 10

- ¿Qué tamaño tenía en `step1`?

R/ 20.

- ¿s1 se está pasando a print_student por valor o por puntero?

R/ Por valor.

Averiguen el tamaño de `*s1`. Añadan `printf("Tamaño de *s1: %zu\n", sizeof(*s1));`,
compilen y ejecuten el programa. ¿Qué tamaño tiene `*s1`?

R/ 20.
Tamaño de s1: 8
Tamaño de *s1: 20
Tamaño de int: 4
Tamaño de char[10]: 10

Modifiquen `print_student` para que modifique la edad después de imprimir los datos.
Llamen a `print_student` otra vez. ¿Se imprimió lo mismo o algo diferente? ¿Porqué?

R/ Se imprimió lo mismo porque se modifica la dirección, no el valor.
Tamaño de s1: 8
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: Maria, age: 20, score: 100
Tamaño de int: 4
Tamaño de char[10]: 10

## Step 1b: paso de parámetros por puntero
Ya vimos que podemos pasar parámetros por valor. Ahora queremos pasar los parámetros
por puntero. Para esto vamos a copiar el archivo `step1a.c` a `step1b.c`.

En primer lugar, es muy molesto estar escribiendo `(*s1).xyz` cada vez que queramos
acceder a un miembro de `s1`. Por ejemplo, en otros lenguajes (como Java) uno
simplemente usa un punto. En C y C++ tenemos una opción más corta y es usar el operador
"arrow" (`->`). Modifiquen `step1b.c` para que se use el operador `->` en lugar
del de desreferencia. Compilen y corran el programa para validar que sigue funcionando.

Tamaño de s1: 8
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: Maria, age: 20, score: 100
Tamaño de int: 4
Tamaño de char[10]: 10

Ahora, modifiquen la función `print_student` para que reciba un `struct student*`
en lugar de un `struct student`.

(El párrafo anterior se lee "... un puntero a struct student en lugar de un struct student")

Para ello modifiquen la firma de la función, de forma que reciba un puntero a un struct
student. Compilen el programa y anoten los mensajes de error. Corrijan los errores que indica el
compilador y logren que el programa funcione correctamente.

R/  In function ‘print_student’:
step1b.c:15:47: error: ‘s’ is a pointer; did you mean to use ‘->’?
Hay error porque son punteros y no se utiliza su sintaxis.

Se corrije:
Tamaño de s1: 8
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: Maria, age: 21, score: 100
Tamaño de int: 4
Tamaño de char[10]: 10

¿Recuerdan que se modificó `print_student` para que cambiara la edad? ¿La segunda vez que se llama
a `print_student` muestra los mismos datos que la primera vez? ¿Porqué?

R/ Si, la firma para recibir un untero y trabajarlos como tal.
No da los mismos resultados, porque ahora s se puede accerder para modificarla.


A veces uno desea modificar los valores pasados como parámetros. A veces uno no desea poder hacerlo,
pero requiere las ventajas de rendimiento de pasar los datos por puntero. ¿Cómo se puede resolver?
En C y C++ es posible declarar algo como constante. Cambien la firma de `print_student` para que sea
`void print_student(const struct student* s)`. Compilen y anoten los errores. Luego eliminen la
instrucción problemática y vuelvan a ejecutar el programa.

R/
 In function ‘print_student’:
step1b.c:17:11: error: increment of member ‘age’ in read-only object
   17 |     s->age++;

Tamaño de s1: 8
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: Maria, age: 20, score: 100
Tamaño de int: 4
Tamaño de char[10]: 10

El uso de const es muy recomendado para APIs donde se desea garantizar que no se va a modificar
la variable. También es posible devolver tipos const, para que el usuario no pueda modificarlos.
Por supuesto, esto es algo para evitar errores simples: alguien podría simplemente hacer un
casting del tipo (convertirlo) y con eso se quita la protección provista por el const. Por ejemplo,
añadan a `print_student` la línea `((struct student*)s)->age = 5;` y corran el programa de nuevo.
¿El compilador reporta algún error? ¿Qué imprime el programa?

R/ No hay errores.
Tamaño de s1: 8
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: Maria, age: 5, score: 100
Tamaño de int: 4
Tamaño de char[10]: 10

## Step 1c: Desreferencia
La función `malloc` nos devuelve punteros. ¿Pero cómo obtenemos el puntero a algo? Con el
operador de "address of" `&` (no confundir con el and lógico o and de operaciones de bits).

Copien `step1b.c`a `step1c.c`. En este otro archivo vamos a crear varios estudiantes. Pero en lugar
de pedir la memoria con malloc vamos a usar la memoria de la pila:

```c
struct student s2 = {"Ana", 25, 100};
```

Ahora, modifiquen el programa para que también imprima los datos de Ana. En primer lugar, intenten
llamar a la función `print_student(s2);`. Compilen e indiquen qué error mostró el compilador.
Luego resuelvanlo para que el programa funcione apropiadamente.

R/
In function ‘main’:
step1c.c:32:19: error: incompatible type for argument 1 of ‘print_student’
   32 |     print_student(s2);
      |                   ^~
      |                   |
      |                   struct student
step1c.c:14:42: note: expected ‘const struct student *’ but argument is of type ‘struct student’
   14 | void print_student(const struct student* s)

Funciona:     print_student(&s2);

Tamaño de s1: 8
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: Maria, age: 5, score: 100
name: Ana, age: 25, score: 100
Tamaño de int: 4
Tamaño de char[10]: 10

Noten que el operador "address of" puede obtener la dirección de lo que sea. Por ejemplo,
creen esta función:

```c
void call_wrapper(void (f)(const struct student*), const struct student* s) {
    printf("antes\n");
    f(s);
    printf("despues\n");
}
```

Y la pueden llamar usando `call_wrapper(&print_student, s1);`. Alternativamente,
podrían usar una firma de función `void call_wrapper(void (*f)(const struct student*), const struct student* s)`
y llamarla usando `call_wrapper(print_student, s1);`.

Tamaño de s1: 8
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: Maria, age: 5, score: 100
name: Ana, age: 25, score: 100
Tamaño de int: 4
Tamaño de char[10]: 10
antes
name: Maria, age: 5, score: 100
despues


# Step 2: memoria y fugas
En este paso vamos ver qué pasa si hacemos operaciones inapropiadas con la memoria. Se usará
la herramienta Valgrind para detectar fugas, strace para ver las llamadas al sistema y vamos
a conocer el segmentation fault, un error típico al manejar mal la memoria.

Para comenzar vamos a usar Valgrind para detectar fugas de memoria. Ejecuten el programa `step1b`
bajo valgrind, usando:

```
    valgrind ./step1b
```

Reporten el resultado que les da Valgrind. Noten las recomendaciones que da el programa. Ejecuten
Valgrind usando los flags recomendados.

==356812== Memcheck, a memory error detector
==356812== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==356812== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==356812== Command: ./step1b
==356812== 
Tamaño de s1: 8
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: Maria, age: 5, score: 100
Tamaño de int: 4
Tamaño de char[10]: 10
==356812== 
==356812== HEAP SUMMARY:
==356812==     in use at exit: 20 bytes in 1 blocks
==356812==   total heap usage: 2 allocs, 1 frees, 1,044 bytes allocated
==356812== 
==356812== LEAK SUMMARY:
==356812==    definitely lost: 20 bytes in 1 blocks
==356812==    indirectly lost: 0 bytes in 0 blocks
==356812==      possibly lost: 0 bytes in 0 blocks
==356812==    still reachable: 0 bytes in 0 blocks
==356812==         suppressed: 0 bytes in 0 blocks
==356812== Rerun with --leak-check=full to see details of leaked memory
==356812== 
==356812== For lists of detected and suppressed errors, rerun with: -s
==356812== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Valgrind es una herramienta que es capaz de detectar fugas de memoria. Por ejemplo, en step1b
"se nos olvidó" liberar la memoria. Noten que Valgrind reporta que los bytes perdidos son "still reachable".
Eso quiere decir que existe en la memoria del programa un puntero que apunta a la memoria que perdimos.
Ejemplos típicos de esto suceden cuando se nos olvida liberar la memoria de una estructura de datos compleja.

Aún no vamos a solucionar la fuga de memoria. Primero copien `step1b.c` a `step2.c`. Luego agreguen los `free`
al final del programa en `step1b.c` y `step1c.c`. Compilen los programas y vuelvanlos a correr bajo Valgrind,
para confirmar que ya no tienen fugas de memoria.

step2
valgrind ./step2
==357834== Memcheck, a memory error detector
==357834== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==357834== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==357834== Command: ./step2
==357834== 
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: Maria, age: 5, score: 100
Tamaño de s1: 8
Tamaño de int: 4
Tamaño de char[10]: 10
(nil)
==357834== 
==357834== HEAP SUMMARY:
==357834==     in use at exit: 20 bytes in 1 blocks
==357834==   total heap usage: 2 allocs, 1 frees, 1,044 bytes allocated
==357834== 
==357834== LEAK SUMMARY:
==357834==    definitely lost: 20 bytes in 1 blocks
==357834==    indirectly lost: 0 bytes in 0 blocks
==357834==      possibly lost: 0 bytes in 0 blocks
==357834==    still reachable: 0 bytes in 0 blocks
==357834==         suppressed: 0 bytes in 0 blocks
==357834== Rerun with --leak-check=full to see details of leaked memory
==357834== 
==357834== For lists of detected and suppressed errors, rerun with: -s
==357834== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

step1b
==358202== Memcheck, a memory error detector
==358202== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==358202== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==358202== Command: ./step1b
==358202== 
Tamaño de s1: 8
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: Maria, age: 5, score: 100
Tamaño de int: 4
Tamaño de char[10]: 10
==358202== 
==358202== HEAP SUMMARY:
==358202==     in use at exit: 0 bytes in 0 blocks
==358202==   total heap usage: 2 allocs, 2 frees, 1,044 bytes allocated
==358202== 
==358202== All heap blocks were freed -- no leaks are possible
==358202== 
==358202== For lists of detected and suppressed errors, rerun with: -s
==358202== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

step1c
==358596== Memcheck, a memory error detector
==358596== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==358596== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==358596== Command: ./step1c
==358596== 
Tamaño de s1: 8
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: Maria, age: 5, score: 100
name: Ana, age: 25, score: 100
Tamaño de int: 4
Tamaño de char[10]: 10
antes
name: Maria, age: 5, score: 100
despues
==358596== 
==358596== HEAP SUMMARY:
==358596==     in use at exit: 0 bytes in 0 blocks
==358596==   total heap usage: 2 allocs, 2 frees, 1,044 bytes allocated
==358596== 
==358596== All heap blocks were freed -- no leaks are possible
==358596== 
==358596== For lists of detected and suppressed errors, rerun with: -s
==358596== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

En `step2.c` en lugar de agregar la función `free` al final del programa vamos a hacer cosas no válidas
y ver qué sucede. Al final del programa agreguen `s1 = NULL;`. Compilen el programa y córranlo sin Valgrind.
Luego córranlo con Valgrind. ¿Cambió el error reportado por Valgrind? ¿Porqué no?

Sin Valgrind:
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: Maria, age: 21, score: 100
Tamaño de s1: 8
Tamaño de int: 4
Tamaño de char[10]: 10
0x5635b843c2a0

Con Valgrind:
==359565== Memcheck, a memory error detector
==359565== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==359565== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==359565== Command: ./step2
==359565== 
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: Maria, age: 21, score: 100
Tamaño de s1: 8
Tamaño de int: 4
Tamaño de char[10]: 10
0x4a8f040
==359565== 
==359565== HEAP SUMMARY:
==359565==     in use at exit: 20 bytes in 1 blocks
==359565==   total heap usage: 2 allocs, 1 frees, 1,044 bytes allocated
==359565== 
==359565== LEAK SUMMARY:
==359565==    definitely lost: 20 bytes in 1 blocks
==359565==    indirectly lost: 0 bytes in 0 blocks
==359565==      possibly lost: 0 bytes in 0 blocks
==359565==    still reachable: 0 bytes in 0 blocks
==359565==         suppressed: 0 bytes in 0 blocks
==359565== Rerun with --leak-check=full to see details of leaked memory
==359565== 
==359565== For lists of detected and suppressed errors, rerun with: -s
==359565== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

No hay errores

Es posible que Valgrind indique que nuestra fuga de memoria sea "still reachable". ¿Valgrind no sirve? No, no
es por eso. La respuesta es que el compilador optimiza nuestro programa. Como nadie lee `s1`
el compilador puede decidir eliminar esa instrucción (tengan cuidado cuando están haciendo benchmarks.
A veces parece que algo es más rápido, pero el compilador simplemente borró el código).
Para obligarlo a generar código necesitamos usar el valor de `s1` después de asignarlo. Agreguen al final
del programa `printf("%p\n", s1);` y vuelvanlo a ejecutar sobre Valgrind. Ahora sí, la memoria está
definitivamente perdida.

==360116== Memcheck, a memory error detector
==360116== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==360116== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==360116== Command: ./step2
==360116== 
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: Maria, age: 5, score: 100
Tamaño de s1: 8
Tamaño de int: 4
Tamaño de char[10]: 10
0x4a8f040
(nil)
==360116== 
==360116== HEAP SUMMARY:
==360116==     in use at exit: 20 bytes in 1 blocks
==360116==   total heap usage: 2 allocs, 1 frees, 1,044 bytes allocated
==360116== 
==360116== LEAK SUMMARY:
==360116==    definitely lost: 20 bytes in 1 blocks
==360116==    indirectly lost: 0 bytes in 0 blocks
==360116==      possibly lost: 0 bytes in 0 blocks
==360116==    still reachable: 0 bytes in 0 blocks
==360116==         suppressed: 0 bytes in 0 blocks
==360116== Rerun with --leak-check=full to see details of leaked memory
==360116== 
==360116== For lists of detected and suppressed errors, rerun with: -s
==360116== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

## Segmentation fault
En `step2.c`, muevan la línea `s1 = NULL` para que esté entre los dos `print_student`. Corran el programa
tanto sin Valgrind como con Valgrind y reporten los resultados.

Sin Valgrind:
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
Segmentation fault

Con Valgrind:
==360313== Memcheck, a memory error detector
==360313== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==360313== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==360313== Command: ./step2
==360313== 
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
==360313== Invalid read of size 4
==360313==    at 0x10917D: print_student (in /home/alfanath/Progra2/Punteros/step2)
==360313==    by 0x109239: main (in /home/alfanath/Progra2/Punteros/step2)
==360313==  Address 0x10 is not stack'd, malloc'd or (recently) free'd
==360313== 
==360313== 
==360313== Process terminating with default action of signal 11 (SIGSEGV)
==360313==  Access not within mapped region at address 0x10
==360313==    at 0x10917D: print_student (in /home/alfanath/Progra2/Punteros/step2)
==360313==    by 0x109239: main (in /home/alfanath/Progra2/Punteros/step2)
==360313==  If you believe this happened as a result of a stack
==360313==  overflow in your program's main thread (unlikely but
==360313==  possible), you can try to increase the size of the
==360313==  main thread stack using the --main-stacksize= flag.
==360313==  The main thread stack size used in this run was 8388608.
==360313== 
==360313== HEAP SUMMARY:
==360313==     in use at exit: 1,044 bytes in 2 blocks
==360313==   total heap usage: 2 allocs, 0 frees, 1,044 bytes allocated
==360313== 
==360313== LEAK SUMMARY:
==360313==    definitely lost: 20 bytes in 1 blocks
==360313==    indirectly lost: 0 bytes in 0 blocks
==360313==      possibly lost: 0 bytes in 0 blocks
==360313==    still reachable: 1,024 bytes in 1 blocks
==360313==         suppressed: 0 bytes in 0 blocks
==360313== Rerun with --leak-check=full to see details of leaked memory
==360313== 
==360313== For lists of detected and suppressed errors, rerun with: -s
==360313== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
Segmentation fault

Acceder a posiciones de memoria inválida produce lo que se conoce como _segmentation fault_. Esto no sucede
solamente cuando accedemos a un puntero nulo, sino cuando accedemos a cualquier posición de memoria que no
le pertenece al programa.

Por ejemplo, creen el archivo `step2a.c` y escriban lo siguiente:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    char* x = strdup("hola");
    int acc = 0;
    for(int i = 0; i < 32; i++) {
        printf("%d: %p -> %c\n", i, &x[i], x[i]);
        acc ^= x[i];
    }
    printf("%d\n", acc);
}
```

Compilen y ejecuten ese programa varias veces. Noten por ejemplo, que el resultado del
final del programa (hacer XOR de cada caracter leído) es diferente. Esto es porque la memoria
no necesariamente es limpiada antes de la ejecución de un programa. En C y C++ por esto
es importantísimo siempre inicializar la memoria.

Incrementen el 32 por un número alto. ¿En qué dirección les da el segmentation fault? (quiten el
salto de línea para evitar que tengan muchas líneas en la terminal)

Vean que en este caso el segmentation fault ocurrió solamente con leer de la memoria, también puede
ocurrir con escribir o intentar ejecutar de un segmento no ejecutable.

No da segmentation fault y eso que lo hice con 100.

## Use after free
¿Qué sucede si intentamos usar la memoria después de liberarla? Copien `step2.c` a `step2b.c` y averiguémoslo.

Modifiquen `step2b.c` y pongan `free(s1)` entre los dos `print_student` y quiten el `s1 = NULL;`. Corran el programa
sin valgrind y con valgrind. Comenten qué observan al ejecutar el programa varias veces.

Muchos errores, la edad cambia por numeros no usuales

Sin:
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
name: 
      �L], age: -664020895, score: 100
Tamaño de s1: 8
Tamaño de int: 4
Tamaño de char[10]: 10
0x55d4cd30c2a0

Con:
==362398== Memcheck, a memory error detector
==362398== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==362398== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==362398== Command: ./step2b
==362398== 
Tamaño de *s1: 20
name: Maria, age: 20, score: 100
==362398== Invalid read of size 4
==362398==    at 0x10919D: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==362398==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Address 0x4a8f050 is 16 bytes inside a block of size 20 free'd
==362398==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x109251: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Block was alloc'd at
==362398==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398== 
==362398== Invalid read of size 4
==362398==    at 0x1091A4: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==362398==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Address 0x4a8f04c is 12 bytes inside a block of size 20 free'd
==362398==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x109251: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Block was alloc'd at
==362398==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398== 
==362398== Invalid read of size 1
==362398==    at 0x484ED16: strlen (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x48D9D30: __vfprintf_internal (vfprintf-internal.c:1517)
==362398==    by 0x48C379E: printf (printf.c:33)
==362398==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==362398==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Address 0x4a8f040 is 0 bytes inside a block of size 20 free'd
==362398==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x109251: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Block was alloc'd at
==362398==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398== 
==362398== Invalid read of size 1
==362398==    at 0x484ED24: strlen (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x48D9D30: __vfprintf_internal (vfprintf-internal.c:1517)
==362398==    by 0x48C379E: printf (printf.c:33)
==362398==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==362398==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Address 0x4a8f041 is 1 bytes inside a block of size 20 free'd
==362398==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x109251: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Block was alloc'd at
==362398==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398== 
==362398== Invalid read of size 1
==362398==    at 0x48EE734: _IO_new_file_xsputn (fileops.c:1218)
==362398==    by 0x48EE734: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1196)
==362398==    by 0x48DA00B: outstring_func (vfprintf-internal.c:239)
==362398==    by 0x48DA00B: __vfprintf_internal (vfprintf-internal.c:1517)
==362398==    by 0x48C379E: printf (printf.c:33)
==362398==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==362398==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Address 0x4a8f044 is 4 bytes inside a block of size 20 free'd
==362398==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x109251: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Block was alloc'd at
==362398==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398== 
==362398== Invalid read of size 1
==362398==    at 0x48534C8: mempcpy (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x48EE664: _IO_new_file_xsputn (fileops.c:1235)
==362398==    by 0x48EE664: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1196)
==362398==    by 0x48DA00B: outstring_func (vfprintf-internal.c:239)
==362398==    by 0x48DA00B: __vfprintf_internal (vfprintf-internal.c:1517)
==362398==    by 0x48C379E: printf (printf.c:33)
==362398==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==362398==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Address 0x4a8f044 is 4 bytes inside a block of size 20 free'd
==362398==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x109251: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Block was alloc'd at
==362398==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398== 
==362398== Invalid read of size 1
==362398==    at 0x48534D6: mempcpy (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x48EE664: _IO_new_file_xsputn (fileops.c:1235)
==362398==    by 0x48EE664: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1196)
==362398==    by 0x48DA00B: outstring_func (vfprintf-internal.c:239)
==362398==    by 0x48DA00B: __vfprintf_internal (vfprintf-internal.c:1517)
==362398==    by 0x48C379E: printf (printf.c:33)
==362398==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==362398==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Address 0x4a8f042 is 2 bytes inside a block of size 20 free'd
==362398==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x109251: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Block was alloc'd at
==362398==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398== 
name: Maria, age: 5, score: 100
==362398== Invalid read of size 4
==362398==    at 0x1091C6: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==362398==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Address 0x4a8f04c is 12 bytes inside a block of size 20 free'd
==362398==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x109251: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Block was alloc'd at
==362398==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398== 
==362398== Invalid write of size 4
==362398==    at 0x1091D0: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==362398==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Address 0x4a8f04c is 12 bytes inside a block of size 20 free'd
==362398==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x109251: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Block was alloc'd at
==362398==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398== 
==362398== Invalid write of size 4
==362398==    at 0x1091D7: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==362398==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Address 0x4a8f04c is 12 bytes inside a block of size 20 free'd
==362398==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x109251: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398==  Block was alloc'd at
==362398==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362398==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==362398== 
Tamaño de s1: 8
Tamaño de int: 4
Tamaño de char[10]: 10
0x4a8f040
==362398== 
==362398== HEAP SUMMARY:
==362398==     in use at exit: 0 bytes in 0 blocks
==362398==   total heap usage: 2 allocs, 2 frees, 1,044 bytes allocated
==362398== 
==362398== All heap blocks were freed -- no leaks are possible
==362398== 
==362398== For lists of detected and suppressed errors, rerun with: -s
==362398== ERROR SUMMARY: 21 errors from 10 contexts (suppressed: 0 from 0)

Intenten asignar la edad y la nota de María después de hacer free. ¿El programa corre bien
después de eso? ¿Porqué? ¿Qué reporta Valgrind?

Se da el resultado en 0 ya que primero se libera y luego se asignan los valores a algo que ya no existe.

Tamaño de *s1: 20
name: Maria, age: 0, score: 0
name: ��dY, age: 20, score: 100
Tamaño de s1: 8
Tamaño de int: 4
Tamaño de char[10]: 10
0x55964d4da2a0

==363091== Memcheck, a memory error detector
==363091== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==363091== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==363091== Command: ./step2b
==363091== 
Tamaño de *s1: 20
==363091== Conditional jump or move depends on uninitialised value(s)
==363091==    at 0x48D9AD6: __vfprintf_internal (vfprintf-internal.c:1516)
==363091==    by 0x48C379E: printf (printf.c:33)
==363091==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10922F: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
==363091== Use of uninitialised value of size 8
==363091==    at 0x48BD2EB: _itoa_word (_itoa.c:177)
==363091==    by 0x48D8ABD: __vfprintf_internal (vfprintf-internal.c:1516)
==363091==    by 0x48C379E: printf (printf.c:33)
==363091==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10922F: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
==363091== Conditional jump or move depends on uninitialised value(s)
==363091==    at 0x48BD2FC: _itoa_word (_itoa.c:177)
==363091==    by 0x48D8ABD: __vfprintf_internal (vfprintf-internal.c:1516)
==363091==    by 0x48C379E: printf (printf.c:33)
==363091==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10922F: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
==363091== Conditional jump or move depends on uninitialised value(s)
==363091==    at 0x48D95C3: __vfprintf_internal (vfprintf-internal.c:1516)
==363091==    by 0x48C379E: printf (printf.c:33)
==363091==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10922F: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
==363091== Conditional jump or move depends on uninitialised value(s)
==363091==    at 0x48D8C05: __vfprintf_internal (vfprintf-internal.c:1516)
==363091==    by 0x48C379E: printf (printf.c:33)
==363091==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10922F: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
name: Maria, age: 0, score: 0
==363091== Invalid write of size 4
==363091==    at 0x109240: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Address 0x4a8f04c is 12 bytes inside a block of size 20 free'd
==363091==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x10923B: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Block was alloc'd at
==363091==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
==363091== Invalid write of size 4
==363091==    at 0x10924B: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Address 0x4a8f050 is 16 bytes inside a block of size 20 free'd
==363091==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x10923B: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Block was alloc'd at
==363091==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
==363091== Invalid read of size 4
==363091==    at 0x10919D: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Address 0x4a8f050 is 16 bytes inside a block of size 20 free'd
==363091==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x10923B: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Block was alloc'd at
==363091==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
==363091== Invalid read of size 4
==363091==    at 0x1091A4: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Address 0x4a8f04c is 12 bytes inside a block of size 20 free'd
==363091==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x10923B: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Block was alloc'd at
==363091==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
==363091== Invalid read of size 1
==363091==    at 0x484ED16: strlen (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x48D9D30: __vfprintf_internal (vfprintf-internal.c:1517)
==363091==    by 0x48C379E: printf (printf.c:33)
==363091==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Address 0x4a8f040 is 0 bytes inside a block of size 20 free'd
==363091==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x10923B: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Block was alloc'd at
==363091==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
==363091== Invalid read of size 1
==363091==    at 0x484ED24: strlen (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x48D9D30: __vfprintf_internal (vfprintf-internal.c:1517)
==363091==    by 0x48C379E: printf (printf.c:33)
==363091==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Address 0x4a8f041 is 1 bytes inside a block of size 20 free'd
==363091==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x10923B: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Block was alloc'd at
==363091==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
==363091== Invalid read of size 1
==363091==    at 0x48EE734: _IO_new_file_xsputn (fileops.c:1218)
==363091==    by 0x48EE734: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1196)
==363091==    by 0x48DA00B: outstring_func (vfprintf-internal.c:239)
==363091==    by 0x48DA00B: __vfprintf_internal (vfprintf-internal.c:1517)
==363091==    by 0x48C379E: printf (printf.c:33)
==363091==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Address 0x4a8f044 is 4 bytes inside a block of size 20 free'd
==363091==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x10923B: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Block was alloc'd at
==363091==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
==363091== Invalid read of size 1
==363091==    at 0x48534C8: mempcpy (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x48EE664: _IO_new_file_xsputn (fileops.c:1235)
==363091==    by 0x48EE664: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1196)
==363091==    by 0x48DA00B: outstring_func (vfprintf-internal.c:239)
==363091==    by 0x48DA00B: __vfprintf_internal (vfprintf-internal.c:1517)
==363091==    by 0x48C379E: printf (printf.c:33)
==363091==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Address 0x4a8f044 is 4 bytes inside a block of size 20 free'd
==363091==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x10923B: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Block was alloc'd at
==363091==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
==363091== Invalid read of size 1
==363091==    at 0x48534D6: mempcpy (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x48EE664: _IO_new_file_xsputn (fileops.c:1235)
==363091==    by 0x48EE664: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1196)
==363091==    by 0x48DA00B: outstring_func (vfprintf-internal.c:239)
==363091==    by 0x48DA00B: __vfprintf_internal (vfprintf-internal.c:1517)
==363091==    by 0x48C379E: printf (printf.c:33)
==363091==    by 0x1091C1: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Address 0x4a8f042 is 2 bytes inside a block of size 20 free'd
==363091==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x10923B: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Block was alloc'd at
==363091==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
name: Maria, age: 20, score: 100
==363091== Invalid read of size 4
==363091==    at 0x1091C6: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Address 0x4a8f04c is 12 bytes inside a block of size 20 free'd
==363091==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x10923B: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Block was alloc'd at
==363091==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
==363091== Invalid write of size 4
==363091==    at 0x1091D0: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Address 0x4a8f04c is 12 bytes inside a block of size 20 free'd
==363091==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x10923B: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Block was alloc'd at
==363091==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
==363091== Invalid write of size 4
==363091==    at 0x1091D7: print_student (in /home/alfanath/Progra2/Punteros/step2b)
==363091==    by 0x10925D: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Address 0x4a8f04c is 12 bytes inside a block of size 20 free'd
==363091==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x10923B: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091==  Block was alloc'd at
==363091==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==363091==    by 0x1091F6: main (in /home/alfanath/Progra2/Punteros/step2b)
==363091== 
Tamaño de s1: 8
Tamaño de int: 4
Tamaño de char[10]: 10
0x4a8f040
==363091== 
==363091== HEAP SUMMARY:
==363091==     in use at exit: 0 bytes in 0 blocks
==363091==   total heap usage: 2 allocs, 2 frees, 1,044 bytes allocated
==363091== 
==363091== All heap blocks were freed -- no leaks are possible
==363091== 
==363091== Use --track-origins=yes to see where uninitialised values come from
==363091== For lists of detected and suppressed errors, rerun with: -s
==363091== ERROR SUMMARY: 33 errors from 17 contexts (suppressed: 0 from 0)

También existe otra herramienta, integrada en los compiladores GCC y Clang que se llama Address Sanitizer o
ASAN. Para usarla compile el programa usando los flags `-fsanitize=address -static-libasan -g`. Corra el
programa y comente los resultados obtenidos.

Tamaño de *s1: 20
name: Maria, age: -1094795586, score: -1094795586
=================================================================
==363618==ERROR: AddressSanitizer: heap-use-after-free on address 0x60300000004c at pc 0x557a082f0e39 bp 0x7ffc9b6a3670 sp 0x7ffc9b6a3660
WRITE of size 4 at 0x60300000004c thread T0
    #0 0x557a082f0e38 in main /home/alfanath/Progra2/Punteros/step2b.c:27
    #1 0x7f92ddc5fd8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #2 0x7f92ddc5fe3f in __libc_start_main_impl ../csu/libc-start.c:392
    #3 0x557a0821b3a4 in _start (/home/alfanath/Progra2/Punteros/step2b+0x83a4)

0x60300000004c is located 12 bytes inside of 20-byte region [0x603000000040,0x603000000054)
freed by thread T0 here:
    #0 0x557a082aada7 in __interceptor_free (/home/alfanath/Progra2/Punteros/step2b+0x97da7)
    #1 0x557a082f0dfd in main /home/alfanath/Progra2/Punteros/step2b.c:26
    #2 0x7f92ddc5fd8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

previously allocated by thread T0 here:
    #0 0x557a082ab0f7 in __interceptor_malloc (/home/alfanath/Progra2/Punteros/step2b+0x980f7)
    #1 0x557a082f0dad in main /home/alfanath/Progra2/Punteros/step2b.c:21
    #2 0x7f92ddc5fd8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

SUMMARY: AddressSanitizer: heap-use-after-free /home/alfanath/Progra2/Punteros/step2b.c:27 in main
Shadow bytes around the buggy address:
  0x0c067fff7fb0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c067fff7fc0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c067fff7fd0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c067fff7fe0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c067fff7ff0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x0c067fff8000: fa fa 00 00 00 fa fa fa fd[fd]fd fa fa fa fa fa
  0x0c067fff8010: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c067fff8020: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c067fff8030: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c067fff8040: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c067fff8050: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
==363618==ABORTING

OJO: Address Sanitizer hace al programa un poco más lento. Típicamente no se usan en producción.
Y Valgrind es muchísimo más lento y ese nunca se usa en producción.

## Fuga de memoria

ATENCIÓN: Este ejercicio podría hacer que su computadora se congele y requiera ser reiniciada a la fuerza. GUARDEN TODO SU TRABAJO ANTES DE EMPEZARLO.

Escriban este programa en `step2c.c`:
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const size_t BUFFER_SIZE = 1024*1024*4;

void main() {
    uintptr_t x = 0;
    size_t total = 0;
    // Ajuste el número abajo para que el programa pida 1GB de memoria adicional
    // a la memoria física de la máquina.
    for (int i = 0; i < 1000000000000; i++) {
        printf("%zu %d |", total, i);
        x ^= (uintptr_t)malloc(BUFFER_SIZE);
    }
    printf("\n%zu", x);
}
```

Abran el monitor del sistema, de forma que puedan ver el gráfico de
consumo de memoria. Cuando corran el programa observen cómo crece el
gráfico de consumo de memoria y luego el de memoria paginada.

Corran el programa. ¿Qué sucede?

Revisen la salida del log del sistema usando el comando `less /var/log/syslog` en
la terminal (presionen g para ir al final). ¿Quién terminó el programa?

Cambie el valor del buffer, por ejemplo a `1024*1024*512`. Vuelva a correr el programa
¿la memoria sigue subiendo como antes? ¿Porqué?

Finalmente, cambie el tamaño del buffer por algo pequeño, como 100. Reduzca el límite
del for loop a 1000. Compile el programa y ejecútelo sobre strace (`strace step2c`). Con ese
comando va a observar las llamadas a funciones del sistema, en particular las llamadas
a `brk` y `mmap`. ¿Observa llamadas a estas llamadas a función cada vez que llama a `malloc`?

# Step 3: Buffer Overflow
Un error típico al programar en C (o usar bibliotecas escritas en C desde C++)
es el buffer overflow. Este consiste en intentar escribir en un buffer más
allá del límite de este.

Copien el archivo `step1.c` a `step3.c`.

En este curso nadie se llama María (ya revisé en Mediación Virtual). Coloquen
su nombre completo (con apellidos) en la línea que ejecuta la función `strcpy`
y compilen el programa. Reporten qué sucede.

El compilador es lo suficientemente inteligente para saber que estamos haciendo
algo mal. Típicamente uno debería ir a arreglar este error, pero no en esta
práctica.

Ejecuten el programa y reporten qué sucede. ¿De qué forma falló?

Dependiendo del compilador, es posible que haya fallado de formas diferentes
(o que no fallara). GCC introduce cierta protección contra sobreescritura de
la pila, conocida como Stack Smashing Protection.

Ahora, vuelvan a compilar el programa, pero esta vez deshabiliten Stack Smashing
Protection, usando el flag: `-fno-stack-protector`. Corran el programa y reporten
qué errores observan. ¿Qué edad y qué nota tienen?

In function ‘main’:
step3.c:19:5: warning: ‘__builtin_memcpy’ writing 24 bytes into a region of size 20 overflows the destination [-Wstringop-overflow=]
   19 |     strcpy(s1.name, "Nathalie Alfaro Quesada");
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
step3.c:16:20: note: destination object ‘s1’ of size 20
   16 |     struct student s1;

Lo que sucedió es que al hacer la copia de su nombre esta sobreescribió otros
valores, como la edad y la nota. Pero noten que quizá el programa no falló:
¡los datos están muy malos y corre perfectamente bien! (si les da un error
intenten acortar el nombre).

Este es un programa pequeño y pensado para que falle. Pero imagínense un error
de estos en un programa grande: un sistema operativo o un navegador pueden tener
millones de líneas de código. Protecciones como Stack Smashing Protector ayudan
a crear código más seguro, ya que este tipo de errores pueden ser usados para tomar
control de la máquina por parte de un usuario malicioso.

Corran el programa usando Valgrind (`valgrind ./step3`). ¿Qué error reporta?
leo algo que no inicialice

Modifiquen el programa para que el nombre mida menos de 20 caracteres (por ejemplo,
12 caracteres). Compilen y ejecuten el programa con Valgrind. ¿Muestra el mismo
error al correrlo con Valgrind? ¿Su compilador mostró algún warning esta vez?
¿Qué edad tienen?
no tira error porque lo que sobreescribe es parte del struct
HEAP SUMMARY:
==38404==     in use at exit: 0 bytes in 0 blocks
==38404==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==38404== 
==38404== All heap blocks were freed -- no leaks are possible
==38404== 
==38404== For lists of detected and suppressed errors, rerun with: -s
==38404== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Como pueden observar, es increiblemente fácil producir un buffer overflow. Y
este último error no puede ser detectado ni por el compilador ni por herramientas
especializadas como Valgrind. Para evitar esto, es importantísimo seguir buenas prácticas
de desarrollo: usar herramientas de análisis estático, herramientas como Valgrind,
pruebas, code review.

## Step 3a: pwned!
Creen el archivo `step3a.c` con el siguiente código:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct user {
    char name[10];
    bool is_admin;
};

void main() {
    struct user s1;
    s1.is_admin = false;

    printf("Escriba su nombre y presione enter:");
    scanf("%s", s1.name);

    if (s1.is_admin) {
        printf("Hola %s, tienes acceso al sistema!\n", s1.name);
    } else {
        printf("Hola %s, no eres administrador\n", s1.name);
    }
}
```

Compílenlo usando `gcc step3a.c -o step3a`. Ejecútenlo e intenten obtener
credenciales de administrador. Procuren que el programa no falle.
¿Con qué nombres no obtuvieron acceso? ¿Con qué nombres sí? ¿Con qué nombres
hicieron que el programa fallara? ¿Qué opinan de este último ejercicio?

Un programa debe desconfiar de TODAS las entradas externas. Es importante sanitizar los datos que vienen de terceros, no confiar en que tengan el formato esperado y los errores deben ser manejados de forma apropiada (ejm: mostrar un error en lugar de caerse). ¿Qué estrategias pueden tomar para arreglar el programa anterior?

Modifiquen el programa para que use `"%9s"` e intenten volver a obtener acceso de administrador. ¿Lo lograron? ¿porqué sí/no?
# Estructuras de datos y su complejidad computacional



### Para compilar:

`cmake -S . -B build && cmake --build build `


### Para ejecutar:

`./build/src/arbol `

### Para ejecutar las pruebas unitarias:

`./build/tests/arbol_test `


### Para ver fugas de memoria:

```
valgrind --leak-check=full --show-leak-kinds=all ./build/tests/arbol_test

valgrind --leak-check=full --show-leak-kinds=all ./build/src/arbol 
```


### Para formatear con Clang format:

`clang-format -i main.cpp`


### Cantidad de lineas por archivo:

`wc -l insertar*`


### Créditos:

- Nathalie Alfaro Quesada, B90221.
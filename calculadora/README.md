# Calculadora

## Instrucciones para compilar
En el directorio raiz del proyecto, ejecuten los siguientes comandos:

```bash
cmake -S . -B build  -DCMAKE_BUILD_TYPE=Debug && cmake --build build
```

Pueden ejecutarlo corriendo el programa que se encuentra en `build/src/calculadora`:

```bash
./build/src/Calculadora
```

## Instrucciones para correr coverage

En el directorio raiz del proyecto, ejecutar los siguientes comandos:

```bash
cmake -S . -B build  -DCMAKE_BUILD_TYPE=Debug -DCOVERAGE=ON && cmake --build build && cd build && make && make coverage && cd ..
```

Luego pueden abrir el archivo index.html que se encuentra en la carpeta coverage (build/coverage/index.html).



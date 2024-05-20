#include <iostream>
using namespace std;

// Encabezado
#ifndef BST_HH
#define BST_HH

class Nodo {
public:
  // Atributos
  int valor;
  Nodo *izquierda;
  Nodo *derecha;

  // Constructor
  Nodo(int valor) : valor(valor), izquierda(nullptr), derecha(nullptr) {}
};

class BST {
public:
  Nodo *raiz;

public:
  // Constructor
  BST() : raiz(nullptr) {}

  // Metodos
  bool insertarNodo(int valor);
  Nodo *insertarNodoRecursivo(Nodo *nodoActual, int valor);
  bool contieneValor(int numero);
};
#endif
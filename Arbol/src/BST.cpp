#include <iostream>

#include <BST.hh>

using namespace std;

// Agrega un nuevo nodo
bool BST::insertarNodo(int valor) {
  raiz = insertarNodoRecursivo(raiz, valor);
  return true;
} // End insertarNodo

Nodo *BST::insertarNodoRecursivo(Nodo *nodoActual, int valor) {
  Nodo *nuevoNodo = new Nodo(valor);

  if (nodoActual == nullptr) {
    return nuevoNodo;
  }

  if (valor < nodoActual->valor) {
    nodoActual->izquierda = insertarNodoRecursivo(nodoActual->izquierda, valor);
  } else if (valor > nodoActual->valor) {
    nodoActual->derecha = insertarNodoRecursivo(nodoActual->derecha, valor);
  }
  return nodoActual;
} // End insertarNodoRecursivo

bool BST::contieneValor(int numero) {
  Nodo *actual = raiz;

  while (actual != nullptr) {
    if (numero == actual->valor) {
      return true;
    } else if (numero < actual->valor) {
      actual = actual->izquierda;
    } else {
      actual = actual->derecha;
    }
  }
  return false;
} // End contieneValor

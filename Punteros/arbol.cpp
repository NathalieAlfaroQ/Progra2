#include <iostream>
using namespace std;

class Nodo
{
public:
  int valor;
  Nodo *izquierda;
  Nodo *derecha;
  Nodo *padre;

  // Constructor
  Nodo(int val)
  {
    valor = val;
    izquierda = nullptr;
    derecha = nullptr;
    padre = nullptr;
  }
}; // End class Nodo

class Arbol
{
  Nodo *raiz;

  void agregarNodoRecursivo(Nodo *nodo, int valor)
  {
    // Guardar a la izquierda
    if (valor < nodo->valor)
    {
      if (nodo->izquierda != nullptr)
      {
        agregarNodoRecursivo(nodo->izquierda, valor);
      }
      else
      {
        Nodo *nuevoNodo = new Nodo(valor);
        nodo->izquierda = nuevoNodo;
        nuevoNodo->padre = nodo;
      }
    }
    else if (valor > nodo->valor) //Guardar a la derecha
    {
      if (nodo->derecha != nullptr)
      {
        agregarNodoRecursivo(nodo->derecha, valor);
      }
      else
      {
        Nodo *nuevoNodo = new Nodo(valor);
        nodo->derecha = nuevoNodo;
        nuevoNodo->padre = nodo;
      }
    }
  }

public:
  Arbol()
  {
    raiz = nullptr;
  }

  void agregarNodo(int valor)
  {
    if (raiz == nullptr)
    {
      raiz = new Nodo(valor);
    }
    else
    {
      agregarNodoRecursivo(raiz, valor);
    }
  }

  Nodo *obtenerRaiz()
  {
    return raiz;
  }

  int sumaArbol(int valor, Nodo* izquierda, Nodo* derecha) {
    int respuesta = valor;
    if (izquierda != nullptr) {
      respuesta += izquierda->sumaArbol(respuesta, izquierda->izquierda, derecha->derecha);
    }
    if (derecha != nullptr) {
      respuesta =+ derecha->sumaArbol();
    }
    return respuesta;
  }


}; // End class Arbol

int main()
{
  Arbol arbol;

  arbol.agregarNodo(5);
  arbol.agregarNodo(3);
  arbol.agregarNodo(8);
  arbol.agregarNodo(2);

  Nodo *raiz = arbol.obtenerRaiz();
  cout << "Raiz: " << raiz->valor << endl;
  cout << "Izquierda: " << raiz->izquierda->valor << endl;
  cout << "Derecha: " << raiz->derecha->valor << endl;
  cout << "Padre del nodo 2: " << raiz->izquierda->izquierda->padre->valor << endl;

  return 0;
} // End main
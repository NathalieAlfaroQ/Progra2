// Incluye bibliotecas:
#include <vector>

// Encabezado:
#ifndef TABLERO_HPP
#define TABLERO_HPP

using namespace std;

class Tablero {
  // Atributos, son privados por defecto:
  int filas, columnas;
  // Matriz de tipo entero.
  vector<vector<int>> matriz;

 public:
  // Constructor:
  Tablero(int filas, int columnas) : filas(filas), columnas(columnas) {
    if (filas < 4 || columnas < 4) {
      throw invalid_argument("Solo filas y columnas mayores o iguales a 4.");
    }  // End if

    // Llena la matriz con 0.
    matriz.resize(filas, vector<int>(columnas, 0));
  }  // End constructor

  // Métodos:
  // Tipo de dato - Nombre de la función - Argumentos
  bool columnaLlena(int columnaUsuario);
  bool comprobarEmpate();
  bool comprobarGanar();
  void imprimir();
  int obtenerColumnas();
  bool ponerFichas(int columnaUsuario, int jugador);
  int victoriaIA();
};  // End class Tablero

#endif
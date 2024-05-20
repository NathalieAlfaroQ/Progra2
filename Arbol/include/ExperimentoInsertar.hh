// Bibliotecas
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <time.h>
#include <unistd.h>
#include <unordered_set>
#include <vector>
#include <fstream>
using namespace std;

// Encabezados ajenos
#include <BST.hh>

// Encabezado
#ifndef EXPERIMENTOINSERTAR_HH
#define EXPERIMENTOINSERTAR_HH

class ExperimentoInsertar {
  public:
  // Atributos
  int operacionesTotal, batch;

  // Constructor
  ExperimentoInsertar(int operacionesTotal, int batch) : operacionesTotal(operacionesTotal), batch(batch) {}

  // Estructuras
  BST *arbol = new BST;
  BST *arbol2 = new BST;
  vector<int> arreglo;
  vector<int> arreglo2;
  set<int> arbolSet;
  set<int> arbolSet2;
  unordered_set<int> arbolUnset;
  unordered_set<int> arbolUnset2;

  // Tiempos
  chrono::high_resolution_clock::time_point inicio;
  chrono::high_resolution_clock::time_point fin;
  chrono::duration<double, nano> diferencia;

  // Guardar los datos
  double *duracion = new double[10000];
  int *numeroOperacion = new int[10000];
  int *valor = new int[10000];

  // Metodos:
  // Arbol
  void insertarOrdenArbol(int operacionesTotal, int batch);
  void insertarDesordenArbol(int operacionesTotal, int batch);
  // Set
  void insertarOrdenSet(int operacionesTotal, int batch);
  void insertarDesordenSet(int operacionesTotal, int batch);
  // Unset
  void insertarOrdenUnset(int operacionesTotal, int batch);
  void insertarDesordenUnset(int operacionesTotal, int batch);
  // Vector
  void insertarOrdenVector(int operacionesTotal, int batch);
  void insertarDesordenVector(int operacionesTotal, int batch);
  // Archivo
  void archivo(const string &nombreArchivo, const int *numeroOperacion,
               const int *valor, const double *duracion, int operacionesTotal);
};
#endif
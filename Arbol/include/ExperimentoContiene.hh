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
#include <ExperimentoInsertar.hh>

// Encabezado
#ifndef EXPERIMENTOCONTIENE_HH
#define EXPERIMENTOCONTIENE_HH

class ExperimentoContiene {
  public:
  // Atributos
  int operacionesTotal, batch;

  // Constructor
  ExperimentoContiene(int operacionesTotal, int batch) : operacionesTotal(operacionesTotal), batch(batch) {}
  
  // Tiempos
  chrono::high_resolution_clock::time_point inicio;
  chrono::high_resolution_clock::time_point fin;
  chrono::duration<double, nano> diferencia;

  // Guardar los datos
  double *duracionC = new double[100];
  int *numeroOperacionC = new int[100];
  int *valorC = new int[100];

  // Metodos:
  // Arbol
  void contieneOrdenArbol(int operacionesTotal, int batch);
  void contieneDesordenArbol(int operacionesTotal, int batch);
  // Set
  void contieneOrdenSet(int operacionesTotal, int batch);
  void contieneDesordenSet(int operacionesTotal, int batch);
  // Unset
  void contieneOrdenUnset(int operacionesTotal, int batch);
  void contieneDesordenUnset(int operacionesTotal, int batch);
  // Vector
  void contieneOrdenVector(int operacionesTotal, int batch);
  void contieneDesordenVector(int operacionesTotal, int batch);
  // Archivo
  void archivo(const string &nombreArchivo, const int *numeroOperacion,
               const int *valor, const double *duracion, int operacionesTotal);
};
#endif
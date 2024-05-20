// Bibliotecas
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <time.h>
#include <unistd.h>
#include <unordered_set>
#include <vector>
using namespace std;

#include <iostream>

// Encabezados
#include <BST.hh>
#include <ExperimentoInsertar.hh>

// Insertar en orden por estructura de arbol
void ExperimentoInsertar::insertarOrdenArbol(int operacionesTotal, int batch) {
  
  cout << "se inicia el experimento" << endl;

  // operacionesTotal
  for (int x = 0; x < operacionesTotal; x++) {
    // Se inicia a contar el tiempo de la insercion
    inicio = chrono::high_resolution_clock::now();
    // Por batch
    for (int y = 0; y < batch; y++) {
      arbol->insertarNodo(y + x * 10000);
    }
    // Se termina de medir el tiempo de la insercion
    fin = chrono::high_resolution_clock::now();
    // Se guarda el numero de operacion en el arreglo
    numeroOperacion[x] = x;
    // Se guarda el numero en el arreglo
    valor[x] = x;
    // Se busca la duracion, para guardarla en el arreglo
    diferencia = fin - inicio;
    // Se guarda la duracion en nanosegundos
    duracion[x] = diferencia.count();
    // Se imprime la duracion en nanosegundos
  }

  cout << "se completo el experimento" << endl;

  archivo("insertarOrdenArbol.csv", numeroOperacion, valor, duracion, operacionesTotal);

  cout << "se guardo el archivo" << endl;
}

// Insertar aleatoriamente por estructura del arbol
void ExperimentoInsertar::insertarDesordenArbol(int operacionesTotal,
                                                int batch) {
  for (int x = 0; x < operacionesTotal; x++) {
    inicio = chrono::high_resolution_clock::now();
    for (int y = 0; y < batch; y++) {
      // Se busca un numero aleatorio
      valor[y] = rand();
      arbol2->insertarNodo(valor[y]);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacion[x] = x;
    diferencia = fin - inicio;
    duracion[x] = diferencia.count();
  }
  archivo("insertarDesordenArbol.csv", numeroOperacion, valor, duracion,
          operacionesTotal);
}

// Insertar en orden por medio de Set
void ExperimentoInsertar::insertarOrdenSet(int operacionesTotal, int batch) {
  for (int x = 0; x < operacionesTotal; x++) {
    inicio = chrono::high_resolution_clock::now();
    for (int y = 0; y < batch; y++) {
      arbolSet.insert(y + x * 10000);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacion[x] = x;
    valor[x] = x;
    diferencia = fin - inicio;
    duracion[x] = diferencia.count();
  }
  archivo("insertarOrdenSet.csv", numeroOperacion, valor, duracion,
          operacionesTotal);
}

// Insertar en desorden por medio de Set
void ExperimentoInsertar::insertarDesordenSet(int operacionesTotal, int batch) {
  for (int x = 0; x < operacionesTotal; x++) {
    inicio = chrono::high_resolution_clock::now();
    for (int y = 0; y < batch; y++) {
      valor[y] = rand();
      arbolSet2.insert(valor[x]);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacion[x] = x;
    diferencia = fin - inicio;
    duracion[x] = diferencia.count();
  }
  archivo("insertarDesordenSet.csv", numeroOperacion, valor, duracion,
          operacionesTotal);
}

// Insertar en orden Unorderedset
void ExperimentoInsertar::insertarOrdenUnset(int operacionesTotal, int batch) {
  for (int x = 0; x < operacionesTotal; x++) {
    inicio = chrono::high_resolution_clock::now();
    for (int y = 0; y < batch; y++) {
      arbolUnset.insert(y + x * 10000);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacion[x] = x;
    valor[x] = x;
    diferencia = fin - inicio;
    duracion[x] = diferencia.count();
  }
  archivo("insertarOrdenUnset.csv", numeroOperacion, valor, duracion,
          operacionesTotal);
}

// Insertar en desorden por medio de Unorderedset
void ExperimentoInsertar::insertarDesordenUnset(int operacionesTotal,
                                                int batch) {
  for (int x = 0; x < operacionesTotal; x++) {
    inicio = chrono::high_resolution_clock::now();
    for (int y = 0; y < batch; y++) {
      valor[y] = rand();
      arbolUnset2.insert(valor[x]);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacion[x] = x;
    diferencia = fin - inicio;
    duracion[x] = diferencia.count();
  }
  archivo("insertarDesordenUnset.csv", numeroOperacion, valor, duracion,
          operacionesTotal);
}

// Insertar en orden vector
void ExperimentoInsertar::insertarOrdenVector(int operacionesTotal, int batch) {
  for (int x = 0; x < operacionesTotal; x++) {
    inicio = chrono::high_resolution_clock::now();
    for (int y = 0; y < batch; y++) {
      arreglo.push_back(y + x * 10000);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacion[x] = x;
    valor[x] = x;
    diferencia = fin - inicio;
    duracion[x] = diferencia.count();
  }
  archivo("insertarOrdenVector.csv", numeroOperacion, valor, duracion,
          operacionesTotal);
}

// Insertar en desorden vector
void ExperimentoInsertar::insertarDesordenVector(int operacionesTotal,
                                                 int batch) {
  for (int x = 0; x < operacionesTotal; x++) {
    inicio = chrono::high_resolution_clock::now();
    for (int y = 0; y < batch; y++) {
      valor[y] = rand();
      arreglo2.push_back(valor[x]);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacion[x] = x;
    diferencia = fin - inicio;
    duracion[x] = diferencia.count();
  }
  archivo("insertarDesordenVector.csv", numeroOperacion, valor, duracion,
          operacionesTotal);
}

// Crear archivo csv
void ExperimentoInsertar::archivo(const string &nombreArchivo,
                                  const int *numeroOperacion, const int *valor,
                                  const double *duracion,
                                  int operacionesTotal) {
  // Abrir el archivo en modo de escritura
  ofstream archivoCSV(nombreArchivo);

  if (!archivoCSV.is_open()) {
    cerr << "Error al abrir el archivo CSV." << endl;
    return;
  }

  // Escribir encabezados en el archivo CSV
  archivoCSV << "Numero operacion, Valor, duracion" << endl;

  // Escribir datos en el archivo CSV
  for (size_t i = 0; i < operacionesTotal; ++i) {
    archivoCSV << numeroOperacion[i] << "," << valor[i] << "," << duracion[i]
               << endl;
  }

  // Cerrar el archivo
  archivoCSV.close();

  cout << "Datos guardados en el archivo CSV exitosamente." << endl;
}
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

// Encabezados
#include <BST.hh>
#include <ExperimentoContiene.hh>
#include <ExperimentoInsertar.hh>

// Notas:
// Orden: 100000
// Azar: 1000

// Contiene en orden por estructura de arbol
void ExperimentoContiene::contieneOrdenArbol(int operacionesTotal, int batch) {
  BST *arbolC = new BST();
  for (int insercion = 0; insercion < 100000; insercion++) {
    arbolC->insertarNodo(rand());
  }

  for (int x = 0; x < operacionesTotal; x++) {
    inicio = chrono::high_resolution_clock::now();
    for (int y = 0; y < batch; y++) {
      arbolC->contieneValor(y);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacionC[x] = x;
    valorC[x] = x;
    diferencia = fin - inicio;
    duracionC[x] = diferencia.count();
  }
  archivo("contieneOrdenArbol.csv", numeroOperacionC, valorC, duracionC,
          operacionesTotal);
}

// Contiene aleatoriamente por estructura del arbol
void ExperimentoContiene::contieneDesordenArbol(int operacionesTotal,
                                                int batch) {
  BST *arbol2C = new BST();
  // Insertar mil nodos aleatorios
  for (int insercion = 0; insercion < 1000; insercion++) {
    arbol2C->insertarNodo(rand());
  }
  // Medicion
  for (int x = 0; x < operacionesTotal; x++) {
    inicio = chrono::high_resolution_clock::now();

    for (int y = 0; y < batch; y++) {
      valorC[y] = rand();
      arbol2C->contieneValor(valorC[y]);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacionC[x] = x;
    diferencia = fin - inicio;
    duracionC[x] = diferencia.count();
  }
  archivo("contieneDesordenArbol.csv", numeroOperacionC, valorC, duracionC,
          operacionesTotal);
}

// Contiene en orden por medio de Set
void ExperimentoContiene::contieneOrdenSet(int operacionesTotal, int batch) {
  set<int> arbolSetC;
  for (int insercion = 0; insercion < 100000; insercion++) {
    arbolSetC.insert(rand());
  }

  for (int x = 0; x < operacionesTotal; x++) {
    inicio = chrono::high_resolution_clock::now();
    for (int y = 0; y < batch; y++) {
      arbolSetC.find(y);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacionC[x] = x;
    valorC[x] = x;
    diferencia = fin - inicio;
    duracionC[x] = diferencia.count();
  }
  archivo("contieneOrdenSet.csv", numeroOperacionC, valorC, duracionC,
          operacionesTotal);
}

// Contiene en desorden por medio de Set
void ExperimentoContiene::contieneDesordenSet(int operacionesTotal, int batch) {
  set<int> arbolSet2C;
  for (int insercion = 0; insercion < 1000; insercion++) {
    arbolSet2C.insert(rand());
  }

  for (int x = 0; x < operacionesTotal; x++) {
    inicio = chrono::high_resolution_clock::now();
    for (int y = 0; y < batch; y++) {
      valorC[y] = rand();
      arbolSet2C.find(valorC[y]);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacionC[x] = x;
    diferencia = fin - inicio;
    duracionC[x] = diferencia.count();
  }
  archivo("contieneDesordenSet.csv", numeroOperacionC, valorC, duracionC,
          operacionesTotal);
}

// Contiene en orden Unorderedset
void ExperimentoContiene::contieneOrdenUnset(int operacionesTotal, int batch) {
  unordered_set<int> arbolUnsetC;
  for (int insercion = 0; insercion < 100000; insercion++) {
    arbolUnsetC.insert(rand());
  }

  for (int x = 0; x < operacionesTotal; x++) {
    inicio = chrono::high_resolution_clock::now();
    for (int y = 0; y < batch; y++) {
      arbolUnsetC.find(y);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacionC[x] = x;
    valorC[x] = x;
    diferencia = fin - inicio;
    duracionC[x] = diferencia.count();
  }
  archivo("contieneOrdenUnset.csv", numeroOperacionC, valorC, duracionC,
          operacionesTotal);
}

// Contiene en desorden por medio de Unorderedset
void ExperimentoContiene::contieneDesordenUnset(int operacionesTotal,
                                                int batch) {
  unordered_set<int> arbolUnset2C;
  for (int insercion = 0; insercion < 1000; insercion++) {
    arbolUnset2C.insert(rand());
  }

  for (int x = 0; x < operacionesTotal; x++) {
    inicio = chrono::high_resolution_clock::now();
    for (int y = 0; y < batch; y++) {
      valorC[y] = rand();
      arbolUnset2C.find(valorC[y]);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacionC[x] = x;
    diferencia = fin - inicio;
    duracionC[x] = diferencia.count();
  }
  archivo("contieneDesordenUnset.csv", numeroOperacionC, valorC, duracionC,
          operacionesTotal);
}

// Contiene en orden vector
void ExperimentoContiene::contieneOrdenVector(int operacionesTotal, int batch)
{
  vector<int> arregloC;
  for (int insercion = 0; insercion < 100000; insercion++)
  {
    arregloC.push_back(rand());
  }

  for (int x = 0; x < operacionesTotal; x++)
  {
    inicio = chrono::high_resolution_clock::now();
    for (int y = 0; y < batch; y++)
    {
      find (arregloC.begin(), arregloC.end(), y);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacionC[x] = x;
    valorC[x] = x;
    diferencia = fin - inicio;
    duracionC[x] = diferencia.count();
  }
  archivo("contieneOrdenVector.csv", numeroOperacionC, valorC, duracionC,
operacionesTotal);
}

// Contiene en desorden vector
void ExperimentoContiene::contieneDesordenVector(int operacionesTotal, int
batch)
{
  vector<int> arreglo2C;
  // Insertar mil numeros aleatorios
  for (int insercion = 0; insercion < 1000; insercion++)
  {
    arreglo2C.push_back(rand());
  }
  // Medicion
  for (int x = 0; x < operacionesTotal; x++)
  {
    inicio = chrono::high_resolution_clock::now();

    for (int y = 0; y < batch; y++)
    {
      valorC[y] = rand();
      find (arreglo2C.begin(), arreglo2C.end(), valorC[y]);
    }
    fin = chrono::high_resolution_clock::now();
    numeroOperacionC[x] = x;
    diferencia = fin - inicio;
    duracionC[x] = diferencia.count();
  }
  archivo("contieneDesordenVector.csv", numeroOperacionC, valorC, duracionC,
operacionesTotal);
}

// Crear archivo csv
void ExperimentoContiene::archivo(const string &nombreArchivo,
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

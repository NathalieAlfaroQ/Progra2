#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <unordered_set>
#include <vector>

#include <BST.hh>
#include <ExperimentoInsertar.hh>
#include <ExperimentoContiene.hh>

using namespace std;

int main() {
  try {
    int experimento, operacionesTotal, batch;

    cout << "\n\nDigite la cantidad de operaciones total:\n";
    cin >> operacionesTotal;

    cout << "\n\nDigite las operaciones por batch:\n";
    cin >> batch;

    cout << "Experimento que desea ejecutar:\n\n1-Insertar en "
            "orden.\n2-Insertar en desorden."
            "\n3-Buscar en orden.\n4-Buscar en desorden.\n";
    cin >> experimento;

    cout << "Escogio el experimento: " << experimento << endl;

    if (experimento == 1) 
    {
      // Insertar en orden
      cout << "insertarOrdenArbol" << endl;
      ExperimentoInsertar experimentoInsertarOrdenArbol(operacionesTotal, batch);
      experimentoInsertarOrdenArbol.insertarOrdenArbol(operacionesTotal, batch);
      
      cout << "insertarOrdenSet" << endl;
      ExperimentoInsertar experimentoInsertarOrdenSet(operacionesTotal, batch);
      experimentoInsertarOrdenSet.insertarOrdenSet(operacionesTotal, batch);
      
      cout << "insertarOrdenUnset" << endl;
      ExperimentoInsertar insertarOrdenUnset(operacionesTotal, batch);
      insertarOrdenUnset.insertarOrdenUnset(operacionesTotal, batch);
      
      cout << "insertarOrdenVector" << endl;
      ExperimentoInsertar insertarOrdenVector(operacionesTotal, batch);
      insertarOrdenVector.insertarOrdenVector(operacionesTotal, batch);
    }
    else if (experimento == 2) 
    {
      // Insertar en desorden
      cout << "insertarDesordenArbol" << endl;
      ExperimentoInsertar insertarDesordenArbol(operacionesTotal, batch);
      insertarDesordenArbol.insertarDesordenArbol(operacionesTotal, batch);

      cout << "insertarDesordenSet" << endl;
      ExperimentoInsertar insertarDesordenSet(operacionesTotal, batch);
      insertarDesordenSet.insertarDesordenSet(operacionesTotal, batch);
      
      cout << "insertarDesordenUnset" << endl;
      ExperimentoInsertar insertarDesordenUnset(operacionesTotal, batch);
      insertarDesordenUnset.insertarDesordenUnset(operacionesTotal, batch);

      cout << "insertarDesordenVector" << endl;
      ExperimentoInsertar insertarDesordenVector(operacionesTotal, batch);
      insertarDesordenVector.insertarDesordenVector(operacionesTotal, batch);
    } 
    else if (experimento == 3) 
    {
      // Buscar en orden
     // cout << "contieneOrdenArbol" << endl;
      //ExperimentoContiene contieneOrdenArbol(operacionesTotal, batch);
     // contieneOrdenArbol.contieneOrdenArbol(operacionesTotal, batch);

      cout << "contieneOrdenSet" << endl;
      ExperimentoContiene contieneOrdenSet(operacionesTotal, batch);
      contieneOrdenSet.contieneOrdenSet(operacionesTotal, batch);

      cout << "contieneOrdenUnset" << endl;
      ExperimentoContiene contieneOrdenUnset(operacionesTotal, batch);
      contieneOrdenUnset.contieneOrdenUnset(operacionesTotal, batch);

      cout << "contieneOrdenVector" << endl;
      ExperimentoContiene contieneOrdenVector(operacionesTotal, batch);
      contieneOrdenVector.contieneOrdenVector(operacionesTotal, batch);
    } 
    else if (experimento == 4) 
    {
      // Buscar en desorden
      cout << "contieneDesordenArbol" << endl;
      ExperimentoContiene contieneDesordenArbol(operacionesTotal, batch);
      contieneDesordenArbol.contieneDesordenArbol(operacionesTotal, batch);
      
      cout << "contieneDesordenSet" << endl;
      ExperimentoContiene contieneDesordenSet(operacionesTotal, batch);
      contieneDesordenSet.contieneDesordenSet(operacionesTotal, batch);
     
      cout << "contieneDesordenUnset" << endl;
      ExperimentoContiene contieneDesordenUnset(operacionesTotal, batch);
      contieneDesordenUnset.contieneDesordenUnset(operacionesTotal, batch);
      
      cout << "contieneDesordenVector" << endl;
      ExperimentoContiene contieneDesordenVector(operacionesTotal, batch);
      contieneDesordenVector.contieneDesordenVector(operacionesTotal, batch);
    } 
    else 
    {
      throw invalid_argument("Solo puede digitar 1, 2, 3 o 4.");
    }
  } catch (invalid_argument &e) {
    cerr << e.what() << endl;
    return -1;
  }
  return 0;
}
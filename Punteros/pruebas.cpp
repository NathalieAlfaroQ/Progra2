#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
using namespace std;

class Tablero
{
private:
  int filas;
  int columnas;
  vector<vector<int>> matriz;

public:
  Tablero(int filas, int columnas) : filas(filas), columnas(columnas)
  {
    matriz.resize(filas, vector<int>(columnas, 0));
  }

  bool comprobarVictoria()
  {
    // Implementa aquí la lógica para comprobar la victoria
    int comprobar;
    for (int i = filas - 1; i >= 0; i--)
    {
      for (int j = columnas - 1; j >= 0; j--)
      {
        if (matriz[i][j] != 0)
        {
          // vertical
          if (i - 3 >= 0)
          {
            comprobar = matriz[i][j];
            if (comprobar == matriz[i - 1][j] && comprobar == matriz[i - 2][j] && comprobar == matriz[i - 3][j])
            {

              return true;
            }
          }
          // Horizontal
          if (j - 3 >= 0)
          {
            comprobar = matriz[i][j];
            if (comprobar == matriz[i][j - 1] && comprobar == matriz[i][j - 2] && comprobar == matriz[i][j - 3])
            {

              return true;
            }
          }
          // Diagonal izquierda
          if (i - 3 >= 0 && j - 3 >= 0)
          {
            comprobar = matriz[i][j];
            if (comprobar == matriz[i - 1][j - 1] && comprobar == matriz[i - 2][j - 2] && comprobar == matriz[i - 3][j - 3])
            {

              return true;
            }
          }
          // Diagonal derecho
          if (i - 3 >= 0 && j + 3 <= columnas)
          {
            comprobar = matriz[i][j];
            if (comprobar == matriz[i - 1][j + 1] && comprobar == matriz[i - 2][j + 2] && comprobar == matriz[i - 3][j + 3])
            {

              return true;
            }
          }
        }
      }
    }

    return false;
  }

  bool columnaLlena(int columna)
  {
    return matriz[0][columna] != 0;
  }

  bool ponerFicha(int columna, int jugador)
  {
    for (int i = filas - 1; i >= 0; i--)
    {
      if (matriz[i][columna] == 0)
      {
        matriz[i][columna] = jugador;
        return true;
      }
    }
    return false;
  }

  void imprimirTablero()
  {
    for (int i = 0; i < filas; i++)
    {
      for (int j = 0; j < columnas; j++)
      {
        cout << matriz[i][j] << " ";
      }
      cout << endl;
    }
  }

  int getColumnas()
  {
    return columnas;
  }

  bool tableroLLeno()
  {
    bool e = false;

    for (int i = 0; i < filas; i++)
    {
      for (int j = 0; j < columnas; j++)
      {
        if (matriz[i][j] == 0)
        {
          e = false;
          return e;
        }
        else
        {
          e = true;
        }
      }
    }
    return e;
  }
};

class Main
{
private:
  Tablero tablero;

public:
  Main(int filas, int columnas) : tablero(filas, columnas) {}

  void jugar(int modo)
  {
    // Elige quien empieza primero de manera aleatoria
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> distR(1, 2);
    int jugador = distR(rng);
    cout << "\n El jugador " << jugador << " empieza primero." << endl;

    bool victoria = false;
    bool empate = false;
    bool iA = true;
    while (!victoria && !empate)
    {
      tablero.imprimirTablero();
      int columna;

      do
      {
        if (modo == 1)
        {

          cout << "Jugador " << jugador << ", ingresa el número de columna (0-" << tablero.getColumnas() - 1 << "): ";
          cin >> columna;
        }
        else if (modo == 2)
        {
          if (jugador == 1)
          {
            cout << "Jugador " << jugador << ", ingresa el número de columna (0-" << tablero.getColumnas() - 1 << "): ";
            cin >> columna;
          }
          else
          {
            random_device dev;
            mt19937 rng(dev());
            uniform_int_distribution<mt19937::result_type> distR(0, tablero.getColumnas() - 1);
            columna = distR(rng);
            cout << "La IA ha jugado en la columna: " << columna << endl;
          }
        }
        else
        {
          random_device dev;
          mt19937 rng(dev());
          uniform_int_distribution<mt19937::result_type> distR(0, tablero.getColumnas() - 1);
          columna = distR(rng);
          if (tablero.columnaLlena(columna) == false)
          {

            this_thread::sleep_for(chrono::milliseconds(2000)); // sleep for 2 second
            cout << "La IA " << jugador << " ha jugado en la columna: " << columna << endl;
          }
        }

      } while (columna < 0 || columna >= tablero.getColumnas() || tablero.columnaLlena(columna));

      if (tablero.ponerFicha(columna, jugador))
      {
        victoria = tablero.comprobarVictoria();
        empate = tablero.tableroLLeno();
        jugador = (jugador == 1) ? 2 : 1;
      }
    }

    tablero.imprimirTablero();
    jugador = (jugador == 1) ? 2 : 1;
    if (victoria)
    {
      cout << "¡Jugador " << jugador << " ha ganado!" << endl;
    }
    else
    {
      cout << "¡Empate!" << endl;
    }
  }
};

int main()
{
  int filas, columnas, modo;

  do
  {
    cout << "Ingresa el número de filas (mayor a 3): ";
    cin >> filas;
    cout << "Ingresa el número de columnas (mayor a 3): ";
    cin >> columnas;
    cout << "Ingrese el modo:";
    cin >> modo;
  } while (filas < 4 || columnas < 4);

  Main juego(filas, columnas);
  juego.jugar(modo);

  return 0;
}
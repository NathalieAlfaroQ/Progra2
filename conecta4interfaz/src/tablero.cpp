// Incluye bibliotecas:
/*#include <cstring>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

// Incluye encabezados:
#include <jugadores.hpp>
#include <tablero.hpp>

using namespace std;

// Método de tipo vacío que imprime el tablero.
void Tablero::imprimir()
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            cout << matriz[i][j] << " ";
        } // End for
        cout << endl;
    } // End for
} // End imprimir

/*
 * Este método de tipo booleano de la clase Tablero, tiene como
 * argumento la columna que el usuario digita para colocar su
 * ficha en la matriz, el fin es verificar si la columna
 * solicitada está dentro del rango y si está llena.
 */
/*bool Tablero::columnaLlena(int columnaUsuario)
{
    // Verificamos si la columna está dentro de los límites de la matriz.
    if (columnaUsuario < 0 || columnaUsuario >= columnas)
    {
        throw out_of_range("Error: Columna fuera de rango.");
    } // End if

    // Revisar si la columna está llena.
    return matriz[0][columnaUsuario] != 0;
} // End columnaLlena

/*
 * Este método de tipo booleano de la clase Tablero, tiene como
 * argumento dos enteros que serán el número de jugador y la columna
 * en la que el usuario quiere colocar su ficha. Primeramente, verifica
 * si la columna tiene espacio para poner la ficha, luego recorre la matriz
 * de abajo hacia arriba, si la celda está vacía se puede colocar la ficha y
 * eso retornaría verdadero.
 */
/*bool Tablero::ponerFichas(int columnaUsuario, int jugador)
{
    // Verificar si hay campo para colocar la ficha en la columna.
    if (columnaLlena(columnaUsuario))
    {
        // No se pudo colocar la ficha ya que la columna está llena.
        return false;
    } // End if

    // Recorre la matriz de abajo hacia arriba.
    for (int i = filas - 1; i >= 0; i--)
    {
        // Si la celda está vacía...
        if (matriz[i][columnaUsuario] == 0)
        {
            // ...coloque la ficha del jugador.
            matriz[i][columnaUsuario] = jugador;
            return true;
        } // End if
    }     // End for
    return false;
} // End ponerFichas

// Solo para retornar las columnas del tablero.
int Tablero::obtenerColumnas() { return columnas; } // End obtenerColumnas

/*
 * Este método de tipo booleano de la clase Tablero, recorre la
 * matriz de abajo hacia y verifica las 3 formas de ganar: vertical,
 * horizontal o diagonal. La forma de ganar es que hayan 4 fichas del
 * mismo "color" (número) seguidas.
 */
/*bool Tablero::comprobarGanar()
{
    int comprobar;
    for (int i = filas - 1; i >= 0; i--)
    {
        for (int j = columnas - 1; j >= 0; j--)
        {
            // Si hay una ficha, se puede verificar.
            if (matriz[i][j] != 0)
            {
                // Vertical.
                if (i - 3 >= 0)
                {
                    comprobar = matriz[i][j];
                    // Comprobando las 4 fichas seguidas.
                    if (comprobar == matriz[i - 1][j] && comprobar == matriz[i -
2][j] && comprobar == matriz[i - 3][j])
                    {
                        return true;
                    } // End if
                }     // End if

                // Horizontal.
                if (j - 3 >= 0)
                {
                    comprobar = matriz[i][j];
                    // Comprobando las 4 fichas seguidas.
                    if (comprobar == matriz[i][j - 1] && comprobar ==
matriz[i][j - 2] && comprobar == matriz[i][j - 3])
                    {
                        return true;
                    } // End if
                }     // End if

                // Diagonal izquierda.
                if (i - 3 >= 0 && j - 3 >= 0)
                {
                    comprobar = matriz[i][j];
                    // Comprobando las 4 fichas seguidas.
                    if (comprobar == matriz[i - 1][j - 1] &&
                        comprobar == matriz[i - 2][j - 2] &&
                        comprobar == matriz[i - 3][j - 3])
                    {
                        return true;
                    } // End if
                }     // End if

                // Diagonal derecha.
                if (i - 3 >= 0 && j + 3 < columnas)
                {
                    comprobar = matriz[i][j];
                    // Comprobando las 4 fichas seguidas.
                    if (comprobar == matriz[i - 1][j + 1] &&
                        comprobar == matriz[i - 2][j + 2] &&
                        comprobar == matriz[i - 3][j + 3])
                    {
                        return true;
                    } // End if
                }     // End if
            }         // End if
        }             // End for
    }                 // End for
    return false;
} // End comprobarGanar

/*
 * Este método de tipo booleano de la clase Tablero comprueba
 * si en la partida hay empate ya que recorre la matriz y si
 * encuentra un 0, significa que hay espacio para seguir jugando,
 * por lo que daría falso ya que no hay empate y si el tablero está
 * lleno, implicaría que es verdadero que hay empate ya que en esta
 * ocasión no hubo ningún match anteriormente.
 */
/*bool Tablero::comprobarEmpate()
{
    bool resultado = false;
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            // Si la celda es 0, es falso ya que hay espacio para jugar.
            if (matriz[i][j] == 0)
            {
                resultado = false;
                return resultado;
            }
            // Si no es 0, hay tablero lleno sin victoria, entonces es empate.
            else
            {
                resultado = true;
            } // End if
        }     // End for
    }         // End for
    return resultado;
} // End comprobarEmpate

/*
 * Este método de tipo entero de la clase Tablero recorre la matriz
 * en busca de jugar de una manera más inteligente, es decir, intentando
 * hacer perder a su oponente, si este coloca 3 fichas seguidas, el robot
 * intentará tapar para que no gane.
 */
/*int Tablero::victoriaIA()
{
    int comprobar;
    for (int i = filas - 1; i >= 0; i--)
    {
        for (int j = columnas - 1; j >= 0; j--)
        {
            // Si la celda tiene una ficha, se revisa si hay algún match.
            if (matriz[i][j] != 0)
            {
                // Vertical.
                if (i - 3 >= 0)
                {
                    comprobar = matriz[i][j];
                    // Comprobando las 4 fichas seguidas.
                    if (comprobar == matriz[i - 1][j] && comprobar == matriz[i -
2][j] && matriz[i - 3][j] == 0)
                    {
                        return j;
                    } // End if
                }     // End if

                // Horizontal.
                if (j - 3 >= 0)
                {
                    comprobar = matriz[i][j];
                    // Comprobando las 4 fichas seguidas.
                    if (comprobar == matriz[i][j - 1] && comprobar ==
matriz[i][j - 2] && matriz[i][j - 3] == 0)
                    {
                        return j - 3;
                    }
                    else if (comprobar == matriz[i][j - 1] && matriz[i][j - 2]
== 0 && comprobar == matriz[i][j - 3])
                    {
                        return j - 2;
                    }
                    else if (matriz[i][j - 1] == 0 && comprobar == matriz[i][j -
2] && comprobar == matriz[i][j - 3])
                    {
                        return j - 1;
                    } // End if
                }     // End if

                // Diagonal izquierda.
                if (i - 3 >= 0 && j - 3 >= 0)
                {
                    comprobar = matriz[i][j];
                    // Comprobando las 4 fichas seguidas.
                    if (comprobar == matriz[i - 1][j - 1] &&
                        comprobar == matriz[i - 2][j - 2] && matriz[i - 3][j -
3] == 0)
                    {
                        return j - 3;
                    }
                    else if (comprobar == matriz[i - 1][j - 1] &&
                             matriz[i - 2][j - 2] == 0 &&
                             comprobar == matriz[i - 3][j - 3])
                    {
                        return j - 2;
                    }
                    else if (matriz[i - 1][j - 1] == 0 &&
                             comprobar == matriz[i - 2][j - 2] &&
                             comprobar == matriz[i - 3][j - 3])
                    {
                        return j - 1;
                    } // End if
                }     // End if

                // Diagonal derecha.
                if (i - 3 >= 0 && j + 3 < columnas)
                {
                    comprobar = matriz[i][j];
                    // Comprobando las 4 fichas seguidas.
                    if (comprobar == matriz[i - 1][j + 1] &&
                        comprobar == matriz[i - 2][j + 2] && matriz[i - 3][j +
3] == 0)
                    {
                        return j + 3;
                    }
                    else if (comprobar == matriz[i - 1][j + 1] &&
                             matriz[i - 2][j + 2] == 0 &&
                             comprobar == matriz[i - 3][j + 3])
                    {
                        return j + 2;
                    }
                    else if (matriz[i - 1][j + 1] == 0 &&
                             comprobar == matriz[i - 2][j + 2] &&
                             comprobar == matriz[i - 3][j + 3])
                    {
                        return j + 1;
                    } // End if
                }     // End if
            }         // End if
        }             // End for
    }                 // End for
    return -1;
} // End victoriaIA
*/
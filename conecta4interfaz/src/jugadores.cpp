/*// Incluye bibliotecas:
#include <chrono>
#include <cstring>
#include <iostream>
#include <random>
#include <stdexcept>
#include <thread>
#include <vector>

// Incluye los encabezados:
#include <jugadores.hpp>
#include <tablero.hpp>

using namespace std;

int Jugadores::jugar(int modo, int dificultad)
{
    // Elige quien empieza primero de manera aleatoria.
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> distR(1, 2);
    int jugador = distR(rng);
    cout << "\n El jugador " << jugador << " empieza primero.\n";

    bool victoria = false;
    bool empate = false;
    bool iA = true;

    // Este ciclo es para jugar.
    while (!victoria && !empate)
    {
        tablero.imprimir();
        int columna;
        do
        {
            // Persona 1 vs persona 2.
            if (modo == 1)
            {
                cout << "Jugador " << jugador << ", ingresa el número de columna
(0-"
                     << tablero.obtenerColumnas() - 1 << "): ";
                cin >> columna;
            }
            // Persona vs robot.
            else if (modo == 2)
            {
                // Turno de la persona.
                if (jugador == 1)
                {
                    cout << "Jugador " << jugador << ", ingresa el número de
columna (0-"
                         << tablero.obtenerColumnas() - 1 << "): ";
                    cin >> columna;
                }
                else
                {
                    // Turno de la IA.
                    if (dificultad == 2)
                    {
                        columna = tablero.victoriaIA();
                    }
                    else
                    {
                        columna = -1;
                    } // End if

                    if (columna == -1)
                    {
                        random_device dev;
                        mt19937 rng(dev());
                        uniform_int_distribution<mt19937::result_type> distR(
                            0, tablero.obtenerColumnas() - 1);
                        columna = distR(rng);
                    } // End if
                    cout << "\n La IA ha jugado en la columna: " << columna <<
endl; } // End if
            }
            // Robot 1 vs robot 2.
            else if (modo == 3)
            {
                /*Crea un número aleatorio entre 0 y la cantidad de columnas
menos uno si no se puede hacer una jugada decisiva.*/
/*  if (dificultad == 2)
   {
       columna = tablero.victoriaIA();
   }
   else
   {
       columna = -1;
   } // End if

   if (columna == -1)
   {
       random_device dev;
       mt19937 rng(dev());
       uniform_int_distribution<mt19937::result_type> distR(
           0, tablero.obtenerColumnas() - 1);
       columna = distR(rng);
   } // End if

   // Si la columna seleccionada está vacía...
   if (tablero.columnaLlena(columna) == false)
   {
       // ...espere 2 segundos.
       this_thread::sleep_for(chrono::milliseconds(2000));
       cout << "\n La IA " << jugador
            << " ha jugado en la columna: " << columna << endl;
   } // End if
}     // End if

// Mientras sea una columna dentro del rango o que la columna esté llena.
} while (columna < 0 || columna >= tablero.obtenerColumnas() ||
    tablero.columnaLlena(columna));
// End do-while

// Si se puede colocar la ficha, se comprueba si hay alguna victoria o
// empate.
if (tablero.ponerFichas(columna, jugador))
{
victoria = tablero.comprobarGanar();
empate = tablero.comprobarEmpate();
// Intercala al jugador 1 y al jugador 2.
jugador = (jugador == 1) ? 2 : 1;
} // End if
}     // End while

tablero.imprimir();
jugador = (jugador == 1) ? 2 : 1;

// Si alguien ganó.
if (victoria)
{
cout << "\n ¡Jugador " << jugador << " ha ganado! \n";
return jugador;
}
// Hay empate.
else
{
cout << "\n ¡Empate!" << endl;
return 0;
} // End if
} // End jugar
*/
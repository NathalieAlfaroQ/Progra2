/*// Incluye bibliotecas:
#include <cctype>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

// Incluye encabezados:
#include <jugadores.hpp>
#include <tablero.hpp>

using namespace std;

void Controlador::inicio()
{
  try
  {
    cout << "\n ¡Bienvenido al juego 4 en línea! \n";
    // Inicializo algunas variables:
    primerGane = 0;
    segundoGane = 0;
    jugando = true;

    // Este ciclo es para jugar varias partidas, cada que se finalice la actual.
    while (jugando)
    {
      /* Pregunta el tamaño del tablero, por sus filas y sus columnas,
       * además solicita y comprueba que el usuario digite bien los
       * datos.
       */
/*  bool preguntar = true;
  while (preguntar)
  {
    cout << "\n El tamaño mínimo del tablero debe ser 4x4.\n";
    cout << "\n Ingrese el número de filas: ";
    cin >> filas;
    cout << "\n Ingrese el número de columnas: ";
    cin >> columnas;

    // Se comprueba que el tablero sea mínimo de 4x4, si no hay error.
    if (filas < 4 || columnas < 4)
    {
      throw invalid_argument(
          "Error: El número a digitar debe ser mayor o igual a 4.");
    }
    else
    {
      // Si es falso, digitó bien los datos y no hay que volver a preguntar.
      preguntar = false;
    } // End if
  }   // End while

  /*
   * Pregunta entre los 3 tipos de modo de juego, además se verifica
   * que se ingrese el tipo de dato solicitado y se pregunta qué tipo
   * de dificultad le gustaría jugar.
   */
/* bool seguir = true;
 while (seguir)
 {
   // Guarda el tipo de juego.
   cout << "\n Elija el modo de juego: \n";
   cout << "\n 1: Persona 1 vs Persona 2. \n 2: Persona vs Robot. \n 3: "
           "Robot vs Robot. \n\n";
   cin >> modo;

   // Verifica que la variable modo tenga el valor correcto.
   if (modo != 1 && modo != 2 && modo != 3)
   {
     throw invalid_argument("Error: Solo puede digitar 1, 2 o 3.");
   } // End if

   // Tipo de dificultad con la que desea jugar.
   if (modo == 2 || modo == 3)
   {
     cout << "\n Elija el nivel de dificultad del robot: \n";
     cout << "\n 1: Fácil. \n 2: Difícil. \n";
     cin >> dificultad;

     // Verifica que la variable dificultad tenga el valor correcto.
     if (dificultad != 1 && dificultad != 2)
     {
       throw invalid_argument("Error: Solo puede digitar 1 o 2.");
     } // End if
   }   // End if
   seguir = false;
 } // End while

 // Inicia la partida:
 cout << "\n ¡A jugar! \n";
 Jugadores juego(filas, columnas);

 // Contador de partidas ganadas de los jugadores.
 int ganador = juego.jugar(modo, dificultad);
 if (ganador == 1)
 {
   primerGane++;
 }
 else if (ganador == 2)
 {
   segundoGane++;
 }

 // Se consulta si desea seguir jugando
 cout << "\n Victorias del jugador 1: " << primerGane
      << "\t Victorias del jugador 2: " << segundoGane << endl;
 cout << "\n ¿Desea seguir jugando, sí o no? \n";
 cin >> respuesta;

 // Convertir la cadena a minúsculas
 for (char &caracter : respuesta)
 {
   caracter = tolower(caracter);
 }

 // Verifica que la variable respuesta tenga el valor correcto.
 if (respuesta != "si" && respuesta != "no" && respuesta != "sí")
 {
   throw invalid_argument("Error: Datos inválidos.");
 }
 else if (respuesta == "no")
 {
   jugando = false;
   cout << "\n ¡Gracias por jugar! \n";
 }
} // End while
}
catch (const exception &e)
{
throw invalid_argument("Error: Datos inválidos.");
} // End try_catch principal
}*/

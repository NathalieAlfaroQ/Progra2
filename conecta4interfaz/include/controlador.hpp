/*// Incluye bibliotecas:
#include <cctype>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

// Incluye encabezados:
#include <jugadores.hpp>
#include <tablero.hpp>
#include <wx/wxprec.hpp>

// Encabezado;
#ifndef CONTROLADOR_HPP
#define CONTROLADOR_HPP

using namespace std;

class Controlador
{
public:
    // Declaro variables:
    int filas, columnas, modo, dificultad, primerGane, segundoGane;
    string respuesta;
    bool jugando;

public:
    // Constructor
    Controlador(int filas, int columnas, int modo, int dificultad, int
primerGane, int segundoGane, string respuesta, bool jugando) : filas(filas),
columnas(columnas), modo(modo), dificultad(dificultad), primerGane(primerGane),
segundoGane(segundoGane), respuesta(respuesta), jugando(jugando) {}

    // Metodos:
    void inicio();
};
#endif*/

#include <gtest/gtest.h>
#include <jugadores.hpp>
#include <tablero.hpp>

using namespace std;

TEST(TableroTest, JugarEnColumnaLlenaEsInvalido)
{
    // Crea un tablero de 4 filas y 4 columnas
    Tablero tablero(4, 4);
    ASSERT_EQ(tablero.ponerFichas(0, 1), true);
    ASSERT_EQ(tablero.ponerFichas(0, 2), true);
    ASSERT_EQ(tablero.ponerFichas(0, 1), true);
    ASSERT_EQ(tablero.ponerFichas(0, 2), true);
    ASSERT_EQ(tablero.ponerFichas(0, 1), false);
}

TEST(TableroTest, TableroInvalido)
{
    EXPECT_THROW(
        {
            try
            {
                Tablero tablero(2, 3);
            }
            catch (const invalid_argument &e)
            {
                EXPECT_STREQ(e.what(),
                             "Solo filas y columnas mayores o iguales a 4.");
                throw;
            }
        },
        invalid_argument);
}

TEST(TableroTest, ColumnaInvalida1)
{
    EXPECT_THROW(
        {
            try
            {
                Tablero tablero(4, 4);
                ASSERT_EQ(tablero.columnaLlena(99), false);
            }
            catch (const out_of_range &e)
            {
                EXPECT_STREQ(e.what(), "Error: Columna fuera de rango.");
                throw;
            }
        },
        out_of_range);
}

TEST(TableroTest, ColumnaInvalida2)
{
    EXPECT_THROW(
        {
            try
            {
                Tablero tablero(4, 4);
                ASSERT_EQ(tablero.columnaLlena(-6), false);
            }
            catch (const out_of_range &e)
            {
                EXPECT_STREQ(e.what(), "Error: Columna fuera de rango.");
                throw;
            }
        },
        out_of_range);
}

TEST(TableroTest, ColumnaInvalida3)
{
    Tablero tablero(4, 4);
    EXPECT_THROW(tablero.columnaLlena(-6657.215), out_of_range);
}

TEST(TableroTest, ColumnaVacia)
{
    Tablero tablero(6, 9);
    // Es false porque esta vacio
    ASSERT_EQ(false, tablero.columnaLlena(3));
}

TEST(TableroTest, ColumnaLlena)
{
    Tablero tablero(5, 5);
    tablero.ponerFichas(0, 1);
    ASSERT_EQ(false, tablero.columnaLlena(0));

    tablero.ponerFichas(0, 2);
    ASSERT_EQ(false, tablero.columnaLlena(0));

    tablero.ponerFichas(0, 1);
    ASSERT_EQ(false, tablero.columnaLlena(0));

    tablero.ponerFichas(0, 2);
    ASSERT_EQ(false, tablero.columnaLlena(0));

    tablero.ponerFichas(0, 1);
    ASSERT_EQ(true, tablero.columnaLlena(0));
}

TEST(TableroTest, TableroValido)
{
    Tablero tablero(10, 8);
}

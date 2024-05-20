// tests/end_to_end_test.cc

#include <gtest/gtest.h>
#include <calculadora.hh>
using namespace std;

TEST(EndToEndTest, Calculadora)
{
  istringstream input_stream("15 + 15 * 2\n");
  ostringstream output_stream;
  bool result = ask_user(input_stream, output_stream);
  EXPECT_TRUE(result);
  string expected_output = "Digite una expresión o escriba\"salir\": El resultado es: 45\n";
  EXPECT_EQ(output_stream.str(), expected_output);
}

TEST(EndToEndTest, conParentesis)
{
  // Operador a probar
  istringstream input_stream("(15 + 15) * 2\n");
  ostringstream output_stream;
  // Aplicacion
  bool result = ask_user(input_stream, output_stream);
  // Resultado esperado
  EXPECT_TRUE(result);
  // Verifica la salida esperada
  string expected_output = "Ingrese una expresión o \"salir\": El resultado es: 60\n";
  EXPECT_EQ(output_stream.str(), expected_output);
}

TEST(EndToEndTest, conDivision)
{
  istringstream input_stream("5 / 1\n");
  ostringstream output_stream;
  bool result = ask_user(input_stream, output_stream);
  EXPECT_TRUE(result);
  string expected_output = "Ingrese una expresión o \"salir\": El resultado es: 5\n";
  EXPECT_EQ(output_stream.str(), expected_output);
}

TEST(EndToEndTest, conResta)
{
  istringstream input_stream("25 - 15\n");
  ostringstream output_stream;
  bool result = ask_user(input_stream, output_stream);
  EXPECT_TRUE(result);
  string expected_output = "Ingrese una expresión o \"salir\": El resultado es: 10\n";
  EXPECT_EQ(output_stream.str(), expected_output);
}

TEST(EndToEndTest, conSuma)
{
  istringstream input_stream("1 + 1\n");
  ostringstream output_stream;
  bool result = ask_user(input_stream, output_stream);
  EXPECT_TRUE(result);
  string expected_output = "Ingrese una expresión o \"salir\": El resultado es: 2\n";
  EXPECT_EQ(output_stream.str(), expected_output);
}

TEST(EndToEndTest, datoInvalida)
{
  istringstream input_stream("exit\n");
  ostringstream output_stream;
  bool result = ask_user(input_stream, output_stream);
  EXPECT_FALSE(result);
  string expected_output = "Ingrese una expresión o \"salir\": Saliendo...\n";
  EXPECT_EQ(output_stream.str(), expected_output);
}
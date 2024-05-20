#include <calculadora.hh>
#include <gtest/gtest.h>
using namespace std;

TEST(CalculadoraTest, EmptyExpression)
{
  Calculadora calculadora("");
  EXPECT_TRUE(calculadora.IsValid());
  EXPECT_EQ(calculadora.Resultado(), 0);
}

TEST(CalculadoraTest, Suma1)
{
  Calculadora calculadora("15 + 15");
  EXPECT_TRUE(calculadora.IsValid());
  EXPECT_EQ(calculadora.Resultado(), 30);
}

TEST(CalculadoraTest, pruebaResta)
{
    Calculadora calculadora("55 - 5");
    EXPECT_TRUE(calculadora.IsValid());
    EXPECT_EQ(calculadora.Resultado(), 50);
}

TEST(CalculadoraTest, Multiplicacion1)
{
  Calculadora calculadora("9 * 10");
  EXPECT_TRUE(calculadora.IsValid());
  EXPECT_EQ(calculadora.Resultado(), 90);
}

TEST(CalculadoraTest, Division1)
{
  Calculadora calculadora("12 / 2");
  EXPECT_TRUE(calculadora.IsValid());
  EXPECT_EQ(calculadora.Resultado(), 6);
}

TEST(CalculadoraTest, Parentesis1)
{
  Calculadora calculadora("(8 + 8) * 1");
  EXPECT_TRUE(calculadora.IsValid());
  EXPECT_EQ(calculadora.Resultado(), 16);
}

TEST(CalculadoraTest, AskUser)
{
  // Entrada simulada
  string input = "2 + 2\nexit\n";
  istringstream input_stream(input);
  ostringstream output_stream;

  // Redirigir entrada y salida
  streambuf *original_cin = cin.rdbuf();
  streambuf *original_cout = cout.rdbuf();
  cin.rdbuf(input_stream.rdbuf());
  cout.rdbuf(output_stream.rdbuf());

  // Ejecutamos función con entrada y salida
  bool result = ask_user(cin, cout);

  // Restaurar entrada y salida
  cin.rdbuf(original_cin);
  cout.rdbuf(original_cout);

  // Resultado
  EXPECT_TRUE(result);
}

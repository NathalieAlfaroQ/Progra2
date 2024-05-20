#include <postfijo.hh>
#include <gtest/gtest.h>
using namespace std;

TEST(PostfijoTest, paraSuma)
{
  queue<Token *> cola;
  cola.push(new TokenNumero(0, 0, 5));
  cola.push(new TokenNumero(2, 2, 5));
  cola.push(new TokenOperador(1, 1, '+'));
  Postfijo postfijo(cola);
  EXPECT_EQ(postfijo.Resultado(), 10);
}

TEST(PostfijoTest, paraResta)
{
  queue<Token *> cola;
  cola.push(new TokenNumero(0, 0, 66));
  cola.push(new TokenNumero(2, 2, 30));
  cola.push(new TokenOperador(1, 1, '-'));
  Postfijo postfijo(cola);
  EXPECT_EQ(postfijo.Resultado(), 36);
}

TEST(PostfijoTest, paraMultiplicacion)
{
  queue<Token *> cola;
  cola.push(new TokenNumero(0, 0, 2));
  cola.push(new TokenNumero(2, 2, 5));
  cola.push(new TokenOperador(1, 1, '*'));
  Postfijo postfijo(cola);
  EXPECT_EQ(postfijo.Resultado(), 10);
}

TEST(PostfijoTest, paraDivision)
{
  queue<Token *> cola;
  cola.push(new TokenNumero(0, 0, 5));
  cola.push(new TokenNumero(2, 2, 1));
  cola.push(new TokenOperador(1, 1, '/'));
  Postfijo postfijo(cola);
  EXPECT_EQ(postfijo.Resultado(), 5);
}

TEST(PostfijoTest, DivisionCero)
{
  queue<Token *> cola;
  cola.push(new TokenNumero(0, 0, 10));
  cola.push(new TokenNumero(2, 2, 0));
  cola.push(new TokenOperador(1, 1, '/'));
  Postfijo postfijo(cola);
  EXPECT_FALSE(postfijo.IsValid());
}
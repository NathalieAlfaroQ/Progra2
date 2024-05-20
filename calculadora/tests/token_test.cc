#include <gtest/gtest.h>
#include "token.hh"

TEST(TokenTest, TokenOperador)
{
  // Token de operador a probar
  TokenOperador tokenOperador(55, 92, '+');

  EXPECT_EQ(tokenOperador.operador(), '+');
  EXPECT_TRUE(tokenOperador.IsOperator());
  EXPECT_FALSE(tokenOperador.IsNumber());
  EXPECT_FALSE(tokenOperador.IsLeftParenthesis());
  EXPECT_FALSE(tokenOperador.IsRightParenthesis());
  EXPECT_EQ(tokenOperador.GetPrecedence(), 1);
}

TEST(TokenTest, TokenNumero)
{
  // Para probar token numero
  TokenNumero tokenNumero(6, 7, 89.0);

  EXPECT_EQ(tokenNumero.valor(), 89.0);
  EXPECT_FALSE(tokenNumero.IsOperator());
  EXPECT_TRUE(tokenNumero.IsNumber());
}

TEST(TokenTest, TokendeResta)
{
  TokenOperador tokenOperador(1, 7, '-');

  EXPECT_EQ(tokenOperador.operador(), '-');
  EXPECT_TRUE(tokenOperador.IsOperator());
  EXPECT_FALSE(tokenOperador.IsNumber());
  EXPECT_FALSE(tokenOperador.IsLeftParenthesis());
  EXPECT_FALSE(tokenOperador.IsRightParenthesis());
  EXPECT_EQ(tokenOperador.GetPrecedence(), 1);
}

TEST(TokenTest, TokenNumero2)
{
  TokenNumero tokenNumero(1, 2, 33.4);

  EXPECT_EQ(tokenNumero.valor(), 33.4);
  EXPECT_FALSE(tokenNumero.IsOperator());
  EXPECT_TRUE(tokenNumero.IsNumber());
}

TEST(TokenTest, TokendeMultiplicacion)
{
  TokenOperador tokenOperador(0, 66, '*');

  EXPECT_EQ(tokenOperador.operador(), '*');
  EXPECT_TRUE(tokenOperador.IsOperator());
  EXPECT_FALSE(tokenOperador.IsNumber());
  EXPECT_FALSE(tokenOperador.IsLeftParenthesis());
  EXPECT_FALSE(tokenOperador.IsRightParenthesis());
  EXPECT_EQ(tokenOperador.GetPrecedence(), 2);
}

TEST(TokenTest, TokendeDivision)
{
  TokenOperador tokenOperador(0, 666, '/');

  EXPECT_EQ(tokenOperador.operador(), '/');
  EXPECT_TRUE(tokenOperador.IsOperator());
  EXPECT_FALSE(tokenOperador.IsNumber());
  EXPECT_FALSE(tokenOperador.IsLeftParenthesis());
  EXPECT_FALSE(tokenOperador.IsRightParenthesis());
  EXPECT_EQ(tokenOperador.GetPrecedence(), 2);
}

TEST(TokenTest, TokenPorDefecto)
{
  // Con operador no conocido
  TokenOperador tokenOperador(22, 99, '#');
  EXPECT_EQ(tokenOperador.GetPrecedence(), 0);
}

TEST(TokenTest, ejecucion)
{
  TokenOperador tokenOperador(22, 99, '+');
  EXPECT_EQ(tokenOperador.inicio(), 22);
  EXPECT_EQ(tokenOperador.fin(), 99);
}
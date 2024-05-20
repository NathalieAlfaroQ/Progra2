#include <gtest/gtest.h>
#include <tokenizer.hh>

TEST(TokenizerTest, EmptyString)
{
  Tokenizer tokenizer("");
  EXPECT_FALSE(tokenizer.HasNext());
}

TEST(TokenizerTest, Suma)
{
  Tokenizer tokenizer("+");
  EXPECT_TRUE(tokenizer.HasNext());
  Token *token = tokenizer.Next();
  ASSERT_TRUE(token != nullptr);
  EXPECT_TRUE(token->IsOperator());
  EXPECT_EQ(token->inicio(), 0);
  EXPECT_EQ(token->fin(), 1);
  delete token;
  EXPECT_FALSE(tokenizer.HasNext());
}

TEST(TokenizerTest, Resta)
{
  Tokenizer tokenizer("-");
  EXPECT_TRUE(tokenizer.HasNext());
  Token *token = tokenizer.Next();
  ASSERT_TRUE(token != nullptr);
  EXPECT_TRUE(token->IsOperator());
  EXPECT_EQ(token->inicio(), 0);
  EXPECT_EQ(token->fin(), 1);
  delete token;
  EXPECT_FALSE(tokenizer.HasNext());
}

TEST(TokenizerTest, Multiplicacion)
{
  Tokenizer tokenizer("*");
  EXPECT_TRUE(tokenizer.HasNext());
  Token *token = tokenizer.Next();
  ASSERT_TRUE(token != nullptr);
  EXPECT_TRUE(token->IsOperator());
  EXPECT_EQ(token->inicio(), 0);
  EXPECT_EQ(token->fin(), 1);
  delete token;
  EXPECT_FALSE(tokenizer.HasNext());
}

TEST(TokenizerTest, Division)
{
  Tokenizer tokenizer("/");
  EXPECT_TRUE(tokenizer.HasNext());
  Token *token = tokenizer.Next();
  ASSERT_TRUE(token != nullptr);
  EXPECT_TRUE(token->IsOperator());
  EXPECT_EQ(token->inicio(), 0);
  EXPECT_EQ(token->fin(), 1);
  delete token;
  EXPECT_FALSE(tokenizer.HasNext());
}

TEST(TokenizerTest, ParentesisIzquierdo1)
{
  Tokenizer tokenizer("(");
  EXPECT_TRUE(tokenizer.HasNext());
  Token *token = tokenizer.Next();
  ASSERT_TRUE(token != nullptr);
  EXPECT_TRUE(token->IsOperator());
  EXPECT_EQ(token->inicio(), 0);
  EXPECT_EQ(token->fin(), 1);
  delete token;
  EXPECT_FALSE(tokenizer.HasNext());
}

TEST(TokenizerTest, ParentesisDerecho1)
{
  Tokenizer tokenizer(")");
  EXPECT_TRUE(tokenizer.HasNext());
  Token *token = tokenizer.Next();
  ASSERT_TRUE(token != nullptr);
  EXPECT_TRUE(token->IsOperator());
  EXPECT_EQ(token->inicio(), 0);
  EXPECT_EQ(token->fin(), 1);
  delete token;
  EXPECT_FALSE(tokenizer.HasNext());
}

TEST(TokenizerTest, Num)
{
  Tokenizer tokenizer("64");
  EXPECT_TRUE(tokenizer.HasNext());
  Token *token = tokenizer.Next();
  ASSERT_TRUE(token != nullptr);
  EXPECT_TRUE(token->IsNumber());
  EXPECT_EQ(token->inicio(), 0);
  EXPECT_EQ(token->fin(), 2);
  delete token;
  EXPECT_FALSE(tokenizer.HasNext());
}

TEST(TokenizerTest, Lleno)
{
  Tokenizer tokenizer("159");

  // Primer token es número
  while (tokenizer.HasNext())
  {
    delete tokenizer.Next();
  }

  // Obtener un token extra
  EXPECT_FALSE(tokenizer.HasNext());
  EXPECT_EQ(tokenizer.Next(), nullptr);
  // Mas tokens
  EXPECT_FALSE(tokenizer.HasNext());
  EXPECT_EQ(tokenizer.Next(), nullptr);
}

TEST(TokenizerTest, evitarEspacio)
{
  Tokenizer tokenizer("  55");

  // Comprobar que no tiene espacio
  EXPECT_TRUE(tokenizer.HasNext());
  Token *token = tokenizer.Next();
  ASSERT_TRUE(token != nullptr);
  EXPECT_TRUE(token->IsNumber());
  EXPECT_EQ(token->inicio(), 0);
  EXPECT_EQ(token->fin(), 4);
  delete token;

  // Tokens llenos?
  EXPECT_FALSE(tokenizer.HasNext());
  EXPECT_EQ(tokenizer.Next(), nullptr);
}

TEST(TokenizerTest, decimales)
{
  Tokenizer tokenizer("3.14.15");

  EXPECT_THROW({
    Token *token = tokenizer.Next();
    delete token;
  },
               std::runtime_error);
}

TEST(TokenizerTest, numerosInvalidos)
{
  Tokenizer tokenizer("3$14");

  EXPECT_THROW({
    while (tokenizer.HasNext())
    {
      Token *token = tokenizer.Next();
      delete token;
    }
  },
               std::runtime_error);
}

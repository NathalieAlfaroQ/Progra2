#include <gtest/gtest.h>
#include <shunting_yard.hh>
using namespace std;

class MockTokenizer : public ITokenizer
{
private:
  queue<Token *> tokens;

public:
  MockTokenizer(const vector<Token *> &tokens)
  {
    for (auto token : tokens)
    {
      this->tokens.push(token);
    }
  }

  virtual bool HasNext() const override
  {
    return !tokens.empty();
  }

  virtual Token *Next() override
  {
    Token *token = tokens.front();
    tokens.pop();
    return token;
  }
};

TEST(ShuntingYardTest, EmptyExpression)
{
  MockTokenizer tokenizer({});
  ShuntingYard shunting_yard(tokenizer);
  queue<Token *> postfijo = shunting_yard.ConvertirAPostfijo();

  EXPECT_TRUE(postfijo.empty());
}

TEST(ShuntingYardTest, NumeroToken)
{
  vector<Token *> tokens = {
      new TokenNumero(0, 0, 37.0),
  };

  MockTokenizer tokenizer(tokens);
  ShuntingYard shunting_yard(tokenizer);
  queue<Token *> postfijo = shunting_yard.ConvertirAPostfijo();
  ASSERT_EQ(postfijo.size(), 1);
  EXPECT_TRUE(postfijo.front()->IsNumber());
}

TEST(ShuntingYardTest, Suma2)
{
  vector<Token *> tokens = {
      new TokenOperador(0, 0, '+'),
  };

  MockTokenizer tokenizer(tokens);
  ShuntingYard shunting_yard(tokenizer);
  queue<Token *> postfijo = shunting_yard.ConvertirAPostfijo();
  ASSERT_EQ(postfijo.size(), 1);
  EXPECT_TRUE(postfijo.front()->IsOperator());
}

TEST(ShuntingYardTest, Resta2)
{
  vector<Token *> tokens = {
      new TokenOperador(0, 0, '-'),
  };

  MockTokenizer tokenizer(tokens);
  ShuntingYard shunting_yard(tokenizer);
  queue<Token *> postfijo = shunting_yard.ConvertirAPostfijo();
  ASSERT_EQ(postfijo.size(), 1);
  EXPECT_TRUE(postfijo.front()->IsOperator());
}

TEST(ShuntingYardTest, Multiplicacion2)
{
  vector<Token *> tokens = {
      new TokenOperador(0, 0, '*'),
  };

  MockTokenizer tokenizer(tokens);
  ShuntingYard shunting_yard(tokenizer);
  queue<Token *> postfijo = shunting_yard.ConvertirAPostfijo();
  ASSERT_EQ(postfijo.size(), 1);
  EXPECT_TRUE(postfijo.front()->IsOperator());
}

TEST(ShuntingYardTest, Division2)
{
  vector<Token *> tokens = {
      new TokenOperador(0, 0, '/'),
  };

  MockTokenizer tokenizer(tokens);
  ShuntingYard shunting_yard(tokenizer);
  queue<Token *> postfijo = shunting_yard.ConvertirAPostfijo();
  ASSERT_EQ(postfijo.size(), 1);
  EXPECT_TRUE(postfijo.front()->IsOperator());
}

TEST(ShuntingYardTest, ParentesisIzquierdo)
{
  vector<Token *> tokens = {
      new TokenOperador(0, 0, '('),
  };

  MockTokenizer tokenizer(tokens);
  ShuntingYard shunting_yard(tokenizer);
  queue<Token *> postfijo = shunting_yard.ConvertirAPostfijo();
  ASSERT_EQ(postfijo.size(), 1);
  EXPECT_TRUE(postfijo.front()->IsOperator());
}

TEST(ShuntingYardTest, SingleOperatorParenDer)
{
  std::vector<Token *> tokens = {
      new TokenOperador(0, 0, ')'), // Token de paréntesis derecho
  };
  MockTokenizer tokenizer(tokens);
  ShuntingYard shunting_yard(tokenizer);

  // Utiliza un bloque try-catch para manejar la excepción
  try
  {
    std::queue<Token *> postfijo = shunting_yard.ConvertirAPostfijo();
    // Si la excepción no se lanza, el test falla
    FAIL() << "Expected exception not thrown";
  }
  catch (const std::runtime_error &e)
  {
    // Verifica que la excepción tiene el mensaje esperado
    EXPECT_STREQ("Problema con los paréntesis", e.what());
  }
}

TEST(ShuntingYardTest, StackHandlingDerecho)
{
  MockTokenizer tokenizer({new TokenOperador(0, 0, ')')});

  ShuntingYard shunting_yard(tokenizer);
  ASSERT_THROW(shunting_yard.ConvertirAPostfijo(), runtime_error);
}

TEST(ShuntingYardTest, HandlingInOutputQueue)
{
  vector<Token *> tokens = {
      new TokenOperador(0, 0, '('),
      new TokenNumero(0, 0, 22.0),
      new TokenOperador(0, 0, '+'),
      new TokenNumero(0, 0, 77.0),
      new TokenOperador(0, 0, ')'),
  };

  MockTokenizer tokenizer(tokens);
  ShuntingYard shunting_yard(tokenizer);
  queue<Token *> postfijo = shunting_yard.ConvertirAPostfijo();
  ASSERT_EQ(postfijo.size(), 3);
  EXPECT_TRUE(postfijo.front()->IsNumber());
  postfijo.pop();
  EXPECT_TRUE(postfijo.front()->IsNumber());
  postfijo.pop();
  EXPECT_TRUE(postfijo.front()->IsOperator());
}

TEST(ShuntingYardTest, ParentesisiIncompleto)
{
  vector<Token *> tokens = {
      new TokenOperador(0, 0, '+'),
      new TokenOperador(0, 0, ')'),
  };

  MockTokenizer tokenizer(tokens);
  ShuntingYard shunting_yard(tokenizer);

  try
  {
    queue<Token *> postfijo = shunting_yard.ConvertirAPostfijo();
    FAIL() << "Expected exception not thrown";
  }
  catch (const runtime_error &e)
  {
    EXPECT_STREQ("Problema con los paréntesis", e.what());
  }
}
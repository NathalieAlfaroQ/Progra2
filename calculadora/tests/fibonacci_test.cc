#include <fibonacci.hh>
#include <gtest/gtest.h>

TEST(CalculadoraTest, Suma)
{
  EXPECT_EQ(2, 1 + 1);
}

TEST(FibonacciTest, Caso0)
{
  EXPECT_EQ(0, fibonacci(0));
}

TEST(FibonacciTest, Caso1)
{
  EXPECT_EQ(1, fibonacci(1));
}

TEST(FibonacciTest, Caso5)
{
  EXPECT_EQ(5, fibonacci(5));
}

TEST(FibonacciTest, CasoNegativo)
{
  // EXPECT_THROW(fibonacci(-1), std::invalid_argument);

  EXPECT_THROW({
    try
    {
      fibonacci(-1);
    }
    catch (std::invalid_argument &e)
    {
      EXPECT_STREQ("Negative arguments not implemented", e.what());
      throw;
    }
  },
               std::invalid_argument);
}
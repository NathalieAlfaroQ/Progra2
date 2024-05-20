#include <BST.hh>
#include <gtest/gtest.h>

TEST(ArbolBinario, Insertar)
{
  BST<int, int> arbol(5, 5);
  arbol.Insert(3, 3);
  arbol.Insert(7, 7);
  arbol.Insert(2, 2);
  arbol.Insert(4, 4);
  arbol.Insert(6, 6);
  arbol.Insert(8, 8);
  EXPECT_EQ(7, arbol.count());
}

TEST(ArbolBinario, InsertarRepetidos)
{
  BST<int, int> arbol(5, 51);
  arbol.Insert(3, 31);
  arbol.Insert(3, 32);
  arbol.Insert(3, 33);
  arbol.Insert(4, 41);
  arbol.Insert(4, 42);
  arbol.Insert(4, 43);
  EXPECT_EQ(3, arbol.count());
}

TEST(ArbolBinario, InsertarRepetidosActualizaViejos)
{
  BST<int, int> arbol(5, 51);
  arbol.Insert(3, 31);
  EXPECT_EQ(31, arbol.Get(3));
  arbol.Insert(3, 32);
  EXPECT_EQ(32, arbol.Get(3));
  arbol.Insert(3, 33);
  EXPECT_EQ(33, arbol.Get(3));

  arbol.Insert(4, 41);
  EXPECT_EQ(41, arbol.Get(4));

  arbol.Insert(4, 42);
  EXPECT_EQ(42, arbol.Get(4));

  arbol.Insert(4, 43);
  EXPECT_EQ(43, arbol.Get(4));
}

TEST(ArbolBinario, GetTiraExcepcion)
{
  BST<int, int> arbol(5, 51);
  arbol.Insert(3, 31);
  arbol.Insert(7, 71);
  EXPECT_THROW(arbol.Get(2), std::invalid_argument);
  EXPECT_THROW(arbol.Get(8), std::invalid_argument);
}

TEST(ArbolBinario, Contiene)
{
  // Crear arbol BST
  BST<int, int> arbol(10, 20);

  // Insertar elementos
  arbol.Insert(2, 200);
  arbol.Insert(8, 800);
  arbol.Insert(5, 500);
  arbol.Insert(9, 900);

  // Verificar que los elementos existan
  EXPECT_TRUE(arbol.Contains(10));
  EXPECT_TRUE(arbol.Contains(2));
  EXPECT_TRUE(arbol.Contains(9));
  EXPECT_TRUE(arbol.Contains(5));

  // Verificar que los elementos no existan
  EXPECT_FALSE(arbol.Contains(11));
  EXPECT_FALSE(arbol.Contains(80));
  EXPECT_FALSE(arbol.Contains(6));
  EXPECT_FALSE(arbol.Contains(1));
}
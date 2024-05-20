#include <gtest/gtest.h>
#include <BST.hh>
using namespace std;

TEST(BSTTest, insertarNodoValido)
{
  BST *arbolPrueba = new BST();
  arbolPrueba->insertarNodo(1);
  ASSERT_EQ(arbolPrueba->contieneValor(1), true);
}

TEST(BSTTest, insertarNodoValido1)
{
  BST *arbolPrueba = new BST();
  arbolPrueba->insertarNodo(100);
  ASSERT_EQ(arbolPrueba->contieneValor(100), true);
}

TEST(BSTTest, insertarNodoValido2)
{
  BST *arbolPrueba = new BST();
  arbolPrueba->insertarNodo(-5);
  ASSERT_EQ(arbolPrueba->contieneValor(-5), true);
}

TEST(BSTTest, insertarNodoInvalido)
{
  BST *arbolPrueba = new BST();
  arbolPrueba->insertarNodo(3.14);
  ASSERT_EQ(arbolPrueba->contieneValor(3.14), false);
}

TEST(BSTTest, insertarNodoInvalido1)
{
  BST *arbolPrueba = new BST();
  arbolPrueba->insertarNodo(-3.14);
  ASSERT_EQ(arbolPrueba->contieneValor(-3.14), false);
}

TEST(BSTTest, insertarNodoRecursivoValido)
{
  BST *arbolPrueba = new BST();
  arbolPrueba->insertarNodoRecursivo(arbolPrueba->raiz, 33);
  ASSERT_EQ(arbolPrueba->contieneValor(33), true);
}

TEST(BSTTest, insertarNodoRecursivoInvalido)
{
  BST *arbolPrueba = new BST();
  arbolPrueba->insertarNodoRecursivo(arbolPrueba->raiz, 33.33);
  ASSERT_EQ(arbolPrueba->contieneValor(33.33), false);
}

#ifndef ITREE_HH
#define ITREE_HH

#include <cstddef>

template <typename TK, typename TV>
class ITree
{
  virtual void Insert(TK clave, TV valor) = 0;
  virtual bool Contains(TK clave) = 0;
  virtual TV Get(TK clave) = 0;
  virtual size_t count() = 0;
};
#endif
#ifndef BST_HH
#define BST_HH

#include <ITree.hh>
#include <stdexcept>

template <typename TK, typename TV>
class BST : public ITree<TK, TV>
{
private:
  TK clave_;
  TV valor_;
  BST *left_ = nullptr;
  BST *right_ = nullptr;

public:
  BST(TK clave, TV valor)
      : clave_(clave), valor_(valor)
  {
  }

  void Insert(TK clave, TV valor)
  {
    BST<TK, TV> *current = this;
    while (true)
    {
      if (clave < current->clave_)
      {
        if (current->left_ == nullptr)
        {
          current->left_ = new BST<TK, TV>(clave, valor);
          break;
        }
        else
        {
          current = current->left_;
        }
      }
      else if (clave > current->clave_)
      {
        if (current->right_ == nullptr)
        {
          current->right_ = new BST<TK, TV>(clave, valor);
          break;
        }
        else
        {
          current = current->right_;
        }
      }
      else
      {
        current->valor_ = valor;
        break;
      }
    }
  }

  bool Contains(TK clave)
  {
    BST<TK, TV> *current = this;
    while (current != nullptr)
    {
      if (clave < current->clave_)
      {
        current = current->left_;
      }
      else if (clave > current->clave_)
      {
        current = current->right_;
      }
      else
      {
        return true;
      }
    }
    return false;
  }

  TV Get(TK clave)
  {
    BST<TK, TV> *current = this;
    while (current != nullptr)
    {
      if (clave < current->clave_)
      {
        current = current->left_;
      }
      else if (clave > current->clave_)
      {
        current = current->right_;
      }
      else
      {
        return current->valor_;
      }
    }
    throw std::invalid_argument("Key not found");
  }

  size_t count()
  {
    size_t count = 1;
    if (left_ != nullptr)
    {
      count += left_->count();
    }
    if (right_ != nullptr)
    {
      count += right_->count();
    }
    return count;
  }
};
#endif>
#ifndef TOKEN_HH
#define TOKEN_HH

#include <string>

// Tipos de tokens
enum TipoToken
{
  Numero,
  Operador,
};

class Token
{
protected:
  size_t inicio_;
  size_t fin_;
  Token(size_t inicio, size_t fin);

public:
  size_t inicio() const;
  size_t fin() const;
  virtual bool IsOperator() const = 0;
  virtual bool IsNumber() const = 0;
};

class TokenNumero : public Token
{
public:
  TokenNumero(size_t inicio, size_t fin, double valor);
  double valor() const;

  bool IsOperator() const override;
  bool IsNumber() const override;

private:
  double valor_;
};

class TokenOperador : public Token
{
public:
  TokenOperador(size_t inicio, size_t fin, char operador);
  char operador() const;

  bool IsOperator() const override;
  bool IsNumber() const override;

  int GetPrecedence() const;
  bool IsLeftParenthesis() const;
  bool IsRightParenthesis() const;

private:
  char operador_;
};

#endif

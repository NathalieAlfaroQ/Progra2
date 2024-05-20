#include <tokenizer.hh>

Tokenizer::Tokenizer(const std::string &text)
    : text_(text), position(0)
{
}

bool Tokenizer::HasNext() const
{
  return position < text_.size();
}

Token *Tokenizer::Next()
{
  size_t last_token_position = position;

  if (position >= text_.size())
  {
    return nullptr;
  }

  // Saltamos los espacios en blanco
  while (position < text_.size() && text_[position] == ' ')
  {
    position++;
  }

  // Revisamos si es un operador
  char c = text_[position];
  switch (c)
  {
  case '+':
    position++;
    return new TokenOperador(last_token_position, position, c);
  case '-':
    position++;
    return new TokenOperador(last_token_position, position, c);
  case '*':
    position++;
    return new TokenOperador(last_token_position, position, c);
  case '/':
    position++;
    return new TokenOperador(last_token_position, position, c);
  case '(':
    position++;
    return new TokenOperador(last_token_position, position, c);
  case ')':
    position++;
    return new TokenOperador(last_token_position, position, c);
  }

  // Revisamos si es un número
  double valor = 0;
  double multiplicador = 1;
  bool decimal = false;
  bool valido = false;
  while (position < text_.size() && text_[position] >= '0' && text_[position] <= '9' || text_[position] == '.')
  {
    valido = true;
    if (text_[position] == '.')
    {
      if (decimal)
      {
        throw std::runtime_error("Número mal formado: no puede haber "
                                 "más de un punto decimal");
      }
      else
      {
        decimal = true;
      }
    }
    else
    {
      if (decimal)
      {
        multiplicador /= 10;
        valor += (text_[position] - 0) * multiplicador;
      }
      else
      {
        valor = valor * 10 + (text_[position] - '0');
      }
    }
    position++;
  }

  if (!valido)
  {
    throw std::runtime_error(
        "Número mal formado: se encontró un caracter inválido");
  }

  return new TokenNumero(last_token_position, position, valor);
}
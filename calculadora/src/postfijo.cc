#include <postfijo.hh>
#include <stack>

Postfijo::Postfijo(std::queue<Token *> cola)
    : cola(cola), error(""), valid(true), resultado(0)
{
  Evaluar();
}

std::string Postfijo::Error() const
{
  return error;
}

bool Postfijo::IsValid() const
{
  return valid;
}

double Postfijo::Resultado() const
{
  return resultado;
}

void Postfijo::Evaluar()
{
  std::stack<double> pila;

  while (!cola.empty())
  {
    Token *token = cola.front();
    cola.pop();
    if (token->IsNumber())
    {
      auto num = static_cast<TokenNumero *>(token);
      pila.push(num->valor());
    }
    else if (token->IsOperator())
    {
      auto operatorToken = static_cast<TokenOperador *>(token);
      if (pila.size() < 2)
      {
        error = "Error: faltan operandos";
        valid = false;
        return;
      }
      double op2 = pila.top();
      pila.pop();
      double op1 = pila.top();
      pila.pop();
      double res = 0;
      switch (operatorToken->operador())
      {
      case '+':
        res = op1 + op2;
        break;
      case '-':
        res = op1 - op2;
        break;
      case '*':
        res = op1 * op2;
        break;
      case '/':
        if (op2 == 0)
        {
          error = "Error: división por cero";
          valid = false;
          return;
        }

        res = op1 / op2;
        break;
      }
      pila.push(res);
    }
  }

  if (pila.size() != 1)
  {
    error = "Error: sobran operandos";
    valid = false;
    return;
  }

  resultado = pila.top();
}
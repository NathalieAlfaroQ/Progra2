#ifndef CALCULADORA_HH
#define CALCULADORA_HH

#include <iostream>
#include <string>

bool ask_user(std::istream &in, std::ostream &out);

class Calculadora
{
private:
  std::string expresion;
  std::string error;
  double resultado;
  void Evaluar();

public:
  Calculadora(std::string expresion);
  double Resultado() const;
  std::string Error() const;
  bool IsValid() const;
};
#endif
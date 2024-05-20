#ifndef POSTFIJO_HH
#define POSTFIJO_HH

#include <queue>
#include <string>

#include <token.hh>

class Postfijo
{
private:
  std::queue<Token *> cola;
  std::string error;
  bool valid;
  double resultado;
  void Evaluar();

public:
  Postfijo(std::queue<Token *> cola);
  std::string Error() const;
  bool IsValid() const;
  double Resultado() const;
};

#endif // POSTFIJO_HH

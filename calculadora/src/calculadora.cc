#include <algorithm>
#include <calculadora.hh>
#include <postfijo.hh>
#include <shunting_yard.hh>
#include <tokenizer.hh>

bool ask_user(std::istream &in, std::ostream &out)
{
  std::string expresion;
  out << "Ingrese una expresión o escriba \"salir\": ";
  getline(in, expresion);

  // Convertir expresion a minúsculas
  std::transform(expresion.begin(), expresion.end(), expresion.begin(), ::tolower);

  if (expresion == "salir")
  {
    out << "Saliendo..." << std::endl;
    return false;
  }

  Calculadora calculadora(expresion);
  if (calculadora.IsValid())
  {
    out << "El resultado es: " << calculadora.Resultado() << std::endl;
  }
  else
  {
    out << "Error: " << calculadora.Error() << std::endl;
  }
  return true;
}

Calculadora::Calculadora(std::string expresion)
    : expresion(expresion), error(""), resultado(0)
{
  Evaluar();
}

double Calculadora::Resultado() const
{
  return resultado;
}

std::string Calculadora::Error() const
{
  return error;
}

bool Calculadora::IsValid() const
{
  return error == "";
}

void Calculadora::Evaluar()
{
  try
  {
    // Primero se tokeniza la expresion
    Tokenizer tokenizer(expresion);

    // Se convierte a postfijo
    ShuntingYard shuntingYard(tokenizer);
    auto cola = shuntingYard.ConvertirAPostfijo();

    // Evaluamos la expresión en postfijo
    Postfijo postfijo(cola);

    // Resultado
    resultado = postfijo.Resultado();
  }
  catch (std::exception &e)
  {
    error = "Error en evaluacion de expresion";
    return;
  }
}
#include <algorithm>
#include <calculadora.hh>
#include <iostream>
#include <string>

bool ask_user(std::istream &in, std::ostream &out);

int main()
{
  std::cout << "Calculadora" << std::endl;
  std::cout << "Esta calculadora permite evaluar expresiones. Para salir simplemente inserte una cadena vacía" << std::endl;

  while (ask_user(std::cin, std::cout))
  {
  };

  return 0;
}

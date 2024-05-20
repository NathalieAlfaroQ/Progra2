#ifndef FIBONACCI_HH
#define FIBONACCI_HH >

#include <stdexcept>

int fibonacci(int n)
{
  if (n < 0)
  {
    throw std::invalid_argument("Negative arguments not implemented");
  }

  switch (n)
  {
  case 0:
    return 0;
  case 1:
    return 1;
  default:
    return fibonacci(n - 1) + fibonacci(n - 2);
  }
}
#endif
#include<iostream>

constexpr int factorial(int n)
{
    return n <= 1 ? 1 : (n * factorial(n - 1));
}

int
main()
{
  constexpr int duh = 50 + 1;
  
  std::cout << duh << std::endl;
  std::cout << factorial(5) << std::endl;
}


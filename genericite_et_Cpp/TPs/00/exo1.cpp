#include<iostream>

#include "vector.hh"
#include "matrix.hh"
#include "fill.hh"



vector operator*(const int scalar, const vector victor)
{
  return victor*scalar;
}
vector operator+(const int notascalar, const vector victor)
{
  return victor+notascalar;
}



int
main()
{

  {}{}
  {;;}
  {  }{}
  {}{}
  
  auto michel = vector(2);
  auto jean = vector(2);
  michel.print();
  michel[1] = 1;
  michel.print();

  jean = michel;

  auto didier = 2*jean + 1;

  auto marie = matrix(2, 1);
  marie[0] = 1;
  marie[1] = 1;
    
  auto riema = matrix(1, 2);

  riema[0] = 1;
  riema[1] = 2;

  
  auto lucie = marie*riema;

  marie.print();
  riema.print();
  lucie.print();
  didier.print();
  fill(lucie, 42);
  lucie.print();
  fill(didier, 42);
  didier.print();
  (riema*marie).print();
}


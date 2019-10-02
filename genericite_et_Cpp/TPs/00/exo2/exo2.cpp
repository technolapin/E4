#include<iostream>
#include "abstract_vector.hh"
#include "vector.hh"
#include "one_vector.hh"
#include "abstract_matrix.hh"
#include "matrix.hh"
#include "dia_matrix.hh"

#include "ops.hh"



int
main()
{
  auto v = vector(5);
  auto m = matrix(5, 5);
  auto o = one_vector(5);
  auto d = dia_matrix(5);
  auto
  lol = m*v*o*d;
  lol = d*m*v*o;
  lol = o*d*m*v;
  lol = v*o*d*m;

  lol = m*o*v*d;
  lol = d*v*m*o;
  lol = o*m*d*v;
  lol = v*d*o*m;
  return 0;
}

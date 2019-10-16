#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <optional>
#include <cassert>

#include "structs_generiques.hh"
#include "structs_generiques.cc"




#include "tests.cc"


int
main()
{
  //test_structs();
  //test_map();
  test_generics();
  test_ndim_map();
  test_masked_box();
  return 0;
}

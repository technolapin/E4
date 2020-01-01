#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <optional>
#include <cassert>


#include "point.hh"
#include "box.hh"
#include "box_iterator.hh"
#include "ngh_iterator.hh"
#include "image.hh"
#include "structs_generiques.hh"
#include "structs_generiques.cc"
#include "distance_map.cc"

#include "tests.cc"


int
main()
{
  test_generics();
  test_ndim_map();
  test_masked_box();
  test_partial();
  return 0;
}

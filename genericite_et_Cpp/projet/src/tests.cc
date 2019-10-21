#pragma once

void
test_generics()
{
  auto p1 = NPoint<3>({2, 4, 8});
  auto p2 = NPoint<3>({0, 0, 0});
  auto p3 = NPoint<3>({0, 2, 3});
  assert(p2 < p1);
  assert(p2 <= p1);
  assert(p3 < p1);
  assert(p3 <= p1);
  assert(p2 < p3);
  assert(p2 <= p3);

  auto box = NBox<3>(p2, p1);

  assert(!box.within(p1));
  assert(box.within(p2));
  assert(box.within(p3));
  auto pmin = box.get_min();
  pmin.coords[0] = -4;
  assert(pmin.coords[0] != box.get_min().coords[0]);

  auto iter = NBoxIterator<3>(box);
  iter.start();
  assert(iter.is_valid());
  auto ngh_iter = NNghIterator<3>(box);
  for(ngh_iter.start(p3); ngh_iter.is_valid(); ngh_iter.next())
  {
    auto pt = ngh_iter.value();
    for (int i = 0; i < 3; i++)
      std::cout <<  pt.coords[i] << " ";
    std::cout << std::endl;
  }

  auto img = NImage<3, int>(box);
  img.set_pixel(p3, 8);
  assert(img.get_pixel(p3)==8);
}

template<typename T, typename Box>
void
print2d(NImage<2, T, Box> &img,
	NPoint<2> &dims)
{
  for (int j = 0; j < dims.coords[1]; j++)
  {
    for(int i = 0; i < dims.coords[0]; i++)
    {
      auto pix = img.get_pixel(NPoint<2>({i,j}));
      if (pix.has_value())
	std::cout << pix.value() << " "; 
      else
	std::cout << "· ";
    }
    std::cout << std::endl;
  }  
};


void
test_ndim_map()
{

  const int dim = 2;
  auto dims = NPoint<dim>({4, 6});
  auto box = NBox<dim>(NPoint<dim>::zero(), dims);
  auto img = NImage<dim, unsigned>(box);
  img.set_pixel(NPoint<dim>({0, 0}), 1);
  auto map = distance_map(img);

  print2d(img, dims); 
  std::cout << std::endl;
  print2d(map, dims);

}

void
test_masked_box()
{
  const int dim = 2;

  auto dims = NPoint<dim>({8, 8});
  auto box = NBox<dim>(NPoint<dim>::zero(), dims);
  auto mask = NImage<dim, bool>(box);

  mask.set_pixel(NPoint<dim>({0, 0}), true);
  mask.set_pixel(NPoint<dim>({0, 1}), true);
  mask.set_pixel(NPoint<dim>({0, 2}), true);
  mask.set_pixel(NPoint<dim>({1, 2}), true);
  mask.set_pixel(NPoint<dim>({2, 2}), true);
  mask.set_pixel(NPoint<dim>({2, 3}), true);
  mask.set_pixel(NPoint<dim>({1, 0}), true);
  mask.set_pixel(NPoint<dim>({2, 0}), true);


  mask.set_pixel(NPoint<dim>({3, 0}), true);
  mask.set_pixel(NPoint<dim>({4, 0}), true);

  mask.set_pixel(NPoint<dim>({3, 3}), true);
  mask.set_pixel(NPoint<dim>({4, 3}), true);
  mask.set_pixel(NPoint<dim>({4, 2}), true);

  //mask.set_pixel(NPoint<dim>({4, 1}), true);

  
  auto masked_box = NMaskedBox<dim>(mask);

  auto img = NImage<dim, unsigned, NMaskedBox<dim>>(masked_box); 
  img.set_pixel(NPoint<dim>({0, 0}), 1);

  std::cout << "img" << std::endl;
  print2d(img, dims);
  auto map = distance_map(img);
  std::cout << std::endl << "mask"<<std::endl;
  print2d(mask, dims); 
  std::cout << std::endl << "map"<<std::endl;
  print2d(map, dims);

  
  assert(masked_box.within(NPoint<dim>({0,0})));
  
}

template<typename T, typename Box>
void
add_pixel_sequence(NImage<2, T, Box>* img,
		   std::vector<T> values)
{
  auto dims = img->get_box()->get_max();
  auto box = NBox<2>(NPoint<2>::zero(), dims);
  auto iter = NBoxIterator<2>(box);
  
  
  for (iter.start();
       iter.is_valid() && iter.value().to_index(dims) < values.size();
       iter.next())
  {
    img->set_pixel(iter.value(), values[iter.value().to_index(dims)]);
  }
  
  
}

void
test_partial()
{
  const int dim = 2;
  using partial_box2d = NMaskedBox<dim>;
  using partial_image2d = NImage<dim, unsigned, partial_box2d>;
  using Point = NPoint<dim>;
  
  auto dims = Point({5, 6});

  auto part_box = partial_box2d(dims);
  add_pixel_sequence(part_box.get_mask(),
		     std::vector<bool>({1, 1, 1, 1, 0,
					0, 0, 0, 1, 0,
					0, 1, 1, 1, 0,
					0, 1, 0, 1, 0,
					1, 1, 0, 0, 0,
					0, 1, 1, 1, 1
		       })
		     );
  auto part_img = partial_image2d(part_box);

  std::cout << std::endl;
  print2d(part_img, dims);
  add_pixel_sequence(&part_img,
		     std::vector<unsigned>({1})
		     );
  std::cout << std::endl;
  print2d(part_img, dims);
  
  auto map = distance_map(part_img);
  std::cout << std::endl;
  print2d(map, dims);
  
}

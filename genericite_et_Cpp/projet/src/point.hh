#pragma once

template<int dim>
struct NPoint
{
  std::array<int, dim> coords;

  int
  to_index(NPoint<dim> dims)
  {
    int index = 0;
    int size = 1;
    for (int i = 0; i < dim; i++)
      {
	index += this->coords[i]*size;
	size *= dims.coords[i];
      }
    return index;

  }


  int
  product() const
  {
    int size = 1;
    for (int i = 0; i < dim; i++)
      {
	size *= this->coords[i];
      }
    return size;

  }

  static NPoint<dim>
  zero()
  {
    auto p = NPoint<dim>();
    for (int i = 0; i < dim; i++)
      p.coords[i] = 0;
    return p;
  }
};



template<int dim>
NPoint<dim>
operator-(NPoint<dim> pa, NPoint<dim> pb)
{
  auto pc = NPoint<dim>();
  for (int i = 0; i < dim; ++i)
    pc.coords[i] = pa.coords[i] + pb.coords[i];
  return pc;
}


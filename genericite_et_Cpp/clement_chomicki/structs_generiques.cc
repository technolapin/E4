template<int dim>
bool
operator<=(NPoint<dim> pa, NPoint<dim> pb)
{
  for (int i = 0; i < dim; i++)
    if (pa.coords[i] > pb.coords[i])
      return false;
  return true;
}

template<int dim>
bool
operator<(NPoint<dim> pa, NPoint<dim> pb)
{
  return !(pb <= pa);
}


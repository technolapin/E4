#pragma once
template<int dim, typename Box = NBox<dim>>
class NBoxIterator
{
  using Point = NPoint<dim>;

private:
  Box box;
  Point current;
  
public:
  NBoxIterator(const Box& box):
    box(box)
  {}
  
  void
  start()
  {
    this->current = this->box.get_min();
  }

  bool
  is_valid() const
  {
    return this->box.within(this->current);
  }
  
  void
  next()
  {
    auto limit = this->box.get_max();
    for (int i = 0; i < dim; i++)
    {
      if (this->current.coords[i]+1 < limit.coords[i])
      {
	++this->current.coords[i];
	if (!this->box.within(this->current))
	  this->next();
	// ai dû rajouté ça pour le cas où on un un cache
	// probablement moyen d'arranger ça plus tard avec
	// des templates
	return;
      }
      else
      {
	this->current.coords[i] = 0;
      }
    }
    this->current = limit;
    // atteint quand toutes les coords sont maxées
}

  Point
  value() const
  {
    return this->current;
  }
  
};

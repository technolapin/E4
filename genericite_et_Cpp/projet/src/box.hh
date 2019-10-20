#pragma once


template<int dim>
class NBox
{
  using Point = NPoint<dim>;
  
private:
  Point p_min;
  Point p_max;
  
public:
  NBox(Point p_min,
       Point p_max):
    p_min(p_min),
    p_max(p_max){}

  bool
  within(Point pt) const
  {
    return this->p_min <= pt && pt < this->p_max;
  }
  
  Point
  get_min() const
  {
    return this->p_min;
  }

  Point
  get_max() const
  {
    return this->p_max;
  }
  
};


#pragma once

template<int dim, typename Box = NBox<dim>>
class NNghIterator
{
  using Point = NPoint<dim>;

private:
  std::vector<Point> neighborhood;
  std::vector<Point>::iterator iterator;
  Box box;
  
public:
  NNghIterator(const Box& box):
    neighborhood(std::vector<Point>()),
    box(box)
  {}
  

  void
  start(const Point& cell)
  {
    this->neighborhood.clear();
    Point left, right;
    for (int i = 0; i < dim; i++)
    {
      left = cell;
      right = cell;
      --left.coords[i];
      ++right.coords[i];
      if (this->box.within(left))
	this->neighborhood.push_back(left);
      if (this->box.within(right))
	this->neighborhood.push_back(right);
    }

      this->iterator = this->neighborhood.begin();

  }

  bool
  is_valid()
  {
    return this->iterator != this->neighborhood.end();
  }

  void
  next()
  {
    ++this->iterator;
  }

  Point
  value()
  {
    return *(this->iterator);
  }

};

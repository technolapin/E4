#pragma once


template<int dim,
	 typename T,
	 typename Box = NBox<dim>>
class NImage
{
  using Point = NPoint<dim>;
  using BoxIterator = NBoxIterator<dim, Box>;
  using NghIterator = NNghIterator<dim, Box>;

private:
  Point dims;
  Box box;
  std::vector<T> data;

public:
  NImage(const Point dims):
    dims(dims),
    box(Point::zero(), dims),
    data(std::vector<T>(dims.product()))
  {}
  
  NImage(const Box box):
    dims(box.get_max() - box.get_min()),
    box(box),
    data(std::vector<T>(dims.product()))
  {}

  const Box*
  get_box() const
  {
    return &this->box;
  }
  
  std::optional<T>
  get_pixel(Point pt) const
  {
    if (this->box.within(pt))
    {
      return this->data[pt.to_index(this->dims)];
    }
    else
    {
      return {};
    }

  }
  
  void
  set_pixel(Point pt, T val)
  {
    if (this->box.within(pt))
    {
      this->data[pt.to_index(this->dims)] = val;
    }    
  }



  BoxIterator
  iterator() const
  {
    return BoxIterator(this->box);
  }

  NghIterator
  neighboor_iterator() const
  {
    return NghIterator(this->box);
  }

};

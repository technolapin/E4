template<int dim>
class NMaskedBox
{
  using Point = NPoint<dim>;
  using Box = NBox<dim>;
  using Mask = NImage<dim, bool>;
  
private:
  Mask mask;
  
public:
  NMaskedBox(Point dims):
    mask(Mask(dims))
  {}
  
  NMaskedBox(Mask mask):
    mask(mask)
  {}

  bool
  within(Point pt) const
  {
    auto pix = this->mask.get_pixel(pt);
    return pix.has_value() && pix.value();
  }
  
  Point
  get_min() const
  {
    return this->mask.get_box()->get_min();
  }

  Point
  get_max() const
  {
    return this->mask.get_box()->get_max();
  }

  Mask*
  get_mask()
  {
    return &this->mask;
  }
  
};



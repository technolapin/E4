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
  
};






template<int dim, typename Box>
NImage<dim, int, Box>
distance_map(const NImage<dim, int, Box> &img)
{
  auto output = NImage<dim, int, Box>(img);
  auto heads = std::queue<NPoint<dim>>();
  auto iter = img.iterator();
  auto nei_iter = img.neighboor_iterator();

  
  for (iter.start(); iter.is_valid(); iter.next())
  {
    auto pt = iter.value();
    auto pix = img.get_pixel(pt).value();

    if (pix != 0)
    {
      heads.push(pt);
      output.set_pixel(pt, 0);
    }
    else
    {
      output.set_pixel(pt, -1);
    }
  }
  
  while (!heads.empty())
  {
    auto head = heads.front();
    heads.pop();
    auto dist_head = output.get_pixel(head).value();

    for (nei_iter.start(head); nei_iter.is_valid(); nei_iter.next())
    {
      auto pt_nei = nei_iter.value();
      if (output.get_pixel(pt_nei).value() == -1)
      {
	output.set_pixel(pt_nei, dist_head+1);
	heads.push(pt_nei);
      }
    }
  }
  
  return output;
}



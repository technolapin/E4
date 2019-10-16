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
  product()
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
  is_valid()
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
  value()
  {
    return this->current;
  }
  
};








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
  NImage(Box box):
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
  iterator()
  {
    return BoxIterator(this->box);
  }

  NghIterator
  neighboor_iterator()
  {
    return NghIterator(this->box);
  }

};


template<int dim, typename Box>
NImage<dim, int, Box>
distance_map(NImage<dim, int, Box> &img)
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



template<int dim>
NPoint<dim>
operator-(NPoint<dim> pa, NPoint<dim> pb)
{
  auto pc = NPoint<dim>();
  for (int i = 0; i < dim; ++i)
    pc.coords[i] = pa.coords[i] + pb.coords[i];
  return pc;
}


template<int dim>
class NMaskedBox
{
  using Point = NPoint<dim>;
  using Box = NBox<dim>;
  using Mask = NImage<dim, bool>;
  
private:
  Mask mask;
  
public:
  NMaskedBox(Mask mask):
    mask(mask)
  {}

  bool
  within(Point pt) const
  {
    auto pix = this->mask.get_pixel(pt);
    /*
    return (this->mask.get_box()->within(pt)
	    && this->mask.get_pixel(pt).value());
    */
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


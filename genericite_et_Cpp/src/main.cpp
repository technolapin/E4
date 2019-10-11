#include <iostream>
#include <vector>
#include <memory>

struct point2d
{
  int x;
  int y;
};

bool
operator<=(point2d pa, point2d pb)
{
  return pa.x <= pb.x && pa.y <= pb.y;
}
bool
operator<(point2d pa, point2d pb)
{
  return pa.x < pb.x && pa.y < pb.y;
}


class box2d
{
private:
  point2d p_min;
  point2d p_max;
public:
  box2d(int x_min, int y_min,
	int x_max, int y_max)
  {
    this->p_min = {x_min, y_min};

    this->p_max = {x_max, y_max};
  }

  ~box2d(){}

  bool
  within(point2d pt) const
  {
    return this->p_min <= pt && pt < this->p_max;
  }
  
  point2d
  get_min() const
  {
    return point2d{this->p_min.x, this->p_min.y};
  }

  point2d
  get_max() const
  {
    return point2d{this->p_max.x, this->p_max.y};
  }
  
};

class box2diterator
{
private:
  point2d current;
  point2d limit;
public:

  box2diterator(const box2d& box)
  {
    this->current = box.get_min();
    this->limit = box.get_max();
  }
  
  void
  start(const box2d &box){
  }; // renvoie rien du tout et initialise l'itérateur

  bool
  is_valid(){
    return this->current < this->limit;
  }; // vrai tant que pas à la fin

  void
  next() // passe au suivant
  {
    this->current.x++;
    if (!this->is_valid())
    {
      this->current.x = 0;
      this->current.y++;
    }
  }

  point2d
  get_current()
  {
    return this->current;
  }
};

template<class T>
class image2d
{
private:
  std::vector<T> data;
  int width;
  int height;
  int length;
  
public:

  image2d(int width, int height)
  {
    this->width = width;
    this->height = height;
    this->length = width*height;
    this->data = new std::vector<T>();
  }
  
};

template<class T>
class neighb2d_iterator
{
private:
  image2d<T> &img;
  
  
public:
  neighb2d_iterator<T>(const image2d<T> &img)
  {
    this->img = img;
  }
};


int
main()
{

  box2d box = * new box2d(0, 0, 64, 64);

  auto iter = new box2diterator(box);

  for (; iter->is_valid(); iter->next())
  {
    auto p = iter->get_current();
    std::cout << p.x << " "<< p.y << std::endl;
  }
  
}

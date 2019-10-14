#pragma once

struct point2d
{
  int x;
  int y;
};



class box2d
{
private:
  point2d p_min;
  point2d p_max;
  
public:
  box2d(int x_min, int y_min,
	int x_max, int y_max);

  bool
  within(point2d pt) const;
  
  point2d
  get_min() const;

  point2d
  get_max() const;
  
};

class box2diterator
{
private:
  point2d begining;
  point2d current;
  point2d limit;
  
public:
  box2diterator(const box2d& box);
  
  void
  start();

  bool
  is_valid();
  
  void
  next();

  point2d
  value();
  
};

class neighb2d_iterator
{
private:
  std::vector<point2d> neighborhood;
  std::vector<point2d>::iterator iterator;

public:
  neighb2d_iterator(const box2d& box, const point2d& cell);
  
  void
  start();

  bool
  is_valid();

  void
  next();

  point2d
  value();

};

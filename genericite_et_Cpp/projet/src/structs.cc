#pragma once


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


box2d::box2d(int x_min, int y_min,
	     int x_max, int y_max)
{
  this->p_min = {x_min, y_min};
  
  this->p_max = {x_max, y_max};
}


bool
box2d::within(point2d pt) const
{
  return this->p_min <= pt && pt < this->p_max;
}
  
point2d
box2d::get_min() const
{
  return point2d{this->p_min.x, this->p_min.y};
}

point2d
box2d::get_max() const
{
  return point2d{this->p_max.x, this->p_max.y};
}
  

box2diterator::box2diterator(const box2d& box):
  begining(box.get_min()),
  limit(box.get_max())
{}
  
void
box2diterator::start()
{
  this->current = this->begining;
}; // renvoie rien du tout et initialise l'itérateur

bool
box2diterator::is_valid(){
  return this->current < this->limit;
}; // vrai tant que pas à la fin

void
box2diterator::next() // passe au suivant
{
    this->current.x++;
    if (!this->is_valid())
    {
      this->current.x = 0;
      this->current.y++;
    }
  }

point2d
box2diterator::value()
{
  return this->current;
}


neighb2d_iterator::neighb2d_iterator(const box2d& box, const point2d& cell):
  neighborhood(std::vector<point2d>())
{
  point2d left  = point2d{cell.x-1, cell.y};
  point2d right = point2d{cell.x+1, cell.y};
  point2d up    = point2d{cell.x, cell.y-1};
  point2d down  = point2d{cell.x, cell.y+1};
  
  if (box.within(left))
    this->neighborhood.push_back(left);
  if (box.within(right))
    this->neighborhood.push_back(right);
  if (box.within(up))
    this->neighborhood.push_back(up);
  if (box.within(down))
    this->neighborhood.push_back(down);
}
  
void
neighb2d_iterator::start()
{
  this->iterator = this->neighborhood.begin();
}; // renvoie rien du tout et initialise l'itérateur

bool
neighb2d_iterator::is_valid(){
  return this->iterator != this->neighborhood.end();
}; // vrai tant que pas à la fin

void
neighb2d_iterator::next() // passe au suivant
{
  ++this->iterator;
}

point2d
neighb2d_iterator::value()
{
  return *(this->iterator);
}



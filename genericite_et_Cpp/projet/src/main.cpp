#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <optional>
#include "structs.hh"
#include "structs.cc"


template<class T>
class image2d
{
private:
  int width;
  int height;
  box2d box;
  std::vector<T> data;

public:
  image2d(int width, int height):
    width(width),
    height(height),
    box(0, 0, width, height),
    data(width*height) {}

  std::optional<T>
  get_pixel(point2d pt)
  {
    if (this->box.within(pt))
    {
      return this->data[pt.x+pt.y*this->width];
    }
    else
    {
      return {};
    }
  }

  void
  set_pixel(point2d pt, T val)
  {
    if (this->box.within(pt))
    {
      this->data[pt.x+pt.y*this->width] = val;
    }    
  }

  box2diterator
  iterator()
  {
    return box2diterator(this->box);
  }
  
  neighb2d_iterator
  neighboor_iterator()
  {
    return neighb2d_iterator(this->box);
  }

  void
  print()
  {
    for (int j = 0; j < this->height; j++)
    {
      for (int i = 0; i < this->width; i++)
      {
	std::cout << this->data[i + j*this->width] << " ";
      }
      std::cout << std::endl;
    }
  }
  
};



image2d<int>
distance_map(image2d<int> &img)
{
  auto output = image2d<int>(img);

  auto heads = std::queue<point2d>();
  
  auto iter = img.iterator();
  auto nei_iter = img.neighboor_iterator();
  // bad idea: prevent easy parallelisation

  
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




void
test_structs()
{

  box2d box = box2d(0, 0, 64, 64);

  auto iter = box2diterator(box);

  for (iter.start(); iter.is_valid(); iter.next())
  {
    auto p = iter.value();
    std::cout << p.x << " " << p.y << std::endl;
  }


  auto nei = neighb2d_iterator(box);

  for (nei.start(point2d{8,8}); nei.is_valid(); nei.next())
  {
    auto p = nei.value();
    std::cout << p.x << " " << p.y << std::endl;
  }

  auto img = image2d<int>(8, 4);
  
}



void
test_map()
{
  auto img = image2d<int>(8, 4); 
  img.set_pixel(point2d{0, 0}, 1);
  img.set_pixel(point2d{7, 0}, 1);
  auto map = distance_map(img);

  
  img.print();
  std::cout << std::endl;
  map.print();
}

int
main()
{
  //test_structs();
  test_map();
  return 0;
}
/*
II.3:
À ce stade, le code n'est toujours pas générique, car
seul le type des valeurs des pixels de l'image est générique, 
alors que le type de points, du domaine, et des iterateurs sont 
toujours fixés (on est toujours en dimension 2).
Il suffit d'ajouter en paramètre de la template la dimension de l'image, et de rendre les autres classes et structures génériques pour pouvoir en changer la dimension.
 */

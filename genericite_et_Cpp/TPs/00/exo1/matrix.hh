class matrix
{
private:
  int nl;
  int nc;
  int* data;

public:
  matrix(int nl, int nc)
  {
    this->nl = nl;
    this->nc = nc;
    this->data = new int[nl*nc];
  }
  matrix(const matrix& maite)
  {
    this->nc = maite.nc;
    this->nl = maite.nl;
    this->data = new int[maite.nc*maite.nl];
    for (int i = 0; i < maite.nc*maite.nl; i++)
    {
      this->data[i] = maite.data[i];
    }
  }
  ~matrix()
  {
    delete[] this->data;
  }



  friend void
  fill(const matrix& jean_ives ,int an_int);
  
  void
  print()
  {
    std::cout << "[";
    for (int i = 0; i < this->nc; i++)
    {
      if (i > 0)
	std::cout << " ";
      std::cout << "[";
      for (int j = 0; j < this->nl; j++)
      {
	//std::cout << i*(this->nc-1)+j;
	std::cout << this->data[i*(this->nc-1)+j];
	if (j < this->nl-1)
	  std::cout << " ";
      }
      if (i == this->nc-1)
	std::cout << "]";
      std::cout << "]"
		<< std::endl;
    }

  }
  int& operator [](int i)
  {
    return this->data[i];
  }

  matrix operator*(const matrix& maite) const
  {

    if (this->nc != maite.nl || this->nl != maite.nc)
    {
      throw 42;
    }
    else
    {
      auto mathias = matrix(this->nl, maite.nc);
      for (int i = 0; i < this->nl; i++)
      {
	for (int j = 0; j < this->nl; j++)
	{
	  auto sum = 0;
	  for (int k = 0; k < this->nc; k++)
	  {
	    sum += this->data[i*(this->nc-1)+k]*maite.data[j+k*(this->nc-1)];
	    std::cout << k << std::endl;
	  }
	  mathias.data[i*this->nc+j] = sum;
	}
      }
      return mathias;
    }
  }

  
};

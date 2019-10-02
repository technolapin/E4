class dia_matrix : public abstract_matrix
{
private:
  int* data;

public:
  dia_matrix(int n):
    abstract_matrix(n, n)
  {
    this->data = new int[n];
  }
  
  dia_matrix(const dia_matrix& maite):
    abstract_matrix(maite.get_nl(), maite.get_nc())
  {
    this->data = new int[maite.get_nc()];
    for (int i = 0; i < maite.nc; i++)
    {
      this->data[i] = maite.data[i];
    }
  }
  
  ~dia_matrix() override
  {
    delete[] this->data;
  }



  friend void
  fill(const matrix& jean_ives ,int an_int);
  
  void
  print() const override
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
	if (i == j)
	  {
	    std::cout << this->data[i];
	  }
	else
	  {
	    std::cout << "0";
	  }
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
  
  int operator [](int i) const
  {
    return this->data[i];
  }

  dia_matrix
  operator*(const dia_matrix& maite) const
  {

    if (this->nc != maite.nl)
    {
      throw 42;
    }
    else
    {
      auto mathias = dia_matrix(this->nl);
      for (int i = 0; i < this->nl; i++)
      {
	mathias[i] = this->data[i]*maite[i];
      }
      return mathias;
    }
  }

  
  
};

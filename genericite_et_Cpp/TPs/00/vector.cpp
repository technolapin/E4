#include<iostream>


class vector
{
private:
  int n;
  int* data;

public:
  vector(int dim)
  {
    this->n = dim;
    this->data = new int[dim];
  }
  vector(const vector& victor)
  {
    this->n = victor.n;
    this->data = new int[victor.n];
    for (int i = 0; i < victor.n; i++)
    {
      this->data[i] = victor.data[i];
    }
  }
  ~vector()
  {
    delete[] this->data;
  }

  void
  print()
  {
    std::cout << "[";
    for (int i = 0; i < this->n; i++)
    {
      std::cout << this->data[i]
		<< " ";
    }
    std::cout << "]\n";
  }

  int& operator [](int i)
  {
    return this->data[i];
  }

  vector& operator =(const vector& sempai)
  {
    if (this->n != sempai.n)
    {
      this->n = sempai.n;
      delete[] this->data;
      this->data = new int[sempai.n];
    }
    
    for (int i = 0; i < sempai.n; i++)
    {
      this->data[i] = sempai.data[i];
    }
    
    return *this;
  }

  vector operator *(const int scalar) const
  {
    auto victor = vector(this->n);
    for (int i = 0; i < this->n; i++)
    {
      victor.data[i] = scalar*this->data[i];
    }
    return victor;
  }

  vector operator+(const int notascalar) const
  {
    auto victor = vector(this->n);
    for (int i = 0; i < this->n; i++)
    {
      victor.data[i] = notascalar+this->data[i];
    }
    return victor;
  }
};

vector operator*(const int scalar, const vector victor)
{
  return victor*scalar;
}
vector operator+(const int notascalar, const vector victor)
{
  return victor+notascalar;
}


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
	std::cout << this->data[i*(this->nc-1)+j];
	if (j < this->nl-1)
	  std::cout << " ";
      }
      if (i == this->nc-1)
	std::cout << "]";
      std::cout << "]"
		<< std::endl;
    }

    std::cout << "DEBUG: ";
    for (int i = 0; i < this->nc*this->nl; i++)
    {
      std::cout << this->data[i]
		<< " " ;
    }
    std::cout << std::endl;
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
	for (int j = 0; j < this->nc; j++)
	{
	  auto sum = 0;
	  for (int k = 0; k < this->nc; k++)
	  {
	    sum = this->data[i*this->nc+k]*maite.data[j+k*this->nc];
	  }
	  mathias.data[i*this->nc+j] = sum;
	}
      }
      return mathias;
    }   
  }
  
  
};



int
main()
{
  auto michel = vector(2);
  auto jean = vector(2);
  michel.print();
  michel[1] = 1;
  michel.print();

  jean = michel;

  auto didier = 2*jean + 1;

  auto marie = matrix(2, 1);
  marie[0] = 1;
  marie[1] = 1;
    
  auto riema = matrix(1, 2);

  riema[0] = 1;
  riema[1] = 2;

  
  auto lucie = marie*riema;

  marie.print();
  riema.print();
  lucie.print();
  didier.print();
}


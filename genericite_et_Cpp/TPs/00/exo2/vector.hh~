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
  
  friend void
  fill(const vector& jean_michel ,int an_int);

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

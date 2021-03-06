class vector : public abstract_vector
{
private:
  int* data;

public:
  vector(const int dim):
    abstract_vector(dim)
  {
    this->data = new int[dim];
  }

  vector(const vector& vec):
    abstract_vector(vec.n)
  {
    this->data = new int[vec.n];
  }

  ~vector() override
  {
    delete[] this->data;
  }

  
  void
  print() const override
  {
    std::cout << "[";
    for (int i = 0; i < this->n; i++)
    {
      std::cout << this->data[i]
		<< " ";
    }
    std::cout << "]\n";
  }


  int& operator [](const int i)
  {
    return this->data[i];
  }

  int operator [](const int i) const
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

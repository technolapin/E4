class one_vector : public abstract_vector
{
private:
  int value;

public:
  one_vector(int dim, int value = 1):
    abstract_vector(dim)
  {
    this->value = value;
  }

  ~one_vector() override {}

  
  void
  print() const override
  {
    std::cout << "[";
    for (int i = 0; i < this->n; i++)
    {
      std::cout << this->value
		<< " ";
    }
    std::cout << "]\n";
  }

  int
  operator[](const int i) const
  {
    if (i >= this->get_dim())
    {
      throw 42;
    }
    else
    {
      return this->value;
    }
  }

  one_vector& operator =(const one_vector& sempai)
  {
    this->n = sempai.get_dim();
    this->value = sempai.value;
      
    return *this;
  }

  one_vector operator *(const int scalar) const
  {
    return one_vector(this->n, this->value*scalar);
  }

  one_vector operator+(const int notascalar) const
  {
    return one_vector(this->n, this->value+notascalar);
  }
};

class vector : public abstract_vector
{
private:

public:
  vector(int dim)
  {
    this->n = dim;
    this->data = new int[dim];
  }
  ~vector() override
  {
    delete[] this->data;
  }
  

  int& operator [](int i)
  {
    return this->data[i];
  }

  vector& operator =(const vector& sempai) override
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

  vector operator *(const int scalar) const override
  {
    auto victor = vector(this->n);
    for (int i = 0; i < this->n; i++)
    {
      victor.data[i] = scalar*this->data[i];
    }
    return victor;
  }

  vector operator+(const int notascalar) const override
  {
    auto victor = vector(this->n);
    for (int i = 0; i < this->n; i++)
    {
      victor.data[i] = notascalar+this->data[i];
    }
    return victor;
  }
};


class abstract_vector
{
protected:
  int n;

public:
  abstract_vector(int n)
  {
    this->n = n;
  }

  int
  get_dim() const
  {
    return this->n;
  }
  
  virtual ~abstract_vector(){};

  virtual void
  print() const = 0;
  
};

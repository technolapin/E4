class abstract_matrix
{
protected:
  int nl;
  int nc;

public:
  abstract_matrix(int nl, int nc)
  {
    this->nl = nl;
    this->nc = nc;
  }

  int
  get_nl() const
  {
    return this->nl;
  }
  
  int
  get_nc() const
  {
    return this->nc;
  }
  
  virtual ~abstract_matrix(){};
  
  virtual void
  print() const = 0;
  
};

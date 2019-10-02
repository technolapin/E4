

vector
operator*(const vector vec,
	  const vector vik)
{
  auto dim_v = vec.get_dim();
  auto dim_o = vik.get_dim();
  if (dim_v != dim_o)
  {
    throw 1;
  }
  else
  {
    auto out = vector(dim_v);
    for (int i = 0; i < vec.get_dim(); i++)
    {
      out[i] = vec[i]*vik[i];
    }
    return out;
  }
  
}


vector
operator*(const vector vec,
	  const one_vector one)
{
  auto dim_v = vec.get_dim();
  auto dim_o = one.get_dim();
  if (dim_v != dim_o)
  {
    throw 1;
  }
  else
  {
    auto out = vector(dim_v);
    for (int i = 0; i < vec.get_dim(); i++)
    {
      out[i] = vec[i]*one[i];
    }
    return out;
  }
  
}


vector
operator*(const one_vector one,
	  const vector vec)
{
  return one*vec;
}


matrix
operator*(const matrix mat,
	  const dia_matrix dia)
{
  auto nl = mat.get_nl();
  auto nc = mat.get_nc();
  auto n_dia = dia.get_nc();
  if (nl != n_dia)
  {
    throw 2;
  }
  else
  {
    auto out = matrix(nl, nc);
    for (int i = 0; i < nl; i++)
    {
      for (int j = 0; j < nc; j++)
      {
	int k = i*(nc-1)+j;
	out[k] = mat[j]*dia[i];
	
      }
    }
    return out;
  }
  
}

matrix
operator*(const dia_matrix dia,
	  const matrix mat)
{
  auto nl = mat.get_nl();
  auto nc = mat.get_nc();
  auto n_dia = dia.get_nc();
  if (nc != n_dia)
  {
    throw 2;
  }
  else
  {
    auto out = matrix(nl, nc);
    for (int i = 0; i < nc; i++)
    {
      for (int j = 0; j < nl; j++)
      {
	int k = j*(nc-1)+i;
	out[k] = mat[j]*dia[i];
	
      }
    }
    return out;
  }
  
}


template <typename M, typename V>
vector
prod_mv(const M mat,
	const V vec)
{
  auto nl = mat.get_nl();
  auto nc = mat.get_nc();
  auto n_vec = vec.get_dim();
  if (nc != n_vec)
  {
    throw 2;
  }
  else
  {
    auto out = vector(n_vec);
    for (int i = 0; i < nl; i++)
    {
      out[i] = 0;
      for (int j = 0; j < nc; j++)
      {
	int k = i*(nc-1)+j;
	out[i] += mat[k]*vec[j];
	
      }
    }
    return out;
  }  
}

template <typename M, typename V>
vector
prod_vm(const V vec,
	const M mat)
{
  auto nl = mat.get_nl();
  auto nc = mat.get_nc();
  auto n_vec = vec.get_dim();
  if (nc != n_vec)
  {
    throw 2;
  }
  else
  {
    auto out = vector(n_vec);
    for (int i = 0; i < nl; i++)
    {
      out[i] = 0;
      for (int j = 0; j < nc; j++)
      {
	int k = j*(nc-1)+i;
	out[i] += mat[k]*vec[j];
	
      }
    }
    return out;
  }  
}



vector
operator*(const matrix mat,
	  const vector vec)
{
  return prod_mv(mat, vec);
}

vector
operator*(const vector vec,
	  const matrix mat)
{
  return prod_vm(vec, mat);
}



vector
operator*(const dia_matrix mat,
	  const vector vec)
{
  return prod_mv(mat, vec);
}

vector
operator*(const vector vec,
	  const dia_matrix mat)
{
  return prod_vm(vec, mat);
}



vector
operator*(const matrix mat,
	  const one_vector vec)
{
  return prod_mv(mat, vec);
}

vector
operator*(const one_vector vec,
	  const matrix mat)
{
  return prod_vm(vec, mat);
}



vector
operator*(const dia_matrix mat,
	  const one_vector vec)
{
  return prod_mv(mat, vec);
}

vector
operator*(const one_vector vec,
	  const dia_matrix mat)
{
  return prod_vm(vec, mat);
}

/* 


vector
operator*(const matrix mat,
	  const one_vector vec)
{
  auto nl = mat.get_nl();
  auto nc = mat.get_nc();
  auto n_vec = vec.get_dim();
  if (nc != n_vec)
  {
    throw 2;
  }
  else
  {
    auto out = vector(n_vec);
    for (int i = 0; i < nl; i++)
    {
      out[i] = 0;
      for (int j = 0; j < nc; j++)
      {
	int k = i*(nc-1)+j;
	out[i] += mat[k]*vec[j];
	
      }
    }
    return out;
  }  
}


vector
operator*(const one_vector vec,
	  const matrix mat)
{
  auto nl = mat.get_nl();
  auto nc = mat.get_nc();
  auto n_vec = vec.get_dim();
  if (nc != n_vec)
  {
    throw 2;
  }
  else
  {
    auto out = vector(n_vec);
    for (int i = 0; i < nl; i++)
    {
      out[i] = 0;
      for (int j = 0; j < nc; j++)
      {
	int k = j*(nc-1)+i;
	out[i] += mat[k]*vec[j];
	
      }
    }
    return out;
  }  
}


vector
operator*(const dia_matrix mat,
	  const one_vector vec)
{
  auto nl = mat.get_nl();
  auto nc = mat.get_nc();
  auto n_vec = vec.get_dim();
  if (nc != n_vec)
  {
    throw 2;
  }
  else
  {
    auto out = vector(n_vec);
    for (int i = 0; i < nl; i++)
    {
      out[i] = 0;
      for (int j = 0; j < nc; j++)
      {
	int k = i*(nc-1)+j;
	out[i] += mat[k]*vec[j];
	
      }
    }
    return out;
  }  
}


vector
operator*(const one_vector vec,
	  const dia_matrix mat)
{
  auto nl = mat.get_nl();
  auto nc = mat.get_nc();
  auto n_vec = vec.get_dim();
  if (nc != n_vec)
  {
    throw 2;
  }
  else
  {
    auto out = vector(n_vec);
    for (int i = 0; i < nl; i++)
    {
      out[i] = 0;
      for (int j = 0; j < nc; j++)
      {
	int k = j*(nc-1)+i;
	out[i] += mat[k]*vec[j];
	
      }
    }
    return out;
  }  
}
*/



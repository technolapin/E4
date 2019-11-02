
int
min(int a, int b)
{
  if (a <= b)
    return a;
  else
    return b;
}

int
max(int a, int b)
{
  if (a <= b)
    return b;
  else
    return a;
}



void
sort(std::vector<ushort>& vec, int start, int end)
{
  if (start+1 < end)
  {
    int mid = (start+end)/2;
    sort(vec, start, mid);
    sort(vec, mid, end);

    for (int i = start; i < end; i++)
    {
      if (vec[i] > vec[mid])
      {
	ushort val = vec[mid];
	for (int j = mid; j > i; --j)
	{
	  vec[j] = vec[j-1];
	}
	vec[i] = val;
	++mid;
	if (mid == end)
	  break;

      }
    }
  }
}


void
test()
{
  auto vec = std::vector<ushort>();

  vec.push_back(1);
  vec.push_back(6);
  vec.push_back(7);
  vec.push_back(2);

  for (int i = 0; i < vec.size(); ++i)
    std::cout << vec[i] << " ";
  std::cout << std::endl;

  sort(vec, 0, vec.size());

  for (int i = 0; i < vec.size(); ++i)
    std::cout << vec[i] << " ";
  std::cout << std::endl;
  assert(false);
}

void
median_blur(cv::InputArray src,
	    cv::OutputArray dst,
	    int kernel)
{
  
  auto mat_in = src.getMat();
  auto el_size = 1;
  auto h = mat_in.size[0];
  auto w = mat_in.size[1];
  auto mat_out = cv::Mat(h, w, mat_in.type());
  auto length = h*w*el_size;

  auto ptr_in = mat_in.data;
  auto ptr_out = mat_out.data;
  int kernel_size = kernel*kernel;
  auto neighborhood = std::vector<ushort>(kernel_size, 0);
  int neigh_size = 0;
  
  int sum = 0;
  
  for (int i = 0; i < w; i++)
  {
    for (int j = 0; j < h; j++)
    {
      neigh_size = 0;
      sum = 0;
      for (int x = i; x < min(w, kernel+i); x++)
      {
	for (int y = j; y < min(h, kernel+j); y++)
	{
	  neighborhood[neigh_size] = ptr_in[y*w+x];
	  neigh_size++;
	}
      }

      sort(neighborhood, 0, kernel_size);
      
      ptr_out[i+j*w] = neighborhood[kernel_size/2];
    }
  }
  std::cout << "PIZZA" << std::endl;
  
  dst.assign(mat_out);

}


void
median_blur_opt(cv::InputArray src,
		cv::OutputArray dst,
		int kernel)
{
  auto mat_in = src.getMat();
  auto el_size = 1;
  auto h = mat_in.size[0];
  auto w = mat_in.size[1];
  auto mat_out = cv::Mat(h, w, mat_in.type());
  auto length = h*w*el_size;

  auto ptr_in = mat_in.data;
  auto ptr_out = mat_out.data;
  int sum = 0;

  for (int i = 0; i < w; i++)
  {
    for (int j = 0; j < h; j++)
    {
      sum = 0;
      for (int x = i; x < min(w, kernel+i); x++)
      {
	for (int y = j; y < min(h, kernel+j); y++)
	{
	    sum+=ptr_in[y*w+x];
	}
      }
      ptr_out[i+j*w] = sum/kernel/kernel;
    }
  }
  
  dst.assign(mat_out);


  
}

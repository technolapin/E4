#include<queue>

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



#include <algorithm>


int median5(std::vector<ushort> & A, int s)
{
    if ( A.size() <= s + 5 )
        return A[s];
   
    std::vector<ushort> B;
    for (int i=s;i < s + 5; i++)
        B.push_back(A[i]);
   
    sort ( B.begin(), B.end() );
    return B[2];
}

int computeKSmallest( std::vector<ushort> & A, int k )
{    
    int n = A.size();
   
    if (n == 1) {
        if ( k == 0) return A[0];
        else std::cout << "Error somewhere!\n";
    }
   
    std::vector<ushort> C;
   
    for (int i=0; i < A.size(); i+=5)
        C.push_back( median5( A, i ) );  
   
    ushort approximate_median = computeKSmallest( C, C.size() / 2 );    
   
    std::vector<ushort> A_small, A_big;
   
    for (int i=0; i < n; i++) {
        if ( A[i] < approximate_median ) A_small.push_back( A[i] );
        else if (A[i] > approximate_median)  A_big.push_back( A[i] );
    }
   
    if ( k+1 <= A_small.size() ) return computeKSmallest( A_small, k );
    if ( k+1 > n - A_big.size() ) return computeKSmallest( A_big, k - ( n - A_big.size() ) );
    else return approximate_median;
}


ushort
median(std::vector<ushort> & vec)
{
  return computeKSmallest(vec, vec.size()/2);
}

// juste pour tester un peu le sort
/*
void
test_sort()
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
*/



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
  
  
  for (int i = 0; i < w; i++)
  {
    for (int j = 0; j < h; j++)
    {
      neigh_size = 0;
      for (int x = i; x < min(w, kernel+i); x++)
      {
	for (int y = j; y < min(h, kernel+j); y++)
	{
	  neighborhood[neigh_size] = ptr_in[y*w+x];
	  neigh_size++;
	}
      }

      //sort(neighborhood, 0, kernel_size);
      //      ptr_out[i+j*w] = neighborhood[kernel_size/2];

      ptr_out[i+j*w] = median(neighborhood);
    }
  }
  std::cout << "PIZZA" << std::endl;
  
  dst.assign(mat_out);

}

/*
void
median_blur_opt(cv::InputArray src,
		cv::OutputArray dst,
		int kernel)
{
  test_median();
  auto mat_in = src.getMat();
  auto el_size = 1;
  auto h = mat_in.size[0];
  auto w = mat_in.size[1];
  auto mat_out = cv::Mat(h, w, mat_in.type());
  auto length = h*w*el_size;

  auto ptr_in = mat_in.data;
  auto ptr_out = mat_out.data;
  int kernel_size = kernel*kernel;
  
  int neigh_size = 0;
  
  
  for (int j = 0; j < h; j++)
  {
    auto neighborhood = std::vector<short>();
    for (int i = 0; i < kernel; i++)
    {
      for (int k = j; k < j+kernel; ++k)
      {
	neighborhood.push_back(ptr_in[i+k*w]);
      }
    }
    for (int i = 0; i < w; i++)
    {
      for (int k = j; k < j+kernel; ++k)
      {
	neighborhood.pop();
	neighborhood.push(ptr_in[i+k*w]);
      }

      //sort(neighborhood, 0, kernel_size);
      
      ptr_out[i+j*w] = neighborhood.front();
    }
  }
  std::cout << "PIZZA" << std::endl;
  
  dst.assign(mat_out);

  
}
*/

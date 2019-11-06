#include <algorithm>
#include<vector>


#include <time.h>
#include <sys/time.h>


#define MEDIAN_TRESHOLD 5


double e;
double s;
struct timeval start, end;


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

    /*
     * Steps 1 and 3 are the slowest
     */

    if (n <= MEDIAN_TRESHOLD) {
      /*
        if ( k == 0) return A[0];
        else std::cout << "Error somewhere!\n";
      */
      sort(A.begin(), A.end());
      return A[k];
    }
   
    std::vector<ushort> C;

    // à peine plus lent, mais quand même significatif
    /*
    for (int i=0; i < A.size(); i+=5)
      C.push_back( median5( A, i ) );
    */      


    /*
    gettimeofday(&start, NULL);
    s = ((double) start.tv_sec * 1000000.0 + (double) start.tv_usec);
    */

    for (auto it = A.begin(); it+5 < A.end(); it+=5)
    {
      sort(it, it+5);
      C.push_back(it[2]);
    }
    /*
    gettimeofday(&end, NULL);
    e = ((double) end.tv_sec * 1000000.0 + (double) end.tv_usec);

    printf("FIRST STEP: %0.lf\n", e-s);
    */

    /*    
    gettimeofday(&start, NULL);
    s = ((double) start.tv_sec * 1000000.0 + (double) start.tv_usec);
    */
    ushort approximate_median = computeKSmallest( C, C.size() / 2 );    

    /*
    gettimeofday(&end, NULL);
    e = ((double) end.tv_sec * 1000000.0 + (double) end.tv_usec);

    printf("SECOND STEP: %0.lf\n", e-s);
    */





    /*
    gettimeofday(&start, NULL);
    s = ((double) start.tv_sec * 1000000.0 + (double) start.tv_usec);
    */
    std::vector<ushort> A_small, A_big;
   
    for (int i=0; i < n; i++) {
        if ( A[i] < approximate_median ) A_small.push_back( A[i] );
        else if (A[i] > approximate_median)  A_big.push_back( A[i] );
    }

    /*
    gettimeofday(&end, NULL);
    e = ((double) end.tv_sec * 1000000.0 + (double) end.tv_usec);

    printf("THIRD STEP: %0.lf\n", e-s);
    */

    
   
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

      ptr_out[i+j*w] = median(neighborhood);
    }
  }
  
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
  int kernel_size = kernel*kernel;
  std::vector<ushort> neighborhood;


  
  for (int i = 0; i < w-kernel; i++)
  {
    neighborhood = std::vector<ushort>(0, kernel_size);
    for (int kj = 0; kj < kernel; ++kj)
    {
      for (int ki = i; ki < i+kernel; ++ki)
      {
	neighborhood.push_back(ptr_in[ki+kj*w]);
      }
    }

    int line_pointer = kernel-1; // to cicle the vec
    /*
    std::cout << kernel << std::endl;
    std::cout << kernel_size << std::endl;
    std::cout << neighborhood.size() << std::endl;
    */
    for (int j = 0; j < h-kernel; j++)
    {
      for (int ki = i; ki < i+kernel; ++ki)
      {
	auto index = ki-i+((j+kernel-1)%kernel)*kernel;
	//std::cout << "index " << index << std::endl; 
	neighborhood[index] = ptr_in[ki+(j+kernel-1)*w];
      }
      line_pointer++;
      ptr_out[i+j*w] = median(neighborhood);
    }
  }
  
  dst.assign(mat_out);

}

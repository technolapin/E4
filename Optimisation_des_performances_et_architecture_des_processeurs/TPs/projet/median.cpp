#include <algorithm>
#include<vector>


#include <time.h>
#include <sys/time.h>

#include <thread>



#define MEDIAN_TRESHOLD 100

typedef struct thread_parameters
{
  unsigned char* ptr_in;
  unsigned char* ptr_out;
  int kernel;
  int w;
  int h;
} threa_parameter;


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

    if (n <= 5) {
      /*
        if ( k == 0) return A[0];
        else std::cout << "Error somewhere!\n";
      */
      sort(A.begin(), A.end());
      return A[k];
    }
   
    std::vector<ushort> C;

    // significativement lent
    for (int i=0; i < A.size(); i+=5)
      C.push_back( median5( A, i ) );

    /*
    gettimeofday(&start, NULL);
    s = ((double) start.tv_sec * 1000000.0 + (double) start.tv_usec);
    */

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


int computeKSmallest_opt( std::vector<ushort> & A, int k )
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
    for (auto it = A.begin(); it+5 < A.end(); it+=5)
    {
      sort(it, it+5);
      C.push_back(it[2]);
    }

    /*
    gettimeofday(&start, NULL);
    s = ((double) start.tv_sec * 1000000.0 + (double) start.tv_usec);
    */

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

ushort
median_opt(std::vector<ushort> & vec)
{
  return computeKSmallest_opt(vec, vec.size()/2);
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
aux_median_blur_opt_sale(unsigned char* ptr_in,
			 unsigned char* ptr_out,
			 int kernel, int w, int h)
{

  
  int kernel_size = kernel*kernel;
  std::vector<ushort> neighborhood;

  auto half_kernel = kernel/2;
  auto kernel_right = kernel/2+1;
  auto kernel_left = kernel-kernel_right;
  
  neighborhood = std::vector<ushort>(kernel_size, 0);
  for (int i = kernel_left; i < w-kernel_right; i++)
  {
    int vec_index = 0;
    for (int kj = 0; kj < kernel; ++kj)
    {
      for (int ki = i-kernel_left; ki < i+kernel_right; ++ki)
      {
	//	neighborhood.push_back(ptr_in[ki+kj*w]);
	neighborhood[vec_index] = ptr_in[ki+kj*w];
	vec_index++;
      }
    }

    /*
    std::cout << kernel << std::endl;
    std::cout << kernel_size << std::endl;
    std::cout << neighborhood.size() << std::endl;
    */
    for (int j = kernel_left; j < h-kernel_right; j++)
    {
      for (int ki = i - kernel_left; ki < i+kernel_right; ++ki)
      {
	auto index = ki-i+kernel_left+((j+kernel_right-1)%kernel)*kernel;
	//std::cout << "index " << index << std::endl; 
	neighborhood[index] = ptr_in[ki+(j+kernel-1)*w];
      }
      ptr_out[i+j*w] = median_opt(neighborhood);
    }


  }

}


void
top_and_bottom_border(unsigned char* ptr_in,
		      unsigned char* ptr_out,
		      int kernel, int w, int h, int n_threads)
{
  auto kernel_right = kernel/2+1; // le nombre de pixels à droite de la cellule centrale
  auto kernel_left = kernel-kernel_right; // le nombre de pixels à gauche
  for (int cell_x = 0; cell_x < w; cell_x++)
  {
    for (int cell_y = 0; cell_y < kernel_left; ++cell_y) // pour le bord en haut
    {
      auto neighborhood = std::vector<ushort>();

      for (int ker_y = 0; ker_y < cell_y+kernel_right; ++ker_y)
	for (int ker_x = cell_x-kernel_left; ker_x < cell_x+kernel_right; ++ker_x)
	  neighborhood.push_back(ptr_in[ker_x+ker_y*w]);
      
      ptr_out[cell_x+cell_y*w] = median_opt(neighborhood);

    }
  }
  for (int cell_x = 0; cell_x < w; cell_x++)
  {
    for (int cell_y = h-kernel_right; cell_y < h; cell_y++) // pour le bord d'en bas
    {
      auto neighborhood = std::vector<ushort>();

      for (int ker_y = cell_y-kernel_left; ker_y < h; ++ker_y)
	for (int ker_x = cell_x-kernel_left; ker_x < cell_x+kernel_right; ++ker_x)
	  neighborhood.push_back(ptr_in[ker_x+ker_y*w]);
      
      ptr_out[cell_x+cell_y*w] = median_opt(neighborhood);

    }
  }

}

void
aux_median_blur_opt(unsigned char* ptr_in,
		    unsigned char* ptr_out,
		    int kernel, int w, int h)
{

  
  int kernel_size = kernel*kernel;

  auto kernel_right = kernel/2+1; // le nombre de pixels à droite de la cellule centrale
  auto kernel_left = kernel-kernel_right; // le nombre de pixels à gauche

  for (int cell_x = 0; cell_x < kernel_left; ++cell_x)
    for(int cell_y = 0; cell_y < h; cell_y++) // pour le bord de gauche
    {
      auto neighborhood = std::vector<ushort>();

      for (int ker_y = cell_y-kernel_left; ker_y < cell_y+kernel_right; ++ker_y)
	for (int ker_x = 0; ker_x < cell_x+kernel_right; ++ker_x)
	  neighborhood.push_back(ptr_in[ker_x+ker_y*w]);
      
      ptr_out[cell_x+cell_y*w] = median_opt(neighborhood);

    }
  for (int cell_x = w-kernel_right; cell_x < w; ++cell_x)
    for(int cell_y = 0; cell_y < h; cell_y++) // pour le bord de droite
    {
      auto neighborhood = std::vector<ushort>();

      for (int ker_y = cell_y-kernel_left; ker_y < cell_y+kernel_right; ++ker_y)
	for (int ker_x = cell_x-kernel_left; ker_x < w; ++ker_x)
	  neighborhood.push_back(ptr_in[ker_x+ker_y*w]);
      
      ptr_out[cell_x+cell_y*w] = median_opt(neighborhood);

    }
  std::vector<ushort> neighborhood;
  // traîtement principal
  for (int cell_x = kernel_left; cell_x < w-kernel_right; ++cell_x) // traîtement principal
  {
    neighborhood = std::vector<ushort>(kernel_size, 0);
    for (int ker_y = -kernel_left; ker_y < kernel_right; ++ker_y) // pour le bord en haut
    {
      for (int ker_x = cell_x-kernel_left; ker_x < cell_x+kernel_right; ++ker_x)
      {
	int index = ker_x+ker_y*w;
	int vec_index =
	  (ker_x - cell_x + kernel_left) // va de 0 jusqu'à kernel (prouvé)
	  + (ker_y+kernel_left)*kernel;
	/*
	std::cout << "index: " << index
		  << "    vec_index: " << vec_index << "/" << neighborhood.size() << std::endl;
	*/
	neighborhood[vec_index] = *(ptr_in+index);
      }
    }
    
    for (int cell_y = 0; cell_y < h; ++cell_y)
    {
      /*
      std::cout << "w " << w
       	      << "  h " << h
     	      << "  cell_x " << cell_x
       	      << "  cell_y " << cell_y << std::endl;
      std::cout << "real_size " << neighborhood.size()
      		<< "  kernel " << kernel << std::endl;
      */
      int cell_index = cell_x+cell_y*w;
      for (int ker_x = cell_x-kernel_left; ker_x < cell_x+kernel_right; ++ker_x)
      {
     	int ker_y = (cell_y+kernel_right-1); // la ligne à ajouter
      	int index = ker_x+ker_y*w;
     	int vec_index =
     	  (ker_x - cell_x + kernel_left) // va de 0 jusqu'à kernel (prouvé)
     	  + (ker_y%kernel)*kernel;
            	
       	
     	neighborhood[vec_index] = ptr_in[index];
      }
      
      ptr_out[cell_index] = median_opt(neighborhood);
      
    }
  }
  

  
}




void
median_blur_opt_thread(cv::InputArray src,
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


  auto params = thread_parameters{ptr_in, ptr_out, kernel, w, h};
  //std::thread t1(aux_median_blur_opt, params);


  int n_threads = 4;
  
  auto threads = std::vector<std::thread>();
  for (int i = 0; i < n_threads; ++i)
  {
    int displacement = i*(w*h/n_threads)+(kernel-kernel/2-1)*w;
    std::thread t(aux_median_blur_opt,
		  ptr_in+displacement,
		  ptr_out+displacement,
		  kernel,
		  w,
		  min(h/n_threads, h-displacement/w-kernel/2-1));
    
    threads.push_back(std::move(t));
  }
  /*
  int displacement = (n_threads-1)*(w*h/n_threads)+(kernel-kernel/2-1)*w;
  std::cout << "UwU "<< displacement/w << "/"<<h<<std::endl;
  std::thread tuturu(aux_median_blur_opt,
		ptr_in+displacement,
		ptr_out+displacement,
		kernel,
		w,
		h-displacement-kernel);
  threads.push_back(std::move(tuturu));
  */
  for (int i = 0; i < n_threads; ++i)
  {
    threads[i].join();
  }
  top_and_bottom_border(ptr_in, ptr_out, kernel, w, h, n_threads);


/*
aux_median_blur_opt(ptr_in,
		      ptr_out,
		      kernel,
		      w,
		      h/n_threads);
*/
  std::cout <<"MAIS\n";
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
      ptr_out[i+j*w] = median_opt(neighborhood);
    }
  }

  
  dst.assign(mat_out);

}

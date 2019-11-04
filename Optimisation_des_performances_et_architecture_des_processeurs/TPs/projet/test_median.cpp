/*

#include<iostream>
#include<vector>

const int w = 9;
const int h = 9;
const ushort data[w*h] =
  {0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 255, 0, 0, 0, 0, 20, 0, 0,
   0, 0, 1, 0, 0, 0, 110, 0, 0,
   0, 0, 241, 0, 0, 10, 0, 0, 0,
   0, 0, 12, 0, 0, 0, 0, 0, 0,
   0, 0, 111, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 222, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 222, 0, 0, 0,
   0, 0, 0, 5, 0, 0, 0, 0, 0
  };

ushort output[w*h];

const int kernel = 3;
const int kernel_size = kernel*kernel;


auto head = std::vector<ushort>(kernel_size, 0);

void
swap(ushort* ptr1, ushort* ptr2)
{
  const auto lol = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = lol;
}

int
partition(ushort* ptr, int start, int end)
{
  auto i_pivot = start; // "random" pivot
  auto pivot = ptr[i_pivot];
  swap(ptr, ptr+i_pivot);  
  for (int j = start+1; j < end; ++j)
  {
    if (ptr[j] < pivot)
    {
      swap(ptr+j, ptr+i_pivot+1);
      swap(ptr+i_pivot, ptr+i_pivot+1);
      i_pivot++;
    }
  }

  std::cout << "PARTITION";
  for (int k = 0; k <= i_pivot; ++k)
    std::cout << " " << ptr[k];
  std::cout << "  | ";
  for (int k = i_pivot+1; k < end; ++k)
    std::cout << " " << ptr[k];
  std::cout << std::endl;
  return i_pivot;
}

ushort
ith(ushort* ptr, int start, int end, int i)
{
  if (start + 1 == end || i == start)
    return ptr[start];
  
  int pivot = partition(ptr, start, end);
  std::cout << "i_pivot " << pivot << "  pivot " << ptr[pivot] <<" i " << i
	    << "   start " << start
	    << "   end " << end
	    << std::endl;
  if (pivot == i)
  {
    return ptr[i];
  }
  else if (pivot < i)
  {
    return ith(ptr, pivot+1, end, i);
  }
  else
  {
    return ith(ptr, start, pivot, i);
  }
}

ushort
median_filter(int i, int j)
{
  int index = 0;
  for (int x = i; x < i+kernel; ++x)
  {
    for (int y = j; y < j+kernel; ++y)
    {
      head[index] = data[x+y*w];
      ++index;
    }
  }

  return head[2];
  
}

void
print(const ushort* ptr)
{
  for (int i = 0; i < w; ++i)
  {
    for (int j = 0; j < h; ++j)
    {
      std::cout << ptr[i+j*w] << " ";
    }
    std::cout << std::endl;
  }
}

int
main()
{
  for (int i = 0; i < w-kernel; ++i)
  {
    for (int j = 0; j < h-kernel; ++j)
    {
      output[i+j*w] = median_filter(i, j);
    }
  }
  
  print(data);
  std::cout << std::endl;
  print(output);

  ushort lol[8] = {100, 9, 4, 5, 6, 66, 0, 1};

  std::cout << ith(lol, 0, 8, 1) << std::endl;
  std::cout << "ololol " << ith(lol, 0, 8, 0) << std::endl;
  std::cout << ith(lol, 0, 8, 2) << std::endl;
  std::cout << ith(lol, 0, 8, 3) << std::endl;
  std::cout << ith(lol, 0, 8, 4) << std::endl;
  for (int i = 0; i < 8; ++i)
    std::cout << lol[i] << " ";
  std::cout << std::endl;
  std::cout << ith(lol, 0, 8, 1) << std::endl;
  for (int i = 0; i < 8; ++i)
    std::cout << lol[i] << " ";
  std::cout << std::endl;
  std::cout << ith(lol, 0, 8, 1) << std::endl;
  std::cout << ith(lol, 0, 8, 1) << std::endl;

  for (int i = 0; i < 8; ++i)
    std::cout << lol[i] << " ";
  std::cout << std::endl;
  
}
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


int median5(std::vector<int> & A, int s)
{
    if ( A.size() <= s + 5 )
        return A[s];
   
    std::vector<int> B;
    for (int i=s;i < s + 5; i++)
        B.push_back(A[i]);
   
    sort ( B.begin(), B.end() );
    return B[2];
}

int computeKSmallest( std::vector<int> & A, int k )
{    
    int n = A.size();
   
    if (n == 1) {
        if ( k == 0) return A[0];
        else std::cout << "Error somewhere!\n";
    }
   
    std::vector<int> C;
   
    for (int i=0; i < A.size(); i+=5)
        C.push_back( median5( A, i ) );  
   
    int approximate_median = computeKSmallest( C, C.size() / 2 );    
   
    std::vector<int> A_small, A_big;
   
    for (int i=0; i < n; i++) {
        if ( A[i] < approximate_median ) A_small.push_back( A[i] );
        else if (A[i] > approximate_median)  A_big.push_back( A[i] );
    }
   
    if ( k+1 <= A_small.size() ) return computeKSmallest( A_small, k );
    if ( k+1 > n - A_big.size() ) return computeKSmallest( A_big, k - ( n - A_big.size() ) );
    else return approximate_median;
}



int main()
{
    std::vector<int> A = {1, 2, 3, 5, 9,3 ,5 ,8 , 12, 4, 8, 0, 4, 7, 21, 45, 47};
    int n = A.size();
   
    int answer = computeKSmallest( A, 10 );
    std::cout << answer << std::endl;  
   
    return 0;
}

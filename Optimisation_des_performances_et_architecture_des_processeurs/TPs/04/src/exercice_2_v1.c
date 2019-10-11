#include<stdio.h>
#include<stdlib.h>

typedef struct Mat
{
  int* data;
  int** matrix;
} realMat, *Mat;

Mat
new_matrix(int size)
{
  int* data = malloc(sizeof(int)*size*size);
  int** mat = malloc(sizeof(int*)*size);

  for (int i = 0; i < size; i++)
  {
    mat[i] = &data[i*size];
  }


  Mat test = malloc(sizeof(realMat));

  test->data = data;
  test->matrix = mat;
  
  return test;
}

void
free_matrix(Mat mat)
{
  free(mat->data);
  free(mat->matrix);
  free(mat);
}



int
main(void)
{
  int size = 1000;
  

  Mat mat_a = new_matrix(size);
  Mat mat_b = new_matrix(size);


  for (int i = 0; i < size*size; i++)
  {
    mat_a->data[i] = rand();
  }


  for (int i = 1; i < size-1; i++)
  {
    for (int j = 1; j < size-1; j++)
    {
      mat_b->matrix[i][j] =
	(mat_a->matrix[i-1][j-1]
	 + mat_a->matrix[i][j-1]
	 + mat_a->matrix[i+1][j-1]
	 + mat_a->matrix[i-1][j]
	 + mat_a->matrix[i][j]
	 + mat_a->matrix[i+1][j]
	 + mat_a->matrix[i-1][j+1]
	 + mat_a->matrix[i][j+1]
	 + mat_a->matrix[i+1][j+1]);
    }
  }

  


  
  free_matrix(mat_a);
  free_matrix(mat_b);

  
  return 0;
}

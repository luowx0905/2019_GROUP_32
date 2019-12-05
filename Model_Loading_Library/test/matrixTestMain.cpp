#include "matrix.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
int main()
{
  cout<<"Making two 3x3 vectors"<<endl;
  Matrix matrix1(3,3);
  Matrix matrix2(3,3);
  cout<<"Matrix1:\n"<<matrix1<<"\nMatrix2:\n"<<matrix2<<endl;
  cout<<"Populating vectors with random numbers between 0 and 9"<<endl;
  for(int cols = 0; cols < 3; cols++)
  {
    for(int rows = 0; rows < 3; rows++)
    {
      matrix1(cols,rows) = rand()%10;
      matrix2(cols,rows) = rand()%10;
    }
  }
  cout<<"Matrix1:\n"<<matrix1<<"\nMatrix2:\n"<<matrix2<<endl;
  cout<<"Multiplying them together\n"<<matrix1*matrix2<<endl;
  cout<<"Adding them together\n"<<matrix1+matrix2<<endl;
  cout<<"Subtracting matrix2 from matrix1\n"<<matrix1-matrix2<<endl;
  cout<<"Finding the inverse of matrix1\n"<<matrix1.inv()<<endl;
}

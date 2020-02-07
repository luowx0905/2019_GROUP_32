#define _USE_MATH_DEFINES
#include "matrix.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cmath>
using namespace std;
int main()
{
  srand(time(NULL));
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

  Vector vector1(1,-5,10);
  cout<<"Vector1:\n"<<vector1<<endl;
  Matrix zRot = Matrix::genRotationMatrix('z',M_PI/2);
  Matrix yRot = Matrix::genRotationMatrix('y',M_PI/2);
  Matrix xRot = Matrix::genRotationMatrix('x',M_PI/2);
  cout<<"Vector1 rotated by pi/2 rads in the z plane is:\n"<< (Matrix(vector1)*zRot).convertToVector() << endl;
  cout<<"Vector1 rotated by pi/2 rads in the y plane is:\n"<< (Matrix(vector1)*yRot).convertToVector() << endl;
  cout<<"Vector1 rotated by pi/2 rads in the x plane is:\n"<< (Matrix(vector1)*xRot).convertToVector() << endl;
}

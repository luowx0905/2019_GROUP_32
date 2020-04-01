#define _USE_MATH_DEFINES
#include "matrix.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cmath>
using namespace std;
int main()
{
  //make empty matricies
  Matrix matrix1(3,3);
  Matrix matrix2(3,3);

  //populate matricies
  for(int cols = 0; cols < 3; cols++)
  {
    for(int rows = 0; rows < 3; rows++)
    {
      matrix1(cols,rows) = cols*rows;
      matrix2(cols,rows) = cols+rows;
    }
  }
  Matrix multAns(3,3);
  multAns(0,0) = 0;
  multAns(0,1) = 0;
  multAns(0,2) = 0;
  multAns(1,0) = 5;
  multAns(1,1) = 8;
  multAns(1,2) = 11;
  multAns(2,0) = 10;
  multAns(2,1) = 16;
  multAns(2,2) = 22;
  bool MULT_STATUS = (matrix1 * matrix2 == multAns);
  
  Matrix addAns(3,3);
  addAns(0,0) = 0;
  addAns(0,1) = 1;
  addAns(0,2) = 2;
  addAns(1,0) = 1;
  addAns(1,1) = 3;
  addAns(1,2) = 5;
  addAns(2,0) = 2;
  addAns(2,1) = 5;
  addAns(2,2) = 8;
  bool ADD_STATUS = (matrix1 + matrix2 == addAns);

  Matrix subAns(3,3);
  subAns(0,0) =  0;
  subAns(0,1) = -1;
  subAns(0,2) = -2;
  subAns(1,0) = -1;
  subAns(1,1) = -1;
  subAns(1,2) = -1;
  subAns(2,0) = -2;
  subAns(2,1) = -1;
  subAns(2,2) =  0;
  bool SUB_STATUS = (matrix1 - matrix2 == subAns);

  //bool INV_STATUS
  //bool ROT_STATUS



  /*Vector vector1(1,-5,10);
  Matrix zRot = Matrix::genRotationMatrix('z',M_PI/2);
  Matrix yRot = Matrix::genRotationMatrix('y',M_PI/2);
  Matrix xRot = Matrix::genRotationMatrix('x',M_PI/2);
  cout<<"Vector1 rotated by pi/2 rads in the z plane is:\n"<< (Matrix(vector1)*zRot).convertToVector() << endl;
  cout<<"Vector1 rotated by pi/2 rads in the y plane is:\n"<< (Matrix(vector1)*yRot).convertToVector() << endl;
  cout<<"Vector1 rotated by pi/2 rads in the x plane is:\n"<< (Matrix(vector1)*xRot).convertToVector() << endl;*/
  return (MULT_STATUS && ADD_STATUS && SUB_STATUS) ? 0 : 1;
}

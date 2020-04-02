#define _USE_MATH_DEFINES
#include "matrix.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cmath>
using namespace std;
int main(int argc, char *argv[])
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
  //Test multiplication operator
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
  
  //Test addition operator
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

  //Test subtraction operator
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

  //Test alt constructor, rotation matricies and convertToVector. @Note dependant on vector class so vector should be tested first
  Vector vector1(1,-5,10);
  Matrix zRot = Matrix::genRotationMatrix('z',M_PI/2);
  Matrix yRot = Matrix::genRotationMatrix('y',M_PI/2);
  Matrix xRot = Matrix::genRotationMatrix('x',M_PI/2);

  bool ROT_STATUS = ((Matrix(vector1)*zRot).convertToVector() == Vector(1,10,5)   && 
                     (Matrix(vector1)*yRot).convertToVector() == Vector(-10,-5,1) &&
                     (Matrix(vector1)*xRot).convertToVector() == Vector(-5,-1,10));
  //cout<<"ROT:"<<ROT_STATUS<<endl;

  //Test transpose function
  Matrix tranAns(3,3);
  tranAns(0,0) = 0;
  tranAns(0,1) = 5;
  tranAns(0,2) = 10;
  tranAns(1,0) = 0;
  tranAns(1,1) = 8;
  tranAns(1,2) = 16;
  tranAns(2,0) = 0;
  tranAns(2,1) = 11;
  tranAns(2,2) = 22;
  bool TRAN_STATUS = (multAns.transpose() == tranAns);
  //cout<<"TRAN:"<<TRAN_STATUS<<endl;

  //Test Determinant
  matrix2(0,0) = 1;
  bool DET_STATUS = (matrix2.det() == -1);
  //cout<<"DET:"<<DET_STATUS<<endl;

  //Test Inverse
  Matrix invAns(3,3);
  invAns(0,0) = 1;
  invAns(0,1) = -2;
  invAns(0,2) = 1;
  invAns(1,0) = -2;
  invAns(1,1) = 0;
  invAns(1,2) = 1;
  invAns(2,0) = 1;
  invAns(2,1) = 1;
  invAns(2,2) = -1;
  bool INV_STATUS = (matrix2.inv() == invAns);
  //cout<<"INV:"<<INV_STATUS<<endl;

  //Test getters
  Matrix nonSquareMatrix(5,9);
  bool GET_STATUS = (nonSquareMatrix.getRow() == 5 && nonSquareMatrix.getCol() == 9 && 
                     nonSquareMatrix.getSize() == 45);
  //cout<<"GET:"<<GET_STATUS<<endl;

  //Test scale
  Matrix scaleAns(3,3);
  scaleAns(0,0) = 3;
  scaleAns(0,1) = -6;
  scaleAns(0,2) = 3;
  scaleAns(1,0) = -6;
  scaleAns(1,1) = 0;
  scaleAns(1,2) = 3;
  scaleAns(2,0) = 3;
  scaleAns(2,1) = 3;
  scaleAns(2,2) = -3;
  bool SCALE_STATUS = (invAns.scale(3) == scaleAns);

  return (MULT_STATUS  && ADD_STATUS && SUB_STATUS && ROT_STATUS &&
          TRAN_STATUS  && DET_STATUS && INV_STATUS && GET_STATUS &&
          SCALE_STATUS ) ? 0 : 1;
}

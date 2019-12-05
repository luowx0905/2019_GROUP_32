#include "matrix.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
int main()
{
  cout<<"Making a 3x3 vector"<<endl;
  Matrix myMatrix(3,3);
  cout<<myMatrix<<endl;
  cout<<"Populating vector with random numbers between 0 and 9"<<endl;
  for(int cols = 0; cols < myMatrix.getCol(); cols++)
  {
    for(int rows = 0; rows < myMatrix.getRow(); rows++)
    {
      myMatrix(cols,rows) = rand()%10;
    }
  }
  cout<<myMatrix<<endl;
  cout<<"Finding the inverse of this matrix\n"<<myMatrix.inv()<<endl;
}

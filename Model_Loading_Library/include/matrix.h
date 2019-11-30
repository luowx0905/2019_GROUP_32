#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <vector>
#include <iostream>
#include "vector.h"
using namespace std;
class Matrix
{
public:
    Matrix(); //zero matrix
    Matrix(const float& r1c1,      const float& r1c2,      const float& r1c3, 
           const float& r2c1 = 0., const float& r2c2 = 0., const float& r2c3 = 0., 
           const float& r3c1 = 0., const float& r3c2 = 0., const float& r3c3 = 0.); //Defaults to row matrix if only three values given
    Matrix(const Matrix& m); //copy

    //For calculations, vector treated as a 3x1 column matrix
    const Matrix& operator=(const Matrix&);
    Matrix operator+(const Matrix& m);
    Matrix operator+(const Vector& v);
    Matrix operator-(const Matrix& m);
    Matrix operator-(const Vector& v);
    Matrix operator*(const Matrix& m);
    Matrix operator*(const Vector& v);

    void invertMatrix();
    void transposeMatrix();

    friend ostream& operator<<(ostream& out, const Matrix& m);
private:
    vector<vector<float>> matrixData;
    void setMatrixData(int row, int column, float val);
};  
#endif //MATRIX_H_INCLUDED
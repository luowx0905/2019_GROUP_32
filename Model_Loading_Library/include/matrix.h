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
    Vector operator*(const Vector& v);
    Matrix operator/(const float& f);

    Matrix calculateInverseMatrix();
    Matrix calculateTransposedMatrix();
    vector<float> getColumn(int column, const Matrix& m);

    friend ostream& operator<<(ostream& out, const Matrix& m);
private:
    vector<vector<float>> matrixData;
    
};  
float getDotProduct(vector<float> m, vector<float> n);
float getDotProduct(vector<float> m, const Vector& v);

#endif //MATRIX_H_INCLUDED
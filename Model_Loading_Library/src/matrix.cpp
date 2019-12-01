#include "matrix.h"
#include "vector.h"
//default constructor (zero matrix)
Matrix::Matrix() 
{
    matrixData.resize(3);
    matrixData[0].resize(3);
    matrixData[1].resize(3);
    matrixData[2].resize(3);
    matrixData[0] = {0,0,0};
    matrixData[1] = {0,0,0};
    matrixData[2] = {0,0,0};
}

//3x3 matrix constructor
Matrix::Matrix(const float& r1c1, const float& r1c2, const float& r1c3,const float& r2c1, const float& r2c2, const float& r2c3,const float& r3c1, const float& r3c2, const float& r3c3)
{
    matrixData.resize(3);
    matrixData[0].resize(3);
    matrixData[1].resize(3);
    matrixData[2].resize(3);
    matrixData[0] = {r1c1,r1c2,r1c3};
    matrixData[1] = {r2c1,r2c2,r2c3};
    matrixData[2] = {r3c1,r3c2,r3c3};
}
Matrix::Matrix(const Matrix& m)
{
    matrixData = m.matrixData;
}
//operator= overload function
const Matrix& Matrix::operator=(const Matrix& m)
{
    if(this==&m) return (*this);
    this->matrixData = m.matrixData;
    return(*this);
}

Matrix Matrix::operator+(const Matrix& m)
{
    Matrix temp;
    for(int i = 0; i < m.matrixData.size(); i++)
        for(int j = 0; j < m.matrixData.size(); j++)
            temp.matrixData[i][j] = this->matrixData[i][j] + m.matrixData[i][j];
    return temp;
}
Matrix Matrix::operator+(const Vector& v) //vector treated as 3x1 column matrix
{
    Matrix temp;
    temp.matrixData[0][0] = this->matrixData[0][0] + v.get_i();
    temp.matrixData[1][0] = this->matrixData[1][0] + v.get_j();
    temp.matrixData[2][0] = this->matrixData[2][0] + v.get_k();
    return temp;
}
Matrix Matrix::operator-(const Matrix& m)
{
    Matrix temp;
    for(int i = 0; i < m.matrixData.size(); i++)
        for(int j = 0; j < m.matrixData.size(); j++)
            temp.matrixData[i][j] = this->matrixData[i][j] - m.matrixData[i][j];
    return temp;
}
Matrix Matrix::operator-(const Vector& v)
{
    Matrix temp;
    temp.matrixData[0][0] = this->matrixData[0][0] - v.get_i();
    temp.matrixData[1][0] = this->matrixData[1][0] - v.get_j();
    temp.matrixData[2][0] = this->matrixData[2][0] - v.get_k();
    return temp;
}
Matrix Matrix::operator*(const Matrix& m)
{
    Matrix temp;
    for(int i = 0; i < this->matrixData.size(); i++)
        for(int j = 0; j < this->matrixData[0].size(); j++)
            temp.matrixData[i][j] = getDotProduct(this->matrixData[i],getColumn(j,m));
    return temp;
}
Vector Matrix::operator*(const Vector& v)
{
    /*Matrix temp;
    temp.matrixData[0][0] = getDotProduct(this->matrixData[0],v);
    temp.matrixData[1][0] = getDotProduct(this->matrixData[1],v);
    temp.matrixData[2][0] = getDotProduct(this->matrixData[2],v);*/
    Vector temp(getDotProduct(this->matrixData[0],v),getDotProduct(this->matrixData[1],v),getDotProduct(this->matrixData[2],v));
    return temp;
}
Matrix Matrix::operator/(const float& f)
{
    Matrix temp;
    for(int i = 0; i < this->matrixData.size(); i++)
        for(int j = 0; j < this->matrixData.size(); j++)
            temp.matrixData[i][j] = this->matrixData[i][j] / f;
    return temp;
}
Matrix Matrix::calculateInverseMatrix()
{
    float determinant = matrixData[0][0]*(matrixData[1][1]*matrixData[2][2] - matrixData[1][2]*matrixData[2][1])
                      - matrixData[0][1]*(matrixData[1][0]*matrixData[2][2] - matrixData[1][2]*matrixData[2][0])
                      + matrixData[0][2]*(matrixData[1][0]*matrixData[2][1] - matrixData[1][1]*matrixData[2][0]);
    if(determinant==0)
    {
        cerr << "no inverse exists\n";
        return (*this);
    }
    Matrix transposed = this->calculateTransposedMatrix();
    cout<<transposed<<endl;
    Matrix adjoint;
    for(int i = 0; i < this->matrixData.size(); i++)
    {
        for(int j = 0; j < this->matrixData.size(); j++)
        {   //modulo equations select cofactors
            adjoint.matrixData[i][j] = transposed.matrixData[(i+1)%3][(j+1)%3]*transposed.matrixData[(i+2)%3][(j+2)%3]
                                     - transposed.matrixData[(i+1)%3][(j+2)%3]*transposed.matrixData[(i+2)%3][(j+1)%3]; 
        }
    }
    return adjoint/determinant;
}
Matrix Matrix::calculateTransposedMatrix()
{
    Matrix temp;
    temp.matrixData[0] = getColumn(0,*this);
    temp.matrixData[1] = getColumn(1,*this);
    temp.matrixData[2] = getColumn(2,*this);
    return temp;
}
float getDotProduct(vector<float> m, vector<float> n)
{
    return (m[0] * n[0] + m[1] * n[1] + m[2] * n[2]);
}
float getDotProduct(vector<float> m, const Vector& v)
{
    return (m[0] * v.get_i() + m[1] * v.get_j() + m[2] * v.get_k());
}
vector<float> Matrix::getColumn(int column, const Matrix& m)
{
    vector<float> temp;
    temp.resize(3);
    temp[0] = m.matrixData[0][column];
    temp[1] = m.matrixData[1][column]; 
    temp[2] = m.matrixData[2][column];
    return temp;
}
ostream& operator<<(ostream& out, const Matrix& m)
{
    for(int i = 0; i < m.matrixData.size(); i++)
    {
        out << "(";
        for(int j = 0; j < m.matrixData[0].size(); j++)
        {
            out << m.matrixData[i][j] << ",";
        }
        out << ")" << endl;
    }
	return out;
}         
#include "matrix.h"

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
        for(int j = 0; j < m.matrixData.size(); i++)
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
        for(int j = 0; j < m.matrixData.size(); i++)
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
    return Matrix();
}
Matrix Matrix::operator*(const Vector& v)
{
    return Matrix();
}

void Matrix::setMatrixData(int row, int, column, float val)
{
    this->matrixData[row][column] = val;
}
void Matrix::invertMatrix()
{

}
void Matrix::transposeMatrix()
{

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
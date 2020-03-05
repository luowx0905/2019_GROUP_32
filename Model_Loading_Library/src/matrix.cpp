#include <iostream>
#include <stdexcept>
#include <cmath>
#include "matrix.h"

using namespace std;

// default constructor
Matrix::Matrix()
{
	row = 0;
	col = 0;
	size = 0;
	data = nullptr;
}

// the size of generated matrix is row * col
Matrix::Matrix(int row, int col)
{
	if (row > 0 && col > 0)
	{
		this->row = row;
		this->col = col;
		size = row * col;

		// dynamic memory allocation for two dimensional array
		data = new double* [row];
		for (size_t i = 0; i < row; i++)
		{
			data[i] = new double[col];
		}

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				data[i][j] = 0; // initialize all the elements in the matrix to 0
			}
		}
	}
	else
	{
		// if the size of matrix is invalid an exception would be thrown
		throw runtime_error("Invalid size");
	}
}
Matrix::Matrix(Vector v)
{
	this->row = 1;
	this->col = 3;
	this->size = 3;
	// dynamic memory allocation for two dimensional array
	data = new double* [row];
	for (size_t i = 0; i < row; i++)
	{
		data[i] = new double[col];
	}
	data[0][0] = v.get_i();
	data[0][1] = v.get_j();
	data[0][2] = v.get_k();
}
// copy constructor
Matrix::Matrix(const Matrix& m)
{
	row = m.row;
	col = m.col;
	size = row * col;

	data = new double* [row];
	for (size_t i = 0; i < row; i++)
	{
		data[i] = new double[col];
	}

	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			data[i][j] = m.data[i][j]; // copy all the elements in another matrix
		}
	}
}

// destructor
Matrix::~Matrix()
{
	// delete the menory
	for (size_t i = 0; i < row; i++)
	{
		delete[] data[i];
	}
	delete[] data;
}

// overload assignment operator
Matrix& Matrix::operator=(const Matrix& m)
{
	if (this != &m) // avoid self assignment
	{
		row = m.row;
		col = m.col;

		data = new double* [row];
		for (size_t i = 0; i < row; i++)
		{
			data[i] = new double[col];
		}

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				data[i][j] = m.data[i][j]; // copy all the elements
			}
		}
	}

	return *this;
}

// overload plus operator
Matrix Matrix::operator+(const Matrix& m)
{
	if (row == m.row && col == m.col) // check the size of two matrix
	{
		Matrix temp(row, col); // store the result

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				temp.data[i][j] = data[i][j] + m.data[i][j];
			}
		}

		return temp;
	}
	else
	{
		// if the size are incompatible an exception would be thrown
		throw runtime_error("operator+ -- size mismatch");
	}
}

// overload minus operator
Matrix Matrix::operator-(const Matrix& m)
{
	if (row == m.row && col == m.col)
	{
		Matrix temp(row, col);

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				temp.data[i][j] = data[i][j] - m.data[i][j];
			}
		}

		return temp;
	}
	else
	{
		throw runtime_error("operator- -- size mismatch");
	}
}

// overload multiply operator
Matrix Matrix::operator*(const Matrix& m)
{
	if (col == m.row)
	{
		Matrix temp(row, m.col);

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < m.col; j++)
			{
				for (size_t k = 0; k < col; k++)
				{
					temp.data[i][j] += data[i][k] * m.data[k][j];
				}
			}
		}

		return temp;
	}
	else
	{
		throw runtime_error("operator* -- size mismatch");
	}
}

// overload the bracket, this operator could return a reference of the specfic element (lvalue)
double& Matrix::operator()(size_t row, size_t col)
{
	if (row < this->row && col < this->col) // check the validation of the index
	{
		return data[row][col];
	}
	else
	{
		// if the index is out of range an exception would be thrown
		throw runtime_error("Index out of range");
	}
}

// overload the bracket, this operator could return a value of the specfic element (rvalue)
double Matrix::operator()(size_t row, size_t col) const
{
	if (row < this->row && col < this->col)
	{
		return data[row][col];
	}
	else
	{
		throw runtime_error("Index out of range");
	}
}

// overload operator to check if two matrix is equal
bool Matrix::operator==(const Matrix& m)
{
	if (row == m.row && col == m.col)
	{
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				if (data[i][j] != m.data[i][j])
				{
					return false;
				}
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

// overload operator to check if two matrix is not equal
bool Matrix::operator!=(const Matrix& m)
{
	return !(*this == m);
}

// obatin the transpose matrix
Matrix Matrix::transpose()
{
	Matrix temp(col, row);

	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			temp.data[j][i] = data[i][j];
		}
	}

	return temp;
}

// obtain the determinant of the matrix
// this function would first copy the original matrix and
// then convert the copy to an upper triangle matrix
// in the upper triangle matrix, the product of all the elements
// on the diagonal is the determinant of the original matrix
double Matrix::det() const
{
	if (row == col) // ensure the matrix is a square matrix
	{
		if (row == 1)
		{
			return data[0][0];
		}
		else if (row == 2)
		{
			return data[0][0] * data[1][1] - data[0][1] * data[1][0];
		}
		else
		{
			Matrix copy(*this); // copy the original matrix
			double result = 1;
			int swap = 0; // record the times that any two rows are swapped

			// this for loop would convert the copy to an upper triangle matrix
			for (size_t i = 0; i < row - 1; i++)
			{
				size_t next;
				bool nonZero = false;
				if (copy.data[i][i] == 0)
				{
					for (next = i + 1; next < row; next++)
					{
						if (copy.data[next][i] != 0)
						{
							nonZero = true;
							break;
						}
					}

					if (!nonZero)
					{
						continue;
					}

					// swap these two rows
					swap++;
					for (size_t j = 0; j < col; j++)
					{
						double temp = copy.data[i][j];
						copy.data[i][j] = copy.data[next][j];
						copy.data[next][j] = temp;
					}
				}

				// use Gaussian elimination method
				for (next = i + 1; next < row; next++)
				{
					double factor = copy.data[next][i] / copy.data[i][i];
					for (size_t k = 0; k < row; k++)
					{
						copy.data[next][k] += -factor * copy.data[i][k];
					}
				}
			}

			// obtain the product of all the elements on the diagonal
			for (size_t i = 0; i < row; i++)
			{
				result *= copy.data[i][i];
			}

			// one of the properties of matrix is
			// if two rows or columns are interchanged, then the sign of
			// the determinant changes, so if variable swap is an even number
			// the determinant is the same, otherwise determinant is -result
			if (swap % 2 == 0)
			{
				return result;
			}
			else
			{
				return -result;
			}
		}
	}
	else
	{
		throw runtime_error("The determinant is invalid");
	}
}

// obtain inverse matrix
// the inverse matrix is all the elements in the adjugate matrix
// multiply 1/determinant
Matrix Matrix::inv()
{
	if (row != col) // ensure the matrix is a square matrix
	{
		throw runtime_error("No inverse matrix");
	}

	double determinant = this->det();
	if (determinant != 0)// ensure the matrix is nonsingular matrix
	{
		Matrix temp = this->adjugate().scale(1 / determinant);
		return temp;
	}
	else
	{
		throw runtime_error("No inverse matrix");
	}
}

// overload stream inseration operator
ostream& operator<<(ostream& out, const Matrix& m)
{
	for (size_t i = 0; i < m.row; i++)
	{
		for (size_t j = 0; j < m.col; j++)
		{
			out << m.data[i][j] << '\t';
		}
		out << endl;
	}

	return out;
}

// get number of row
int Matrix::getRow() const
{
	return row;
}

// get the number of column
int Matrix::getCol() const
{
	return col;
}

// get the number of elements
int Matrix::getSize() const
{
	return size;
}

// all the elements in the matrix multiply a constant
Matrix Matrix::scale(double size)
{
	Matrix temp(*this);

	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			temp.data[i][j] = data[i][j] * size;
		}
	}

	return temp;
}

// return a submatrix
Matrix Matrix::subMat(int rowStart, int colStart, int rowEnd, int colEnd)
{
	if (rowEnd == 0 && colEnd == 0)
	{
		Matrix temp(row - rowStart, col - colStart);

		for (size_t i = rowStart, m = 0; i < row; i++, m++)
		{
			for (size_t j = colStart, n = 0; j < col; j++, n++)
			{
				temp.data[m][n] = data[i][j];
			}
		}

		return temp;
	}
	else if (rowStart <= rowEnd && colStart <= colEnd && rowEnd < row && colEnd < col)
	{
		Matrix temp(rowEnd - rowStart + 1, colEnd - colStart + 1);

		for (size_t i = rowStart, m = 0; i <= rowEnd; i++, m++)
		{
			for (size_t j = colStart, n = 0; j <= colEnd; j++, n++)
			{
				temp.data[m][n] = data[i][j];
			}
		}

		return temp;
	}
	else
	{
		throw runtime_error("Submatrix size error");
	}
}

// obtain the minor of the specific element
Matrix Matrix::minor_(int row, int col)
{
	Matrix temp(this->row - 1, this->col - 1);

	for (size_t i = 0, m = 0; i < this->row; i++)
	{
		if (i == row)
		{
			continue;
		}
		for (size_t j = 0, n = 0; j < this->col; j++)
		{
			if (j == col)
			{
				continue;
			}

			temp.data[m][n] = data[i][j];
			n++;
		}
		m++;
	}

	return temp;
}

// obtain the cofactor of the specific element
Matrix Matrix::cofactor(int row, int col)
{
	Matrix temp = this->minor_(row, col);

	temp = temp.scale(pow(-1, row + col));

	return temp;
}

// obtain the adjugate matrix
Matrix Matrix::adjugate()
{
	Matrix result(row, col);

	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			Matrix temp = this->minor_(i, j);
			double determinant = temp.det() * pow(-1, i + j);
			result.data[j][i] = determinant;
		}
	}

	return result;
}
Matrix Matrix::genRotationMatrix(char plane, double angle)
{
	Matrix temp(3,3);
	if (plane == 'Z' || plane == 'z')
	{
		temp(0,0) = 1;
		temp(1,1) = cos(angle);
		temp(1,2) = -1 * sin(angle);
		temp(2,1) = sin(angle);
		temp(2,2) = cos(angle);
	}
	else if (plane == 'Y' || plane == 'y')
	{
		temp(0,0) = cos(angle);
		temp(0,2) = sin(angle);
		temp(1,1) = 1;
		temp(2,0) = -1 * sin(angle);
		temp(2,2) = cos(angle);
	}
	else if (plane == 'X' || plane == 'x')
	{
		temp(0,0) = cos(angle);
		temp(0,1) = -1 * sin(angle);
		temp(1,0) = sin(angle);
		temp(1,1) = cos(angle);
		temp(2,2) = 1;
	}
	else
	{
		throw runtime_error("Rotation plane is invalid");
	}
	return temp;
}
Vector Matrix::convertToVector()
{
	if(this->row == 1 && this->col == 3)
	{
		return Vector(this->data[0][0],this->data[0][1],this->data[0][2]);
	}
	else
	{
		throw runtime_error("Invalid matrix size to convert to vector");
	}
}

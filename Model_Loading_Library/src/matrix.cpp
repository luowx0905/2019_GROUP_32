#include <iostream>
#include <stdexcept>
#include "matrix.h"

using namespace std;

Matrix::Matrix()
{
	row = 0;
	col = 0;
	size = 0;
	data = nullptr;
}

Matrix::Matrix(int row, int col)
{
	if (row > 0 && col > 0)
	{
		this->row = row;
		this->col = col;
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
				data[i][j] = 0;
			}
		}
	}
	else
	{
		throw runtime_error("Invalid size");
	}
}

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
			data[i][j] = m.data[i][j];
		}
	}
}

Matrix::~Matrix()
{
	for (size_t i = 0; i < row; i++)
	{
		delete[] data[i];
	}
	delete[] data;
}

Matrix& Matrix::operator=(const Matrix& m)
{
	if (this != &m)
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
				data[i][j] = m.data[i][j];
			}
		}
	}

	return *this;
}

Matrix Matrix::operator+(const Matrix& m)
{
	if (row == m.row && col == m.col)
	{
		Matrix temp(row, col);

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
		throw runtime_error("operator+ -- size mismatch");
	}
}

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

Matrix Matrix::operator*(const Matrix& m)
{
	if (row == m.col && col == m.row)
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

double& Matrix::operator()(size_t row, size_t col)
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

bool Matrix::operator!=(const Matrix& m)
{
	return !(*this == m);
}

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

double Matrix::det() const
{
	if (row == col)
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
			double result = 1;
			bool nonZero = false;
			int swap = 0;

			for (size_t i = 0; i < row - 1; i++)
			{
				size_t next;
				if (data[i][i] == 0)
				{
					for (next = i + 1; next < row; next++)
					{
						if (data[i][i] != 0)
						{
							nonZero = true;
							break;
						}
					}

					if (!nonZero)
					{
						continue;
					}

					swap++;
					for (size_t j = 0; j < col; j++)
					{
						double temp = data[i][j];
						data[i][j] = data[next][j];
						data[next][j] = temp;
					}
				}

				for (next = i + 1; next < row; next++)
				{
					double factor = data[next][i] / data[i][i];
					for (size_t k = 0; k < row; k++)
					{
						data[next][k] += -factor * data[i][k];
					}
				}
			}

			for (size_t i = 0; i < row; i++)
			{
				result *= data[i][i];
			}

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

int Matrix::getRow() const
{
	return row;
}

int Matrix::getCol() const
{
	return col;
}

int Matrix::getSize() const
{
	return size;
}

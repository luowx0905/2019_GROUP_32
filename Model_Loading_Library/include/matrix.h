#ifndef MATRIX_H
#define MATRIX_H 

#include <iostream>
#include <stdexcept>

class Matrix
{
public:
	Matrix();
	Matrix(int row, int col);
	Matrix(const Matrix& m);
	~Matrix();
	
	Matrix& operator=(const Matrix& m);
	Matrix operator+(const Matrix& m);
	Matrix operator-(const Matrix& m);
	Matrix operator*(const Matrix& m);

	double& operator()(size_t row, size_t col);
	double operator()(size_t row, size_t col) const;

	bool operator==(const Matrix& m);
	bool operator!=(const Matrix& m);

	Matrix transpose();
	double det() const;
	
	friend std::ostream& operator<<(std::ostream& out, const Matrix& m);

	int getRow() const;
	int getCol() const;
	int getSize() const;

private:
	double** data;
	int row;
	int col;
	int size;
};

#endif // MATRIX_H
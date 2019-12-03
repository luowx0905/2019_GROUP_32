#ifndef MATRIX_H
#define MATRIX_H 

#include <iostream>
#include <stdexcept>

class Matrix
{
public:
	Matrix(); // default constructor
	Matrix(int row, int col);
	Matrix(const Matrix& m); // copy constructor
	~Matrix(); // destructor
	
	//// overload some useful operators
	Matrix& operator=(const Matrix& m); 
	Matrix operator+(const Matrix& m);
	Matrix operator-(const Matrix& m);
	Matrix operator*(const Matrix& m);

	double& operator()(size_t row, size_t col);
	double operator()(size_t row, size_t col) const;

	bool operator==(const Matrix& m);
	bool operator!=(const Matrix& m);

	Matrix transpose(); // obtain the transpose matrix
	double det() const; // obtain the determinant of the matrix
	Matrix inv(); //obtain the inverse matrix
	
	// overload stream insertion operator
	friend std::ostream& operator<<(std::ostream& out, const Matrix& m);

	int getRow() const; // get the number of row of the matrix
	int getCol() const; // get the number of column of the matrix
	int getSize() const; // get the number of element of the matrix

	Matrix scale(double size); // all elements in the matrix multiply a constant;
	Matrix subMat(int rowStart, int colStart, int rowEnd = 0, int colEnd = 0); // get submatrix
	Matrix minor(int row, int col); // get minor of the matrix
	Matrix cofactor(int row, int col); // get cofactor of the matrix
	Matrix adjugate(); // get the adjugate matrix

private:
	double** data; // store data in this pointer
	int row; // number of row
	int col; // number of column
	int size; // number of element
};

#endif // MATRIX_H

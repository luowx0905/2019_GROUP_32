//matrix.h
#ifndef MATRIX_H
#define MATRIX_H 

/** 
 * @file This file contains the declarations for the matrix class
 */

#include <iostream>
#include <stdexcept>
/** 
 * @brief Class for creating matrix object to use in matrix calculations
 * @author
 * @version 1.0
 * @date 05/12/2019
 */
class Matrix
{
public:
	///Default constructor
	Matrix();
	///@brief Constructs a matrix object of given dimensions
	///@param row number of rows the matrix will have
	///@param col number of columns the matrix will have
	Matrix(int row, int col);
	///Copy constructor
	Matrix(const Matrix& m);
	///Default destructor
	~Matrix(); 
	///operator= overload
	Matrix& operator=(const Matrix& m);
	///@brief overload matrix addition
	///@note matricies must have the same dimensions for matrix addition
	///@warning throws runtime error when there is a size mismatch 
	Matrix operator+(const Matrix& m);
	///@brief overload matrix subtraction
	///@note matricies must have the same dimensions for matrix subtraction
	///@warning throws runtime error when there is a size mismatch 
	Matrix operator-(const Matrix& m);
	///@brief overload matrix multiplication
	///@note when multiplying matricies, the first matrix must have as many columns as the second has rows. i.e 3xN * Nx3
	///@warning throws runtime error when there is a size mismatch
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

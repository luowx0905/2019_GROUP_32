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
 * @author Wenxiang Luo
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
	///@brief overload the bracket
	///@param row index of desired element's row
	///@param col index of desired element's column
	///@return reference to the desired element
	double& operator()(size_t row, size_t col);
	///@brief overload the bracket
	///@param row index of desired element's row
	///@param col index of desired element's column
	///@return value of the desired element
	double operator()(size_t row, size_t col) const;
	///@brief == comparison overload
	bool operator==(const Matrix& m);
	///@brief != comparison overload
	bool operator!=(const Matrix& m);
	///@brief transpose the current matrix
	///@return Transposed matrix as matrix object
	Matrix transpose();
	///@brief Obtain the determinant of the matrix
	///@warning if the matrix object is not square i.e NxN then a runtime error ('The determinent is invalid') is thrown
	///@return determinant of matrix as double
	double det() const;
	///@brief Obtain the inverse matrix
	///@warning if the matrix object is not square i.e NxN then a runtime error ('No inverse matrix') is thrown
	///@warning if the matrix has no inverse (determinant = 0) then a runtime error ('No inverse matrix') is thrown
	///@return inverse matrix as matrix object
	Matrix inv(); 

	///Overload stream insertion operator
	friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
	///@brief get the number of rows of the matrix
	///@return number of rows as int
	int getRow() const;
	///@brief get the number of columns of the matrix
	///@return number of columns as int
	int getCol() const;
	///@brief get the total number of elements in the matrix
	///@return size of matrix as int
	int getSize() const;
	///@brief multiply each element in the matrix by a constant
	///@param size constant to multiply the matrix elements by
	///@return Scaled matrix as matrix object
	Matrix scale(double size);
	///@brief obtain the submatrix
	///@param rowStart starting row index of desired submatrix
	///@param colStart starting column index of desired submatrix
	///@param rowEnd last row index of desired submatrix
	///@param colEnd last column index of desired submatrix
	///@return The submatrix as matrix object
	Matrix subMat(int rowStart, int colStart, int rowEnd = 0, int colEnd = 0);
	///@brief obtain the minor of an element in the matrix
	///@param row the row index of the element 
	///@param col the column index of the element
	///@return the minor of the element as a matrix object
	Matrix minor(int row, int col);
	///@brief obtain the cofactor matrix of an element in the matrix
	///@param row the row index of the element
	///@param col the column index of the element
	///@return the cofactor of the element as a matrix object
	Matrix cofactor(int row, int col);
	///@brief obtain the adjugate matrix of the matrix
	///@return the adjugate matrix as a matrix object
	Matrix adjugate();

private:
	double** data; // store data in this pointer
	int row; // number of row
	int col; // number of column
	int size; // number of element
};

#endif // MATRIX_H

//cell.h
#ifndef CELL_H
#define CELL_H

/** 
 * @file This file contains the declarations for the cell class
 */

#include <vector>
#include <string>
#include <iostream>
#include "vector.h"
#include "material.h"

/** 
 * @brief Class for storing properties of a cell
 * @author Wenxiang Luo
 * @version 1.0
 * @date 06/12/2019
 */

class Cell
{
public:
	///Default Constructor
	Cell();

	///Default Destructor
	~Cell() = default;

	///Assignment operator overload
	Cell& operator=(const Cell& c);

	///@brief gets the volume of the cell
	double getVolume() const;
	///@brief gets the weight of the cell
	double getWeight() const;
	///@brief gets the type of the cell
	std::string getType() const; 
	const std::vector<double>& getGravityCenter() const; // get the gravity center of the cell

	// overload stream insertion operator
	friend std::ostream& operator<<(std::ostream& out, const Cell& c);

protected:
	std::vector<Vector> data; // store the vertex of the cell
	std::string cellType; // a string store cell type
	std::vector<double> gravityCenter; // store gravity center of the cell | Could you not store this point as a vector object? ~ Ewan
	double volume; // the volume of the cell
	double weight; // the weight of the cell
	double density; // the density of the ell

	virtual void setVolume(); // determine the volume
	void setWeight(); // determine the weight
	void setGravityCenter(); // determine the gravity center
};

#endif //CELL_H

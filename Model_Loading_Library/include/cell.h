#ifndef CELL_H
#define CELL_H

#include <vector>
#include <string>
#include <iostream>
#include "vector.h"
#include "material.h"

class Cell
{
public:
	// default constructors
	Cell();

	// default destructor
	~Cell() = default;

	// overload assignment operator
	Cell& operator=(const Cell& c);

	double getVolume() const; // get the volume of the cell
	double getWeight() const; // get the weight of the cell
	std::string getType() const; //get the type of the cell
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

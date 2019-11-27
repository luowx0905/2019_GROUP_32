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

	// constructor for the tetrahedron
	Cell(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Material& m);

	// constructor for the pyramid
	Cell(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Vector& v4, Material& m);

	// constructor for the hexahedron
	Cell(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Vector& v4, Vector& v5, Vector& v6, Vector& v7, Material& m);
	
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

private:
	std::vector<Vector> data; // store the vertex of the cell
	std::string cellType; // a string store cell type
	std::vector<double> gravityCenter; // store gravity center of the cell
	double volume; // the volume of the cell
	double weight; // the weight of the cell
	double density; // the density of the ell

	void setVolume(); // determine the volume
	void setWeight(); // determine the weight
	void setGravityCenter(); // determine the gravity center
};

#endif CELL_H

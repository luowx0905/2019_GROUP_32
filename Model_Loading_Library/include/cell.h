#ifndef CELL_H
#define CELL_H

#include <vector>
#include <string>
#include "vector.h"
#include "material.h"

class Cell
{
public:
	// constructors
	Cell();
	Cell(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Material& m);
	Cell(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Vector& v4, Material& m);
	Cell(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Vector& v4, Vector& v5, Vector& v6, Vector& v7, Material& m);
	// destructor
	~Cell() = default;
	// overload assignment operator
	Cell& operator=(const Cell& c);

	double getVolume() const; // get the volume of the cell
	double getWeight() const; // get the weight of the cell
	std::string getType() const; //get the type of the cell
	const std::vector<double>& getGravityCenter() const; // get the gravity center of the cell

private:
	std::vector<Vector> data; // store the vertex of the cell
	std::string cellType;
	std::vector<double> gravityCenter;
	double volume;
	double weight;
	double density;

	void setVolume(); // determine the volume
	void setWeight(); // determine the weight
	void setGravityCenter(); // determine the gravity center
};

#endif CELL_H

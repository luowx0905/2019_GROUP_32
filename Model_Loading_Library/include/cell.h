#ifndef CELL_H
#define CELL_H

#include <vector>
#include <string>
#include "vector.h"
#include "material.h"

class Cell
{
public:
	Cell(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Material& m);
	Cell(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Vector& v4, Material& m);
	Cell(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Vector& v4, Vector& v5, Vector& v6, Vector& v7, Material& m);

	Cell& operator=(const Cell& c);

	double getVolume() const;
	double getWeight() const;
	std::string getType() const;
	const std::vector<double>& getGravityCenter() const;

private:
	std::vector<Vector> data;
	std::string cellType;
	std::vector<double> gravityCenter;
	double volume;
	double weight;
	double density;

	void setVolume();
	void setWeight();
	void setGravityCenter();
};

#endif CELL_H

#include <vector>
#include <string>
#include <iostream>
#include "cell.h"
#include "vector.h"
#include "material.h"
using namespace std;

// define default constructor
Cell::Cell()
{
	cellType = "Invalid";
	density = 0;
	volume = 0;
	weight = 0;
}

// overloading assignment operator
Cell& Cell::operator=(const Cell& c)
{
	// avoid self assignment
	if (this != &c)
	{
		data = c.data;
		cellType = c.cellType;
		gravityCenter = c.gravityCenter;
		volume = c.volume;
		weight = c.weight;
		density = c.density;
	}

	return *this;
}

// determine the volume
void Cell::setVolume()
{
	// set volume to a default value
	volume = 0;
}

// determine the weight
void Cell::setWeight()
{
	// weight is the product of density and volume
	weight = density * volume;
}

// determine the gravity center
void Cell::setGravityCenter()
{
	vector<Vector>::iterator itor;
	double x, y, z;
	double sumX = 0, sumY = 0, sumZ = 0;

	for (itor = data.begin(); itor != data.end(); itor++)
	{
		sumX += itor->get_i();
		sumY += itor->get_j();
		sumZ += itor->get_k();
	}

	x = sumX / data.size();
	y = sumY / data.size();
	z = sumZ / data.size();

	gravityCenter.push_back(x);
	gravityCenter.push_back(y); //Could you not store this point as a vector object? ~ Ewan
	gravityCenter.push_back(z);
}

// return the weight of the cell
double Cell::getWeight() const
{
	return weight;
}

// return the volume of the cell
double Cell::getVolume() const
{
	return volume;
}

// return the cell type of the cell
string Cell::getType() const
{
	return cellType;
}

// return the gravity center of the cell
const vector<double>& Cell::getGravityCenter() const
{
	return gravityCenter;
}

// overloading stream insertion operator
ostream& operator<<(ostream& out, const Cell& c)
{
	out << "Type: " <<c.cellType << endl;
	out << " Volume: " << c.volume << endl;
	out << " Weight: " << c.weight << endl;
	out << " Density: " << c.density << endl;
	if (c.cellType != "Invalid")
	{
		out << " Centre of Gravity: (" << c.gravityCenter[0] << ", " << c.gravityCenter[1]
			<< ", " << c.gravityCenter[2] << ")\n";

		vector<Vector>::const_iterator citor;

		cout << " The vector:" << endl;
		for (citor = c.data.begin(); citor != c.data.end(); citor++)
		{
			cout << " " << citor->get_i() << "\t" << citor->get_j() 
				<< "\t" << citor->get_k() << "\t" << endl;
		}
	}

	return out;
}

vector<Vector> Cell::getVertex() const
{
	return data;
}

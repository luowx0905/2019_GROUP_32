#include <vector>
#include <string>
#include <iostream>
#include "cell.h"
#include "vector.h"

using namespace std;

// define default constructor
Cell::Cell()
{
	cellType = "Invalid";
	density = 0;
	volume = 0;
	weight = 0;
}

// define the constructor for the Tetrahedron
Cell::Cell(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Material& m)
{
	cellType = "Tetrahedron";
	this->density = m.getdensity();
	
	data.push_back(v0);
	data.push_back(v1);
	data.push_back(v2);
	data.push_back(v3);

	setVolume();
	setWeight();
	setGravityCenter();
}

// define the constructor for the Pyramid
Cell::Cell(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Vector& v4, Material& m)
{
	cellType = "Pyramid";
	this->density = m.getdensity();

	data.push_back(v0);
	data.push_back(v1);
	data.push_back(v2);
	data.push_back(v3);
	data.push_back(v4);

	setVolume();
	setWeight();
	setGravityCenter();
}

// define the constructor for the Hexahedron
Cell::Cell(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Vector& v4, Vector& v5, Vector& v6, Vector& v7, Material& m)
{
	cellType = "Hexahedron";
	this->density = m.getdensity();

	data.push_back(v0);
	data.push_back(v1);
	data.push_back(v2);
	data.push_back(v3);
	data.push_back(v4);
	data.push_back(v5);
	data.push_back(v6);
	data.push_back(v7);

	setVolume();
	setWeight();
	setGravityCenter();
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
	vector<Vector>::iterator itor = data.begin();

	// the volume of a tetrahedron is |(v1*v2)，v3|/6
	// these three vectors should have the same starting point
	if (cellType == "Tetrahedron") 
	{
		Vector v1 = *itor - *(itor + 1); 
		Vector v2 = *itor - *(itor + 2);
		Vector v3 = *itor - *(itor + 3);

		Vector temp = v1.get_cross_p(v2);
		double det = temp.get_dot_p(v3);

		volume = abs(det) / 6;
	}

	// a pyramid could be divided into two tetrahedrons, therefore 
	// volume is |(v1*v2)，v3|/6 + |(v1*v3)，v4|/6
	// these four vectors should have the same starting point
	// and the starting point is not one of the points on the base
	else if (cellType == "Pyramid") 
	{
		Vector v1 = *(itor + 4) - *itor;
		Vector v2 = *(itor + 4) - *(itor + 1);
		Vector v3 = *(itor + 4) - *(itor + 2);
		Vector v4 = *(itor + 4) - *(itor + 3);

		Vector temp1 = v1.get_cross_p(v2);
		double det1 = abs(temp1.get_dot_p(v3));
		Vector temp2 = v1.get_cross_p(v3);
		double det2 = abs(temp2.get_dot_p(v4));

		volume = (det1 + det2) / 6;
	}

	// the volume of hexahedron could be determined by
	// |(v1*v2)，v3|/6 + |(v1*v4)，v5|/6 + |(v1*v6)，v7|/6
	// the formula could be found in Efficient computation of volume of hexahedral cells
	// available at https://www.osti.gov/biblio/632793/
	else
	{
		Vector v1 = *(itor + 6) - *itor;
		Vector v2 = *(itor + 1) - *itor;
		Vector v3 = *(itor + 2) - *(itor + 5);
		Vector v4 = *(itor + 4) - *itor;
		Vector v5 = *(itor + 5) - *(itor + 7);
		Vector v6 = *(itor + 3) - *itor;
		Vector v7 = *(itor + 7) - *(itor + 2);

		Vector temp1 = v1.get_cross_p(v2);
		double det1 = abs(temp1.get_dot_p(v3));
		Vector temp2 = v1.get_cross_p(v4);
		double det2 = abs(temp2.get_dot_p(v5));
		Vector temp3 = v1.get_cross_p(v6);
		double det3 = abs(temp3.get_dot_p(v7));

		volume = (det1 + det2 + det3) / 6;
	}
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
	gravityCenter.push_back(y);
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
	out << c.cellType << endl;
	out << "Gravity center (" << c.gravityCenter[0] << ", " << c.gravityCenter[1]
		<< ", " << c.gravityCenter[2] << ")\n";
	out << "Volume: " << c.volume << endl;
	out << "Weight: " << c.weight << endl;
	out << "Density: " << c.density << endl;

	return out;
}

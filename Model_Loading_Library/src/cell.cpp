#include <vector>
#include <string>
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

Cell& Cell::operator=(const Cell& c)
{
	// avoid self assignment
	if (this != &c)
	{
		cellType = c.cellType;
		data = c.data;
		gravityCenter = c.gravityCenter;
		volume = c.volume;
		weight = c.weight;
	}

	return *this;
}

void Cell::setVolume()
{
	vector<Vector>::iterator itor = data.begin();
	if (cellType == "Tetrahedron") 
	{
		Vector v1 = *itor - *(itor + 1); 
		Vector v2 = *itor - *(itor + 2);
		Vector v3 = *itor - *(itor + 3);

		Vector temp = v1.get_cross_p(v2);
		double det = temp.get_dot_p(v3);

		volume = abs(det) / 6;
	}
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

void Cell::setWeight()
{
	weight = density * volume;
}

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

double Cell::getWeight() const
{
	return weight;
}

double Cell::getVolume() const
{
	return volume;
}

string Cell::getType() const
{
	return cellType;
}

const vector<double>& Cell::getGravityCenter() const
{
	return gravityCenter;
}

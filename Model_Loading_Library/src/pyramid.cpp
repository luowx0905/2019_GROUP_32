#include <string>
#include <vector>
#include "pyramid.h"
#include "vector.h"
#include "material.h"

using namespace std;

Pyramid::Pyramid() : Cell()
{
	cellType = "Pyramid";
}

Pyramid::Pyramid(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Vector& v4, Material& m) : Cell()
{
	cellType = "Pyramid";
	this->density = m.getDensity();
	color = m.getColour();

	data.push_back(v0);
	data.push_back(v1);
	data.push_back(v2);
	data.push_back(v3);
	data.push_back(v4);

	setVolume();
	setWeight();
	setGravityCenter();
}

Pyramid& Pyramid::operator=(const Pyramid& p)
{
	// avoid self assignment
	if (this != &p)
	{
		data = p.data;
		cellType = p.cellType;
		color = p.color;
		gravityCenter = p.gravityCenter;
		volume = p.volume;
		weight = p.weight;
		density = p.density;
	}

	return *this;
}

void Pyramid::setVolume()
{
	// a pyramid could be divided into two tetrahedrons, therefore 
	// volume is |(v1*v2)¡¤v3|/6 + |(v1*v3)v4|/6
	// these four vectors should have the same starting point
	// and the starting point is not one of the points on the base
	vector<Vector>::iterator itor = data.begin();

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

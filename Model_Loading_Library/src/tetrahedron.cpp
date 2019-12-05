#include <string>
#include <vector>
#include "vector.h"
#include "material.h"
#include "tetrahedron.h"

using namespace std;

Tetrahedron::Tetrahedron() : Cell()
{
	cellType = "Trtradron";
}

// define the constructor for the Tetrahedron
Tetrahedron::Tetrahedron(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Material& m) : Cell()
{
	cellType = "Tetrahedron";
	this->density = m.getDensity();

	data.push_back(v0);
	data.push_back(v1);
	data.push_back(v2);
	data.push_back(v3);

	setVolume();
	setWeight();
	setGravityCenter();
}

Tetrahedron& Tetrahedron::operator=(const Tetrahedron& t)
{
	// avoid self assignment
	if (this != &t)
	{
		data = t.data;
		cellType = t.cellType;
		gravityCenter = t.gravityCenter;
		volume = t.volume;
		weight = t.weight;
		density = t.density;
	}

	return *this;
}

void Tetrahedron::setVolume()
{
	// the volume of a tetrahedron is |(v1*v2)v3|/6
	// these three vectors should have the same starting point
	vector<Vector>::iterator itor = data.begin();

	Vector v1 = *itor - *(itor + 1);
	Vector v2 = *itor - *(itor + 2);
	Vector v3 = *itor - *(itor + 3);

	Vector temp = v1.get_cross_p(v2);
	double det = temp.get_dot_p(v3);

	volume = abs(det) / 6;
}

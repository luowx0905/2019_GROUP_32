#include <string>
#include <vector>
#include "hexahedron.h"
#include "vector.h"
#include "material.h"

using namespace std;

Hexahedron::Hexahedron() : Cell()
{
	cellType = "Hexahedron";
}

Hexahedron::Hexahedron(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Vector& v4, Vector& v5, Vector& v6, Vector& v7, Material& m) : Cell()
{
	cellType = "Hexahedron";
	this->density = m.getDensity();
	color = m.getColour();

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

Hexahedron& Hexahedron::operator=(const Hexahedron& h)
{
	// avoid self assignment
	if (this != &h)
	{
		data = h.data;
		cellType = h.cellType;
		color = h.color;
		gravityCenter = h.gravityCenter;
		volume = h.volume;
		weight = h.weight;
		density = h.density;
	}

	return *this;
}

void Hexahedron::setVolume()
{
	// the volume of hexahedron could be determined by
	// |(v1*v2)v3|/6 + |(v1*v4)v5|/6 + |(v1*v6)v7|/6
	// the formula could be found in Efficient computation of volume of hexahedral cells
	// available at https://www.osti.gov/biblio/632793/
	vector<Vector>::iterator itor = data.begin();

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

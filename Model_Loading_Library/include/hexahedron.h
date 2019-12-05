#ifndef HEXAHEDRON_H
#define HEXAHEDRON_H

#include "cell.h"
#include "vector.h"
#include "material.h"

class Hexahedron : public Cell
{
public:
	// constructors
	Hexahedron();
	Hexahedron(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Vector& v4, Vector& v5, Vector& v6, Vector& v7, Material& m);

	// default destructor
	~Hexahedron() = default;

	// overload assignment operator
	Hexahedron& operator=(const Hexahedron& h);

private:
	virtual void setVolume() override; // determine the volume
};


#endif // !HEXAHEDRON_H


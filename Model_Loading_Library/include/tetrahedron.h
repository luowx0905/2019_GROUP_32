#pragma once
#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include "cell.h"
#include "vector.h"
#include  "material.h"
#include <stdlib.h>

class Tetrahedron : public Cell
{
public:
	// constructors
	Tetrahedron();
	Tetrahedron(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Material& m);

	// destructors
	~Tetrahedron() = default;

	// overload assignment operator
	Tetrahedron& operator=(const Tetrahedron& c);

private:
	void setVolume() override; // determine the volume
};

#endif // !TETRAHEDRON_H

#ifndef PYRAMID_H
#define PYRAMID_H

#include "cell.h"
#include "vector.h"
#include "material.h"
#include <cmath>

class Pyramid : public Cell
{
public:
	// constructors
	Pyramid();
	Pyramid(Vector& v0, Vector& v1, Vector& v2, Vector& v3, Vector& v4, Material& m);

	// destructor
	~Pyramid() = default;

	// overload assignment operator
	Pyramid& operator=(const Pyramid& p);

private:
	virtual void setVolume() override; // determine the volume
};

#endif // !PYRAMID_H

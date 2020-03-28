#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "cell.h"
#include "vector.h"
#include "material.h"
using namespace std;

// define default constructor
Cell::Cell()
{
	cellType = "Invalid";
	color = "000000";
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
		color = c.color;
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

vector<int> Cell::getColorRGB() const
{
	string red = color.substr(0, 2);
	string green = color.substr(2, 2);
	string blue = color.substr(4, 2);

	vector<int> color;
	color.push_back(hexToDec(red));
	color.push_back(hexToDec(green));
	color.push_back(hexToDec(blue));

	return color;
}

int Cell::hexToDec(string color) const
{
	transform(color.begin(), color.end(), color.begin(), ::tolower);
	int decimal = 0;

	size_t power = 0;
	for (int i = 1; i >= 0; i--, power++)
	{
		switch (color[i])
		{
		case '0':
		{
			break;
		}

		case '1':
		{
			decimal += pow(16, power);
			break;
		}

		case '2':
		{
			decimal += 2 * pow(16, power);
			break;
		}

		case '3':
		{
			decimal += 3 * pow(16, power);
			break;
		}

		case '4':
		{
			decimal += 4 * pow(16, power);
			break;
		}

		case '5':
		{
			decimal += 5 * pow(16, power);
			break;
		}

		case '6':
		{
			decimal += 6 * pow(16, power);
			break;
		}

		case '7':
		{
			decimal += 7 * pow(16, power);
			break;
		}

		case '8':
		{
			decimal += 8 * pow(16, power);
			break;
		}

		case '9':
		{
			decimal += 9 * pow(16, power);
			break;
		}

		case 'a':
		{
			decimal += 10 * pow(16, power);
			break;
		}

		case 'b':
		{
			decimal += 11 * pow(16, power);
			break;
		}

		case 'c':
		{
			decimal += 12 * pow(16, power);
			break;
		}

		case 'd':
		{
			decimal += 13 * pow(16, power);
			break;
		}

		case 'e':
		{
			decimal += 14 * pow(16, power);
			break;
		}

		case 'f':
		{
			decimal += 15 * pow(16, power);
			break;
		}

		default:
		{
			throw runtime_error("The color is invalid");
		}
		}
	}

	return decimal;
}

size_t Cell::getVectorNumber(vector<Vector>& vertex, int index) const
{
	size_t i;
	for (i = 0; i < vertex.size(); i++)
	{
		if (vertex[i] == data[index])
		{
			break;
		}
	}

	return i;
}

#include <iostream>
#include "Vector.h"

using namespace std;

//constructors
//-------------------------------------------------------------------------------------------------
Vector::Vector()
{
    i=0; //fill variables with 0
    j=0;
    k=0;
    mag=0;
}

/*Vector::Vector(float _mag,float _direction_i,float _direction_j,float _direction_k)
{
    mag=_mag; //fill variables with given values.
    direction_i=_direction_i;
    direction_j=_direction_j;
    direction_k=_direction_k;

    //calculate i,j,k using the magnitude and direction (completes the vector class).
    calc_Vector(mag,direction_i,direction_j,direction_k);
}*/

Vector::Vector(float _i,float _j,float _k)
{
    i=_i;
    j=_j;
    k=_k;

    //calc_Vector(i, j, k);
    calc_mag(_i,_j,_k);
}
//end of constructors
//-------------------------------------------------------------------------------------------------


void Vector::calc_mag(float _i,float _j,float _k) //calculates the magnitude of the vector to store in the class
{
    mag=sqrt((_i*_i)+(_j*_j)+(_k*_k));
}


Vector::~Vector(){}

Vector::Vector(const Vector& _Vector) //copy
{
    i=_Vector.i;
    j=_Vector.j;
    k=_Vector.k;
    mag=_Vector.mag;
}

//operators
//-------------------------------------------------------------------------------------------------
Vector Vector::operator=(const Vector& _Vector) //= (copies a Vector)
{
    i=_Vector.i;
    j=_Vector.j;
    k=_Vector.k;
    mag=_Vector.mag;

    return(*this);
}

Vector Vector::operator+(const Vector& _Vector) //+ (adds two vectors)
{
	float new_i = i + _Vector.i;
	float new_j = j + _Vector.j;
	float new_k = k + _Vector.k;
	Vector temp(new_i, new_j, new_k);


    temp.calc_mag(i,j,k);
    //temp.calc_Vector(i,j,k);

    return temp;
}

Vector Vector::operator+=(const Vector& _Vector) //+= (adds two vectors)
{
	float new_i = i + _Vector.i;
	float new_j = j + _Vector.j;
	float new_k = k + _Vector.k;
	Vector temp(new_i, new_j, new_k);


   temp.calc_mag(i,j,k);

	//temp.calc_Vector(i, j, k);

	return temp;
}

Vector Vector::operator-=(const Vector& _Vector) //- (subtracts two vectors)
{
	float new_i = i - _Vector.i;
	float new_j = j - _Vector.j;
	float new_k = k - _Vector.k;
	Vector temp(new_i, new_j, new_k);

    temp.calc_mag(i,j,k);
	//temp.calc_Vector(i, j, k);

	return temp;
}

Vector Vector::operator-(const Vector& _Vector) //-= (subtracts two vectors)
{
	float new_i = i - _Vector.i;
	float new_j = j - _Vector.j;
	float new_k = k - _Vector.k;
	Vector temp(new_i, new_j, new_k);


    temp.calc_mag(i,j,k);
	//temp.calc_Vector(i, j, k);


	return temp;
}


/*Vector Vector::operator*(const float& ScalingFactor) //* (scales the vector using scalar product)
{
    i*=ScalingFactor;
    j*=ScalingFactor;
    k*=ScalingFactor;
    mag*=ScalingFactor;*/


Vector operator*(const float ScalingFactor, const Vector& v) //* (scales the vector using scalar product)
{
	float new_i = v.i * ScalingFactor;
	float new_j = v.j * ScalingFactor;
	float new_k = v.k * ScalingFactor;
	Vector temp(new_i, new_j, new_k);

	//temp.calc_Vector(i, j, k);

	return temp;
}
//end of operators
//-------------------------------------------------------------------------------------------------


//set functions
//-------------------------------------------------------------------------------------------------
void Vector::set_i(const float& value) //set functions, changes variable to value, then recalculates class. Nothing returned.
{
    i=value;

    calc_mag(i,j,k);
}

void Vector::set_j(const float& value)
{
    j=value;

    calc_mag(i,j,k);
}

void Vector::set_k(const float& value)
{
    k=value;

    calc_mag(i,j,k);
}
//end of set functions
//-------------------------------------------------------------------------------------------------


//get Functions
//-------------------------------------------------------------------------------------------------
float Vector::get_i() const //gets the value of variables
{
    return(this->i);
}

float Vector::get_j() const
{
    return(this->j);
}

float Vector::get_k() const
{
    return(this->k);
}

float Vector::get_mag() const
{
    return(mag);
}

float Vector::get_direction_i() const
{
    return(direction_i);
}

float Vector::get_direction_j()const
{
    return(direction_j);
}

float Vector::get_direction_k() const 
{
    return(direction_k);
}
//end of get functions.


//-------------------------------------------------------------------------------------------------

float Vector::get_dot_p(const Vector& a)
{
	float temp = i * a.i + j * a.j + k * a.k;

	return temp;
}
//-------------------------------------------------------------------------------------------------

Vector Vector::get_cross_p(const Vector& _Vector1)
{
	float new_i = j * _Vector1.k - k * _Vector1.j;
	float new_j = -(i * _Vector1.k - k * _Vector1.i);
	float new_k = i * _Vector1.j - j * _Vector1.i;
	Vector temp(new_i, new_j, new_k);

	return temp;
}

ostream& operator<<(ostream& out, const Vector& v)
{
	out << "(" << v.i << ", " << v.j << ", " << v.k << ")";

	return out;
}

#include <iostream>
#include "vector.h"

using namespace std;

//constructors
//-------------------------------------------------------------------------------------------------
Vector::Vector() //New Vector filled with 0s
{
    i=0;
    j=0;
    k=0;
    mag=0;
}


Vector::Vector(float _i,float _j,float _k) //New Vector, the magnitude is calculated for you.
{
    i=_i;
    j=_j;
    k=_k;

    calc_mag(_i,_j,_k);
}
//end of constructors
//-------------------------------------------------------------------------------------------------


void Vector::calc_mag(float _i,float _j,float _k) //calculates the magnitude of the vector to store in the class
{
    mag=sqrt((_i*_i)+(_j*_j)+(_k*_k));
}


Vector::~Vector() {}

Vector::Vector(const Vector& _Vector) //copy
{
    i=_Vector.i;
    j=_Vector.j;
    k=_Vector.k;
    mag=_Vector.mag;
}

//operators
//-------------------------------------------------------------------------------------------------
const Vector& Vector::operator=(const Vector& _Vector) //= (copies a Vector)
{
    if(this==&_Vector)
        return (*this);
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

    return temp;
}

const Vector& Vector::operator+=(const Vector& _Vector) //+= (adds two vectors)
{
    this->i += _Vector.i;
    this->j += _Vector.j;
    this->k += _Vector.k;
    this->calc_mag(i,j,k);
    return (*this);
}

const Vector& Vector::operator-=(const Vector& _Vector) //- (subtracts two vectors)
{
    this->i -= _Vector.i;
    this->j -= _Vector.j;
    this->k -= _Vector.k;
    this->calc_mag(i,j,k);
    return (*this);
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
    mag*=ScalingFactor;
}*/


Vector operator*(const float ScalingFactor, const Vector& v) //* (scales the vector using scalar product)
{
    float new_i = v.i * ScalingFactor;
    float new_j = v.j * ScalingFactor;
    float new_k = v.k * ScalingFactor;
    Vector temp(new_i, new_j, new_k);

    return temp;
}
//end of operators
//-------------------------------------------------------------------------------------------------



//set functions
//set functions, changes variable to value, then recalculates the magnitude with new value.
//-------------------------------------------------------------------------------------------------
void Vector::set_i(const float& value)
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
//end of get functions.
//-------------------------------------------------------------------------------------------------



//calculates the dot product of a Vector (stored in a new Vector)
float Vector::get_dot_p(const Vector& a)
{
    float temp = i * a.i + j * a.j + k * a.k;

    return temp;
}


//calculates the cross product of a Vector (stored in a new Vector
Vector Vector::get_cross_p(const Vector& _Vector1)
{
    float new_i = j * _Vector1.k - k * _Vector1.j;
    float new_j = -(i * _Vector1.k - k * _Vector1.i);
    float new_k = i * _Vector1.j - j * _Vector1.i;
    Vector temp(new_i, new_j, new_k);

    return temp;
}


//output vector
ostream& operator<<(ostream& out, const Vector& v)
{
    out << "(" << v.i << ", " << v.j << ", " << v.k << ")";

    return out;
}

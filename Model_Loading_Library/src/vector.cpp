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
    direction_i=0;
    direction_j=0;
    direction_k=0;
}

Vector::Vector(float _mag,float _direction_i,float _direction_j,float _direction_k)
{
    mag=_mag; //fill variables with given values.
    direction_i=_direction_i;
    direction_j=_direction_j;
    direction_k=_direction_k;

    //calculate i,j,k using the magnitude and direction (completes the vector class).
    calc_Vector(mag,direction_i,direction_j,direction_k);
}

Vector::Vector(float _i,float _j,float _k)
{
    i=_i;
    j=_j;
    k=_k;

    calc_Vector(i, j, k);
}
//end of constructors
//-------------------------------------------------------------------------------------------------
Vector::~Vector(){}
Vector::Vector(const Vector& _Vector) //copy
{
    i=_Vector.i;
    j=_Vector.j;
    k=_Vector.k;
    mag=_Vector.mag;
    direction_i=_Vector.direction_i;
    direction_j=_Vector.direction_j;
    direction_k=_Vector.direction_k;
}

//operators
//-------------------------------------------------------------------------------------------------
Vector Vector::operator=(const Vector& _Vector) //= (copies a Vector)
{
    i=_Vector.i;
    j=_Vector.j;
    k=_Vector.k;
    mag=_Vector.mag;
    direction_i=_Vector.direction_i;
    direction_j=_Vector.direction_j;
    direction_k=_Vector.direction_k;

    return(*this);
}


Vector Vector::operator+(const Vector& _Vector) //+ (adds two vectors)
{
    i+=_Vector.i;
    j+=_Vector.j;
    k+=_Vector.k;

    calc_Vector(i,j,k);

    return(*this);
}


Vector Vector::operator+=(const Vector& _Vector) //+= (adds two vectors)
{
    i+=_Vector.i;
    j+=_Vector.j;
    k+=_Vector.k;

    calc_Vector(i,j,k);

    return(*this);
}


Vector Vector::operator-=(const Vector& _Vector) //- (subtracts two vectors)
{
    i-=_Vector.i;
    j-=_Vector.j;
    k-=_Vector.k;

    calc_Vector(i,j,k);

    return(*this);
}


Vector Vector::operator-(const Vector& _Vector) //-= (subtracts two vectors)
{
    i-=_Vector.i;
    j-=_Vector.j;
    k-=_Vector.k;

    calc_Vector(i,j,k);

    return(*this);
}


Vector Vector::operator*(const float ScalingFactor) //* (scales the vector using scalar product)
{
    i*=ScalingFactor;
    j*=ScalingFactor;
    k*=ScalingFactor;

    calc_Vector(i,j,k);

    return(*this);
}

//end of operators
//-------------------------------------------------------------------------------------------------


//set functions
//-------------------------------------------------------------------------------------------------
void Vector::set_i(float value) //set functions, changes variable to value, then recalculates class. Nothing returned.
{
    i=value;

    calc_Vector(i,j,k);
}
void Vector::set_j(float value)
{
    j=value;

    calc_Vector(i,j,k);

}


void Vector::set_k(float value)
{
    k=value;

    calc_Vector(i,j,k);

    return;
}


void Vector::set_mag(float value)
{
    mag=value;

    calc_Vector(mag, direction_i, direction_j, direction_k);

    return;
}


void Vector::set_direction_i(float value)
{
    direction_i=value;

    calc_Vector(mag, direction_i, direction_j, direction_k);
    return;
}


void Vector::set_direction_j(float value)
{
    direction_j=value;

    calc_Vector(mag, direction_i, direction_j, direction_k);

    return;
}


void Vector::set_direction_k(float value)
{
    direction_k=value;

    calc_Vector(mag, direction_i, direction_j, direction_k);

    return;
}

//end of set functions
//-------------------------------------------------------------------------------------------------


//get Functions
//-------------------------------------------------------------------------------------------------
float Vector::get_i()  //gets the value of variables
{
    return(this->i);
}

float Vector::get_j()
{
    return(this->j);
}

float Vector::get_k()
{
    return(this->k);
}

float Vector::get_mag()
{
    return(mag);
}

float Vector::get_direction_i()
{
    return(direction_i);
}

float Vector::get_direction_j()
{
    return(direction_j);
}

float Vector::get_direction_k()
{
    return(direction_k);
}

//end of get functions.
//-------------------------------------------------------------------------------------------------

//completes the vector class by calculating missing variables.
//-------------------------------------------------------------------------------------------------
void Vector::calc_Vector(float mag, float direction_i,float direction_j,float direction_k)
{
    i=cos(direction_i);
    return;
}


void Vector::calc_Vector(float i,float j,float k)
{
    direction_i=acos(i);
    direction_j=acos(j);
    direction_k=acos(k);

    mag= sqrt((i*i)+(j*j)+(k*k));

    return;
}
//-------------------------------------------------------------------------------------------------


//calculate dot product.
//-------------------------------------------------------------------------------------------------
float Vector::get_dot_p(const Vector& a, const Vector& b)
{
    return(0);
}
//-------------------------------------------------------------------------------------------------

Vector Vector::get_cross_p(const Vector& _Vector1, const Vector& _Vector2)
{
    return(Vector()); //temporarily made so can compile
}
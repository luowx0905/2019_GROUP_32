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
    k=_k;//antony pres at ours at 8

    //calc_Vector(i, j, k);
    calc_mag(_i,_j,_k);
}
//end of constructors
//-------------------------------------------------------------------------------------------------

void Vector::calc_mag(float _i,float _j,float _k) //calculates the magnitude of the vector to store in the class
{
    mag=sqrt((_i*_i)+(_j*_j)+(_k*_k));
}


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
    i+=_Vector.i;
    j+=_Vector.j;
    k+=_Vector.k;

    calc_mag(i,j,k);

    return(*this);
}

Vector Vector::operator+=(const Vector& _Vector) //+= (adds two vectors)
{
    i+=_Vector.i;
    j+=_Vector.j;
    k+=_Vector.k;

    calc_mag(i,j,k);

    return(*this);
}

Vector Vector::operator-=(const Vector& _Vector) //- (subtracts two vectors)
{
    i-=_Vector.i;
    j-=_Vector.j;
    k-=_Vector.k;

    calc_mag(i,j,k);

    return(*this);
}

Vector Vector::operator-(const Vector& _Vector) //-= (subtracts two vectors)
{
    i-=_Vector.i;
    j-=_Vector.j;
    k-=_Vector.k;

    calc_mag(i,j,k);

    return(*this);
}

Vector Vector::operator*(const float& ScalingFactor) //* (scales the vector using scalar product)
{
    i*=ScalingFactor;
    j*=ScalingFactor;
    k*=ScalingFactor;
    mag*=ScalingFactor;

    return(*this);
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
float Vector::get_i()  //gets the value of variables
{
    return(i);
}

float Vector::get_j()
{
    return(j);
}

float Vector::get_k()
{
    return(k);
}

float Vector::get_mag()
{
    return(mag);
}
//end of get functions.
//-------------------------------------------------------------------------------------------------


//calculate dot product.
//-------------------------------------------------------------------------------------------------
static float get_dot_p(Vector& _Vector1,Vector& _Vector2) //not functioning
{
    float dot_p;
    dot_p=acos(((_Vector1.get_i()*_Vector2.get_i())+(_Vector1.get_j()*_Vector2.get_j())+(_Vector1.get_k()*_Vector2.get_k()))/(_Vector1.get_mag()*_Vector2.get_mag()));
    return(dot_p);
}
//-------------------------------------------------------------------------------------------------


ostream& operator<<(ostream& out,const Vector& _Vector)
{
    out<<"\ni = "<<_Vector.i<<"\nj = "<<_Vector.j<<"\nk = "<<_Vector.k<<"\nMagnitude = "<<_Vector.mag;
    return(out);
}

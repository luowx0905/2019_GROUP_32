#ifndef Vector_H
#define Vector_H

#include <math.h>
#include <iostream>

using namespace std;

    class Vector
    {
    public:
        Vector(); //constructor
        Vector(float i, float j, float k);


        ~Vector(); //destruct

        Vector(const Vector& _Vector); //copy

        const Vector& operator=(const Vector& _Vector); //= (copies a Vector) //operators
        Vector operator+(const Vector& _Vector); //+ (adds two vectors)
        const Vector& operator+=(const Vector& _Vector); //+= (adds two vectors)
        const Vector& operator-=(const Vector& _Vector); //- (subtracts two vectors)
        Vector operator-(const Vector& _Vector); //-= (subtracts two vectors)

        //Vector operator*(const float& ScalingFactor); //* (scales the vector using scalar product)
        friend Vector operator*(const float ScalingFactor, const Vector& v); //* (scales the vector using scalar product)

        void set_i(const float& value); //set functions, changes to value, then recalculates class. Nothing returned.
        void set_j(const float& value);
        void set_k(const float& value);


        float get_i() const;  //gets the value of variables
        float get_j() const;  
        float get_k() const; 
        float get_mag() const; 
        //float get_direction_i() const;  
        //float get_direction_j() const; 
        //float get_direction_k() const;

        /*float calc_mag(const Vector& a) //calculate magnitude of a vector from 0,0,0 or a vector between two points.
        float calc_mag(const Vector& start1, const Vector& end1);*/

        void calc_mag(float _i,float _j,float _k); //calculates the magnitude of the vector to store in the class


        //static double get_dot_p(Vector& _Vector1,Vector& _Vector2); //not functioning //~Ewan changed to double for debugging with cell class

        float get_dot_p(const Vector& a);

        Vector get_cross_p(const Vector& _Vector1);


        //static Vector get_cross_p(const Vector& _Vector1, const Vector& _Vector2);

        //output stream operator for testing

        friend ostream& operator<<(ostream& out, const Vector& v);

    private:
        float i;
        float j;
        float k;

        float mag;

    };

#endif // Vector_H

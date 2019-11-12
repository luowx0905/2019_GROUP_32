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


        ~Vector(); //destruct //not needed

        Vector(const Vector& _Vector); //copy

        Vector operator=(const Vector& _Vector); //= (copies a Vector) //operators
        Vector operator+(const Vector& _Vector); //+ (adds two vectors)
        Vector operator+=(const Vector& _Vector); //+= (adds two vectors)
        Vector operator-=(const Vector& _Vector); //- (subtracts two vectors)
        Vector operator-(const Vector& _Vector); //-= (subtracts two vectors)
        Vector operator*(const float& ScalingFactor); //* (scales the vector using scalar product)

        void set_i(const float& value); //set functions, changes to value, then recalculates class. Nothing returned.
        void set_j(const float& value);
        void set_k(const float& value);

        float get_i(); //gets the value of variables
        float get_j();
        float get_k();
        float get_mag();

        void calc_mag(float _i,float _j,float _k); //calculates the magnitude of the vector to store in the class


        static double get_dot_p(Vector& _Vector1,Vector& _Vector2); //not functioning //~Ewan changed to double for debugging with cell class


        static Vector get_cross_p(const Vector& _Vector1, const Vector& _Vector2);

        //output stream operator for testing
        friend ostream& operator<<(ostream& out,const Vector& _Vector);

    private:
        float i;
        float j;
        float k;

        float mag;

    };

#endif // Vector_H

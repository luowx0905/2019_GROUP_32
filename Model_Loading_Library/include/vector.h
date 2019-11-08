#ifndef Vector_H
#define Vector_H

#include <math.h>

using namespace std;

    class Vector
    {
    public:
        Vector(); //constructor
        Vector(float _mag, float _direction_i, float _direction_j, float _direction_k);
        Vector(float i, float j, float k);

        ~Vector(); //destruct //not needed

        Vector(const Vector& _Vector); //copy

        Vector operator=(const Vector& _Vector); //= (copies a Vector) //operators
        Vector operator+(const Vector& _Vector); //+ (adds two vectors)
        Vector operator+=(const Vector& _Vector); //+= (adds two vectors)
        Vector operator-=(const Vector& _Vector); //- (subtracts two vectors)
        Vector operator-(const Vector& _Vector); //-= (subtracts two vectors)
        Vector operator*(const float ScalingFactor); //* (scales the vector using scalar product)

        void set_i(float value); //set functions, changes to value, then recalculates class. Nothing returned.
        void set_j(float value);
        void set_k(float value);
        void set_mag(float value);
        void set_direction_i(float value);
        void set_direction_j(float value);
        void set_direction_k(float value);

        float get_i(); //gets the value of variables
        float get_j();
        float get_k();
        float get_mag();
        float get_direction_i();
        float get_direction_j();
        float get_direction_k();

        /*float calc_mag(const Vector& a) //calculate magnitude of a vector from 0,0,0 or a vector between two points.
        float calc_mag(const Vector& start1, const Vector& end1);*/

       /* float calc_direction_1(const Vector& a); //calculates each angle
        float calc_direction_j(const Vector& a);
        float calc_direction_k(const Vector& a);
        float calc_direction(const Vector& start1, const Vector& end1);*/

        //void calc_Vector(Vector& a);
        void calc_Vector(float _mag, float _direction_i,float _direction_j,float _direction_k); //completes the vector class by calculating missing variables.
        void calc_Vector(float _i,float _j,float _k);

        static float get_dot_p(const Vector& a, const Vector& b);

        static Vector get_cross_p(const Vector& _Vector1, const Vector& _Vector2);


        //output stream operator for testing
        //friend ostream& operator<<(ostream& out, );

    private:
        float i;
        float j;
        float k;

        float mag;

        float direction_i;
        float direction_j;
        float direction_k;

    };

#endif // Vector_H

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include <string>
using namespace std;//for std::

class Material {
private:
  //Variables
  double density;
  string colour;
  string name;
  double id;
public:
  //Default Constructure
  Material();
  /*Overload Constructure
  d = density
  c = colour
  n = name
  i = id
  */
  Material (double d, string c, string n, double i);
  //Destuctor
  ~Material();
  /*Setup Function
  d = density
  c = colour 
  n = name
  i = id*/
  void setMaterial( double d, string c, string n, double i);
  double getdensity();//return density
  string getcolour();//return colour
  string getname();//return name
  double getid();//return id
  };

 #endif // End of material.h

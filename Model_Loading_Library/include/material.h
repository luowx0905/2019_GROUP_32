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
  int id;
public:
  //Default Constructure
  Material();
  /*Overload Constructure
  d = density
  c = colour
  n = name
  i = id
  */
  Material (double d, string c, string n, int i);
  //Destuctor
  ~Material();
  /*Setup Function
  d = density
  c = colour 
  n = name
  i = id*/
  void setMaterial( double d, string c, string n, double i);
  double getDensity();//return density
  string getColour();//return colour
  string getName();//return name
  double getID();//return id
  };

 #endif // End of material.h

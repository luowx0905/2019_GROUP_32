#include <iostream>
#include "material.h"

//Create Material Deault Value
Material::Material()
{
  this->density = 0;
  this->colour = "000000";
  this->name = "untitled";
  this->id = 0;
}

//Create Material by Overload Constructure
Material::Material(double d, string c, string n, double i)
{
 this->density = d;
 this->colour = c;
 this->name = n;
 this->id = i;
}
//Destructor
Material::~Material()
{

}
//Create Material by Setup Function
//The line below seems like it will cause issues as you are using this eventhough the function is not inside an object. Is this function even required? ~Ewan
void Material::setMaterial(double d, string c, string n, double i)
{
  this->density = d;
  this->colour = c;
  this->name = n;
  this->id = i;
}
//Accestor Function/ Return Value
double Material::getdensity()
{
  return this->density;
}

string Material::getcolour()
{
  return this->colour;
}
string Material::getname()
{
  return this->name;
}
double Material::getid()
{
  return this->id;
}

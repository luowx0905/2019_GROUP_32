#include <iostream>
#include<material.h>

//Create Material Deault Value
Material::Material()
{
  this->density = 0;
  this->colour = 0;
  this->name = unknow;
  this->id = unknow;
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
void Material(double d, string c, string n, double i)
{
  this->density = d;
  this->colour = c;
  this->name = n:
  this->id = i;
}
//Accestor Function/ Return Value
double Matrial::getdensity()
{
  return this->desity;
}

string Material::getcolour()
{
  return this->colour;
}
string Material::getstring()
{
  return this->name;
}
double Material::getid()
{
  return this->id;
}

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
Material::Material(double d, string c, string n, int i)
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
//The line below seems like it will cause issues as you are using 'this' eventhough the function is not inside an object. ~Ewan
/*void Material(double d, string c, string n, double i)
{
  this->density = d;
  this->colour = c;
  this->name = n;
  this->id = i;
}*/
//Accessor Function/ Return Value
ostream& operator<<(ostream& out,const Material& m)
{
    out<<"\n  Name = "<<m.name<<"\n  Colour = "<<m.colour<<"\n  Density = "<<m.density;
    return(out);
}

double Material::getDensity()
{
  return this->density;
}

string Material::getColour()
{
  return this->colour;
}
string Material::getName()
{
  return this->name;
}
double Material::getID()
{
  return this->id;
}

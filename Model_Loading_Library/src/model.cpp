#include "model.h"
#include <fstream>
#include <sstream>
Model::Model(string filePath):sourceFilePath(filePath){}
Model::~Model(){}
void Model::loadModel()
{
    int vectorListLength = 0;
    int cellListLength = 0;
    int materialListLength = 0;

    this->fileStream.open(this->sourceFilePath.c_str());
    if (!this->fileStream) //checks to see if file was opened succesfully
    {
        cerr << "Unable to open model file";
        exit(1);
    }
    string line;
    while(!this->fileStream.eof()) //loops till end of file reached
    {
        getline(this->fileStream,line); //read each line into a string 
        if(line.length() != 0) //checks whether line is empty
        {
            if(line.at(0) != '#') //checks if line is a comment first for efficiency
            {
                if(line.at(0) == 'v') //check first character to see if line represents a vector
                {
                    vectorListLength ++; 
                    listOfVectors.resize(vectorListLength); //increases the size of the vector list by one to make space for new addition
                    readVector(line);
                }
                else if(line.at(0) == 'c')
                {
                    cellListLength++;
                    readCell(line);
                }
                else if(line.at(0) == 'm')
                {
                    materialListLength++;
                    readMaterial(line);
                }
            }
        }
    }
    this->fileStream.close();
}
void Model::readVector(string line)
{
    istringstream linestream(line); //turn line string into string stream
    int id;
    float xcoord;
    float ycoord;
    float zcoord;
    linestream.ignore(1); //ignore the object identifier
    linestream >> id;
    linestream >> xcoord;
    linestream >> ycoord;
    linestream >> zcoord;
    listOfVectors.at(id) = Vector(xcoord,ycoord,zcoord);
}
void Model::readCell(string line)
{
    return;
}
void Model::readMaterial(string line)
{
    return;
}
//update functions in header
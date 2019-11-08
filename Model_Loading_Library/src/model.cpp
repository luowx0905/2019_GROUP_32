#include "model.h"
#include <fstream>
#include <sstream>
Model::Model(string filePath):sourceFilePath(filePath){}
Model::~Model(){}
void Model::loadModel()
{
    populateVectorList();
}

void Model::populateVectorList()
{
    int vectorListLength = 0;
    ifstream fileStream;
    string line;
    fileStream.open(this->sourceFilePath.c_str());
    if (!fileStream)
    {
        cerr << "Unable to open model file";
        exit(1);
    }
    while(!fileStream.eof())
    {
        getline(fileStream,line);
        if(line.length() != 0)
        {
            if(line.at(0) == 'v')
            {
                vectorListLength++;
                istringstream linestream(line);
                listOfVectors.resize(vectorListLength);
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
        }
    }
}
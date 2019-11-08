#include "model.h"
#include <fstream>
#include <sstream>
Model::Model(String filePath):sourceFilePath(filePath){}
Model::~Model(){}
void Model::loadModel()
{
    populateVectorList();
}

void Model::populateVectorList()
{
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
                istringstream linestream(line);
                int id;
                float xcoord;
                float ycoord;
                float zcoord;
                linestream.ignore(1); //ignore the object identifier
                linestream >> id;
                linestream >> xcoord;
                linestream >> ycoord;
                linestream >> zcoord;
                listOfVectors[id] = Vector(param1,param2,param3);
            }
        }
    }
}
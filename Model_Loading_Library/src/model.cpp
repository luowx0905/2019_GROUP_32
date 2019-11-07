#include "model.h"
#include <fstream>
Model::Model(String filePath):sourceFilePath(filePath){}
int Model::getNumberOfVectors()
{
    ifstream fileStream;
    string line;
    int numberOfVectors = 0;
    fileStream.open(this->sourceFilePath);
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
                numberOfVectors ++;
            }
        }
    }
    fileStream.close();
    return numberOfVectors;
}
void Model::populateVectorList()
{
    this->listOfVectors = new Vector [getNumberOfVectors];
    ifstream fileStream;
    string line;
    fileStream.open(this->sourceFilePath);
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
               
            }
        }
    }
}
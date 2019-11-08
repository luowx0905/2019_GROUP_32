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

    this->fileStream.open(this->sourceFilePath.c_str()); //opens file
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
                    listOfCells.resize(cellListLength);
                    readCell(line);
                }
                else if(line.at(0) == 'm')
                {
                    materialListLength++;
                    listOfMaterials.resize(materialListLength);
                    readMaterial(line);
                }
                else
                {
                    cerr << "Error in reading line - Object Identifier not recognised";
                    exit(1);
                }
                
            }
        }
    }
    this->fileStream.close();
    return;
}
void Model::readVector(string line)
{
    istringstream linestream(line); //turn line string into string stream
    int vectorID;
    float xcoord; //TODO Mention to anthony about possibly changing vector parameters to doubles for more precision
    float ycoord;
    float zcoord;
    linestream.ignore(1); //ignore the object identifier
    linestream >> vectorID;
    linestream >> xcoord;
    linestream >> ycoord;
    linestream >> zcoord;
    listOfVectors.at(vectorID) = Vector(xcoord,ycoord,zcoord); 
    //Storing the vector at the ID of its index may cause issues in future if any are added or removed or simply if the IDs are not consecutive and starting from 0.
    //If this becomes an issue then a solution would be to make the ID a parameter of the vector object itself.
    return;
}
void Model::readCell(string line)
{
    istringstream linestream(line); //c 0 h 0 0 1 2 3 4 5 6 7
    int cellID;
    char shapeType;
    int materialID;
    int vectors[8];
    linestream.ignore(1);
    linestream >> cellID;
    linestream >> shapeType;
    linestream >> materialID;
    for(int i = 0; i < 8; i++)
        linestream >> vectors[i]; //reads the rest of the line into an array.
    if(shapeType == 'h')
    {
        listOfCells.at(cellID) = Cell(listOfVectors[vectors[0]], listOfVectors[vectors[1]], listOfVectors[vectors[2]], 
                                      listOfVectors[vectors[3]], listOfVectors[vectors[4]], listOfVectors[vectors[5]], 
                                      listOfVectors[vectors[6]], listOfVectors[vectors[7]], listOfMaterials[materialID]);
        return;
    }
    else if(shapeType == 'p')
    {
        listOfCells.at(cellID) = Cell(listOfVectors[vectors[0]], listOfVectors[vectors[1]], listOfVectors[vectors[2]],
                                      listOfVectors[vectors[3]], listOfVectors[vectors[4]], listOfMaterials[materialID]);
        return;
    }
    else if(shapeType == 't')
    {
        listOfCells.at(cellID) = Cell(listOfVectors[vectors[0]],listOfVectors[vectors[1]],listOfVectors[vectors[2]],
                                      listOfVectors[vectors[3]],listOfMaterials[materialID]);
        return;
    }
    else
    {
        cerr << "Error in reading cell - shapeType not found";
        exit(1);
    }
    //Storing the cell in the list at the ID of its index may cause issues in future if any are added or removed or simply if the IDs are not consecutive and starting from 0.
    //If this becomes an issue then a solution would be to make the ID a parameter of the cell object itself.
}   
void Model::readMaterial(string line)
{
    istringstream linestream(line); //m 0 8940 b87333 cu
    int materialID;
    double density;
    string colour;
    string name;
    linestream.ignore(1);
    linestream >> materialID;
    linestream >> density;
    linestream >> colour;
    linestream >> name;
    listOfMaterials.at(materialID) = Material(); //TODO finish using Material constructor
    return;
}
//update functions in header
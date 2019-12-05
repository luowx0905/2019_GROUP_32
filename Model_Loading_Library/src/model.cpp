#include "model.h"
#include <fstream>
#include <sstream>

Model::Model(string filePath):sourceFilePath(filePath){loadModel();}
Model::Model(){}
Model::~Model()
{
    //Declare vectors on the stack so that the vector destructors will be called to deallocate them
    vector<Vector> listOfVectors;
    vector<Cell> listOfCells;
    vector<Material> listOfMaterials;
    vector<vector<int>> uninitCellList; 
}
const Model& Model::operator=(const Model& m)
{
    if(this==&m) return (*this);
    listOfVectors = m.listOfVectors;
    listOfCells = m.listOfCells;
    listOfMaterials = m.listOfMaterials;
    return(*this);
}
Model::Model(const Model& m)
{
    listOfVectors = m.listOfVectors;
    listOfCells = m.listOfCells;
    listOfMaterials = m.listOfMaterials;
}
void Model::displayVertices() const
{
    cout << "-=-=-=-=-=Vertices=-=-=-=-=-"<<endl;
    for(int i = 0; i < this->listOfVectors.size();i++)
        cout <<"Vector "<< i << ": "<< this->listOfVectors[i] << endl;
    cout<<endl<<endl;
    return;
}
void Model::displayCells() const
{
    cout << "-=-=-=-=-=-=-=-=Cells=-=-=-=-=-=-=-=-"<<endl;
    for(int i = 0; i < this->listOfCells.size();i++)
        cout <<"Cell "<< i << ": "<< this->listOfCells[i] << endl;
    cout<<endl<<endl;
    return;
}
void Model::displayMaterials() const
{
    cout << "-=-=-=-=Materials=-=-=-=-"<<endl;
    for(int i = 0; i < this->listOfMaterials.size(); i++)
        cout <<"Material "<< i << ": "<<this->listOfMaterials[i] << endl;
    cout<<endl<<endl;
    return;
}
long Model::getNumberOfCells() const
{
    return this->listOfCells.size();
}
long Model::getNumberOfVertices() const
{
    return this->listOfVectors.size();
}
long Model::getNumberOfMaterials() const
{
    return this->listOfMaterials.size();
}
Vector Model::getModelCentre() const
{
    vector<double> cellCentre;
    double sumX = 0;
    double sumY = 0;
    double sumZ = 0;
    for(int i = 0; i < listOfCells.size(); i++)
    {
        cellCentre = listOfCells[i].getGravityCenter();
        sumX += cellCentre[0];
        sumY += cellCentre[1];
        sumZ += cellCentre[2];
    }
    Vector temp(sumX/listOfCells.size(),sumY/listOfCells.size(),sumZ/listOfCells.size());
    return(temp);
}
double Model::getModelWeight() const
{
    double modelWeight = 0;
    for(int i = 0; i < this->listOfCells.size(); i++)
        modelWeight += listOfCells[i].getWeight();
    return modelWeight;
}

void Model::loadModel()
{
    int vectorListLength = 0;
    int cellListLength = 0;
    int materialListLength = 0;
    uninitCellList.resize(10); //makes the 10 rows
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
                    for(int i = 0; i < 10; i++)//iterates through each of the 11 rows of the 2D list
                    {
                        uninitCellList[i].resize(cellListLength);
                    }
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
    generateCellList(cellListLength);
    this->fileStream.close();
    vector<vector<int>> uninitCellList; //vector no longer needed so de-allocate memory associated with it 
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
        uninitCellList[0][cellID] = 72; //ASCII for 'H'
        for(int i = 0; i < 8; i++)
            uninitCellList[i+1][cellID] = vectors[i];
        uninitCellList[9][cellID] = materialID;
        return;
    }
    else if(shapeType == 'p')
    {
        uninitCellList[0][cellID] = 80; //ASCII for 'P'
        for(int i = 0; i < 5; i++)
            uninitCellList[i+1][cellID] = vectors[i];
        uninitCellList[9][cellID] = materialID;
        return;
    }
    else if(shapeType == 't')
    {
        uninitCellList[0][cellID] = 84; //ASCII for 'T'
        for(int i = 0; i < 4; i++)
            uninitCellList[i+1][cellID] = vectors[i];
        uninitCellList[9][cellID] = materialID;
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
    listOfMaterials.at(materialID) = Material(density,colour,name,materialID);
    return;
}
void Model::generateCellList(int cellListLength)
{
    listOfCells.resize(cellListLength);
    for(int i = 0; i < cellListLength; i++)
    {
        if(uninitCellList[0][i] == 72)
        {
            listOfCells[i] = Hexahedron(listOfVectors[uninitCellList[1][i]], listOfVectors[uninitCellList[2][i]], listOfVectors[uninitCellList[3][i]],
                                  listOfVectors[uninitCellList[4][i]], listOfVectors[uninitCellList[5][i]], listOfVectors[uninitCellList[6][i]],
                                  listOfVectors[uninitCellList[7][i]], listOfVectors[uninitCellList[8][i]], listOfMaterials[uninitCellList[9][i]]);
        }
        else if (uninitCellList[0][i] == 80)
        {
            listOfCells[i] = Pyramid(listOfVectors[uninitCellList[1][i]], listOfVectors[uninitCellList[2][i]], listOfVectors[uninitCellList[3][i]],
                                  listOfVectors[uninitCellList[4][i]], listOfVectors[uninitCellList[5][i]], listOfMaterials[uninitCellList[9][i]]);
        }
        else if (uninitCellList[0][i] == 84)
        {
            listOfCells[i] = Tetrahedron(listOfVectors[uninitCellList[1][i]], listOfVectors[uninitCellList[2][i]], listOfVectors[uninitCellList[3][i]],
                                  listOfVectors[uninitCellList[4][i]], listOfMaterials[uninitCellList[9][i]]);
        }
    }

    return;
}
//TODO Replace cellList appending with insert/pushback to remove need to manually resize array at each line in file

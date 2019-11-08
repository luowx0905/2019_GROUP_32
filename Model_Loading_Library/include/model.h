#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED
#include <vector>
#include <iostream>
#include <fstream>
#include "vector.h"
using namespace std;
//For now, class only used to load a model, not create new.
class Model
{
    public:
    Model(string filePath); 
    ~Model();
    void displayVertices();
    void displayCells();
    Vector getModelCentre();
    void loadModel();
    vector<Vector> listOfVectors;

    private:
    //vector<Cell> listOfCells;
    //vector<Material> listOfMaterials;
    void populateVectorList();
    void populateCellList();
    void populateMateriallist();
    string sourceFilePath;
    ifstream fileStream;
};
#endif // MODEL_H_INCLUDED

//TODO ensure file only opens once - file opening code in loadModel function?
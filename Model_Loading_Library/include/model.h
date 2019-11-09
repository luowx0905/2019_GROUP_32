#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "vector.h"
#include "cell.h"
#include "material.h"
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
    vector<Vector> listOfVectors; //currently in public just for testing - must return to private

    private:
    vector<Cell> listOfCells;
    vector<Material> listOfMaterials;
    void readVector(string line);
    void readCell(string line);
    void readMaterial(string line);
    string sourceFilePath;
    ifstream fileStream;
};
#endif // MODEL_H_INCLUDED

#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <iostream>
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

    private:
    Vector* listOfVectors;
    Cell* listOfCells;
    Material* listOfMaterials;
    int getNumberOfVectors(); //scan the file to find how large to make vector list
    void populateVectorList();
    string sourceFilePath
};
#endif // MODEL_H_INCLUDED
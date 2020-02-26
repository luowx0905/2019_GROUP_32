#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "vector.h"
#include "cell.h"
#include "material.h"
#include "pyramid.h"
#include "hexahedron.h"
#include "tetrahedron.h"

using namespace std;

//For now, class only used to load a model, not create new.
class Model
{
    public:
    Model(string filePath); 
    Model();
    ~Model();
    Model(const Model&);
    const Model& operator=(const Model&);

    void displayVertices()const;
    void displayCells()const;
    void displayMaterials()const;

    Vector getModelCentre()const;//Returns models centre as a vector point. still TODO
    double getModelWeight()const;
    long getNumberOfVertices()const;
    long getNumberOfCells()const;
    long getNumberOfMaterials()const;

	vector<Pyramid> getPyramid() const;
	vector<Hexahedron> getHex() const;
	vector<Tetrahedron> getTetra() const;
    
    private:
    vector<Vector> listOfVectors;
    vector<Cell> listOfCells;
    vector<Material> listOfMaterials;
    vector<vector<int>> uninitCellList; 
	vector<Pyramid> pyramidList;
	vector<Hexahedron> hexList;
	vector<Tetrahedron> tetraList;
    /*uninitCellList
    Row Index: 0    1     2    3    4   5   6   7   8   9   
    Data:     type  v1   v2   v3   v4  v5  v6  v7  v8  material
    */
    //each column pertains to a new cellID
    void generateCellList(int cellListLength); //function populates a 2D vector with all the vectors each cell should contain. Will then be used to generate list containing actual Cell objects once the entire file has been read
    void readVector(string line);
    void readCell(string line);
    void readMaterial(string line);
    void setFilePath(string fp);
    void loadModel();
    string sourceFilePath;
    ifstream fileStream;
};
#endif // MODEL_H_INCLUDED

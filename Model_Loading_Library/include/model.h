// model.h
#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED
/** @file
 * This file contains the declarations for the model class
 */
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "vector.h"
#include "cell.h"
#include "material.h"
#include "hexahedron.h"
#include "tetrahedron.h"
#include "pyramid.h"

using namespace std;

//For now, class only used to load a model, not create new.
/** 
 * @brief Class for reading .mod file and providing details regarding its contents
 * 
 * @author Ewan Drever-Smith
 */
class Model
{
public:
    /**
    * @brief Construct model object from data loaded from a given file
    * @param filePath Location of .mod file to be loaded
    */
    Model(string filePath);
    /// Default constructor
    Model();
    /// @brief Deallocates memory associated with vector lists
    ~Model();
    /// Copy constructor
    Model(const Model&); 
    /// Operator= overload
    const Model& operator=(const Model&); 
    /// @brief Outputs the coordinates of each vertice in the model to the console
    /// @return Void
    void displayVertices()const;//outputs to the console each vertice and its coordinate vector (x,y,z)
    /// @brief Outputs the properties of each cell in the model to the console
    /// @return Void
    void displayCells()const;//outputs to the console each cell and its properties (type, volume, weight, density)
    /// @brief Outputs the properties of each material in the model to the console
    /// @return Void
    void displayMaterials()const;//outputs to the console each material in the model and its properties (Density, name colour)
    /// @brief Calculates the centre of the model
    /// @return Calculation result as a Vector point
    /// @TODO Implement this function
    Vector getModelCentre()const;
    /// @brief Calculates the total weight of all cells in the model
    /// @return Calculated weight as a double
    double getModelWeight()const;
    /// @brief Gets the number of vertices in the model
    /// @return Number of vertices as a long
    long getNumberOfVertices()const;
    /// @brief Gets the number of cells in the model
    /// @return Number of cells as a long
    long getNumberOfCells()const;
    /// @brief Gets the number of materials in the model
    /// @return Number of materials as a long
    long getNumberOfMaterials()const;
private:
    //Note that each object in the object lists is stored at the index of its ID - This was done for speed in locating the object needed however it does have consequences
    //in that every ID in the file must be consecutive or else the object will attempted to be added to a point outside the range of the std::vector
    //In future if this is no longer acceptable, then store ID as a parameter of the object itself. This would mean that each object could be stored at any point in the list, but would take longer to search for the object with a particular ID.
    vector<Vector> listOfVectors;
    vector<Cell> listOfCells;
    vector<Material> listOfMaterials;
    vector<vector<int>> uninitCellList; 
    /*uninitCellList
    Row Index: 0    1     2    3    4   5   6   7   8   9   
    Data:     type  v1   v2   v3   v4  v5  v6  v7  v8  material
    */
    //each column pertains to a new cellID
    void generateCellList(int cellListLength); //function populates a 2D vector with all the vectors each cell should contain. Will then be used to generate list containing actual Cell objects once the entire file has been read
    void readVector(string line);//reads the passed line string and constructs a vector object using details from the line. This object is then added to the vector list at the index of its ID
    void readCell(string line);//reads the the passed line string and adds the vector 'recipe' to the uninitCellList to be constructed at a later time.
    void readMaterial(string line);//reads the passed line string and constructs a Material object using details from the line. This object is then added to the material list at the index of its ID
    void setFilePath(string fp);//Unused - delete?
    void loadModel();//Loads file located at sourceFilePath into model object
    string sourceFilePath; // contains the location of the file to be read.
    ifstream fileStream;//TODO remove this from the class data and use locally inside loadModel()
};
#endif // MODEL_H_INCLUDED

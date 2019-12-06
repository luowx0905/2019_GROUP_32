#include "model.h"
#include "vector.h"
#include "cell.h"
#include "material.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int main(int argc, char *argv[])
{
    if(argc != 2 || atoi(argv[1]) > 3 || atoi(argv[1]) < 1)
    {
        cerr << "Incorrect arguments... Please provide one number between 1 and 3 to select model to read"<< endl;
        exit(1);
    }
    char filePath[30] = "";
    sprintf(filePath,"../test/ExampleModel%s.mod",argv[1]);
    string strfilePath(filePath);
    //test constructors
    Model myModel(strfilePath); 
    //test display functions
    cout<<myModel;
    myModel.displayVertices();
    myModel.displayCells();
    myModel.displayMaterials();
}
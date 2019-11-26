#include "model.h"
#include "vector.h"
#include "cell.h"
#include "material.h"
using namespace std;
int main()
{
    Model myModel("../test/ExampleModel1.mod");
    myModel.loadModel();
    myModel.displayVertices();

}
#include "model.h"
#include "vector.h"
#include "cell.h"
#include "material.h"
using namespace std;
int main()
{
    Model myModel("C:/Users/Ewan/Documents/.University/Computing Project/Group32/Model_Loading_Library/ExampleModel1.mod");
    myModel.loadModel();
    myModel.displayVertices();
}
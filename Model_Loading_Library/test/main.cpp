#include "model.h"
#include "vector.h"
using namespace std;
int main()
{
    Model myModel("C:/Users/Ewan/Documents/.University/Computing Project/Group32/Model_Loading_Library/ExampleModel1.mod");
    myModel.loadModel();
    for(int i = 0; i < myModel.listOfVectors.size();i++)
        cout <<"Vector "<< i << myModel.listOfVectors[i] << endl;
    while(1){}
}
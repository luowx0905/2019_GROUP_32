#include "model.h"
#include "vector.h"
using namespace std;
int main()
{
    Model myModel("C:/Users/Ewan/Documents/.University/Computing Project/Group32/Model_Loading_Library/ExampleModel1.mod");
    myModel.loadModel();
    cout << "hello" << endl;
    cout << myModel.listOfVectors[5].get_j() << endl;
    while(1){}
}
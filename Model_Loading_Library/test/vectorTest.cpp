#include <iostream>
#include "vector.h"
int main(int argc, char *argv[])
{
    //initialise some vectors to use for testing
    Vector testVector(0,4,3);
    Vector testVector2(8,6,4);
    Vector testVector3(6,9,7);

    //get magnitude test
    bool GET_MAG_STATUS = (testVector.get_mag() == 5) ? 0 : 1;

    //Set and Get test
    testVector.set_i(6);
    testVector.set_j(9);
    testVector.set_k(7);
    bool SET_AND_GET_STATUS = (testVector.get_i() == 6
                            && testVector.get_j() == 9
                            && testVector.get_k() == 7) ? 0 : 1;
    //Add test
    Vector temp = testVector2 + testVector3;
    bool ADD_STATUS = (temp.get_i() == 14
                    && temp.get_j() == 15
                    && temp.get_k() == 11) ? 0 : 1;

    return (GET_MAG_STATUS == 0 && SET_AND_GET_STATUS == 0 && ADD_STATUS == 0) ? 0 : 1; //1 represents error
}

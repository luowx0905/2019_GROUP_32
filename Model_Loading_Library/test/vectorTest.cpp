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
    //operator== test
    bool EQUALITY_OPERATOR_STATUS = (!(testVector2 == testVector3) && testVector3 == Vector(6,9,7) ) ? 0 : 1;
    
    //get_got_p() test
    bool DOT_PROD_STATUS = (testVector2.get_dot_p(testVector3) == 130) ? 0 : 1;

    //get_cross_p() test
    bool CROSS_PROD_STATUS = (testVector2.get_cross_p(testVector3) == Vector(6,-32,36)) ? 0 : 1;

    return (GET_MAG_STATUS  == 0 && SET_AND_GET_STATUS == 0 && 
            ADD_STATUS      == 0 && EQUALITY_OPERATOR_STATUS == 0 && 
            DOT_PROD_STATUS == 0 && CROSS_PROD_STATUS == 0) ? 0 : 1; //1 represents error
}

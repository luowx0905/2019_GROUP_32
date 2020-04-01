#include <iostream>
#include "vector.h"
#include <sstream>
int main(int argc, char *argv[])
{
    //initialise some vectors to use for testing
    Vector testVector(0,4,3);
    Vector testVector2(8,6,4);
    Vector testVector3(6,9,7);

    //get magnitude test
    bool GET_MAG_STATUS = (testVector.get_mag() == 5);

    //Set and Get test
    testVector.set_i(6);
    testVector.set_j(9);
    testVector.set_k(7);
    bool SET_AND_GET_STATUS = (testVector.get_i() == 6
                            && testVector.get_j() == 9
                            && testVector.get_k() == 7);
    //Add test
    Vector temp1 = testVector2 + testVector3;
    bool ADD_STATUS = (temp1.get_i() == 14
                    && temp1.get_j() == 15
                    && temp1.get_k() == 11);
    //operator== test
    bool EQUALITY_OP_STATUS = (!(testVector2 == testVector3) && testVector3 == Vector(6,9,7) );
    
    //get_got_p() test
    bool DOT_PROD_STATUS = (testVector2.get_dot_p(testVector3) == 130);

    //get_cross_p() test
    bool CROSS_PROD_STATUS = (testVector2.get_cross_p(testVector3) == Vector(6,-32,36));

    //operator<< test
    std::ostringstream temp2;
    temp2 << testVector2;
    bool OUTPUT_OP_STATUS = (temp2.str()=="(8, 6, 4)");

    return (GET_MAG_STATUS  && SET_AND_GET_STATUS && 
            ADD_STATUS      && EQUALITY_OP_STATUS && 
            DOT_PROD_STATUS && CROSS_PROD_STATUS  &&
            OUTPUT_OP_STATUS) ? 0 : 1; //1 represents error
}

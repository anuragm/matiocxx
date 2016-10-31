#include "matiocxx.hpp"
#include <iostream>

int main()
{
    double myDataDouble[] = {1.05,2.05,3.05};
    int myDataInt[] = {1,2,3};
    std::vector<int> intVec(myDataInt,myDataInt+3);

    matio::matvar<double> myVarDouble("myDataDouble",{1,3},myDataDouble);
    matio::matvar<int>    myVarInt("myDataInt",{1,3},myDataInt);
    matio::matvar<int>    var_stdvec("std_vec_int",intVec);
    matio::matvar<char>   var_string("myString","This is a test string");

    matio::matfile myFile("test.mat");

    myFile << myVarDouble << myVarInt << var_stdvec <<var_string;
    myFile.write();

    return 0;
}

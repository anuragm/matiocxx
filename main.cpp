#include "matiocxx.hpp"
#include <iostream>

int main()
{
    double myDataDouble[] = {1.05,2.05,3.05};
    int myDataInt[] = {1,2,3};

    matio::matvar<double> myVarDouble("myDataDouble",{1,3},myDataDouble);
    std::printf("Created first variable \n");

    matio::matvar<int> myVarInt("myDataInt",{1,3},myDataInt);
    std::printf("Created second variable \n");

    matio::matfile myFile("test.mat");

    myFile << myVarDouble;
    std::printf("Written first variable to matfile class\n");

    myFile << myVarInt;
    std::printf("Written second variable to matfile class \n");


    myFile.write();
    std::printf("Written file to disk. Exiting .... \n");

    return 0;
}

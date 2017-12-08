# A C++ library for manipulating MATLAB data files

MatioCXX is a C++ wrapper for reading and writing MATLAB data files
build up on [libmatio](https://sourceforge.net/projects/matio/). This
is a header only library. Just include `matiocxx.hpp` to your source
files. Requires a compiler supporting C++14 or above.

Following code snippet shows some useful functions. MatioCXX supports
reading and writing data in form of a POD, as `std::vector` and also
supports writing [Armadillo](http://arma.sourceforge.net/) matrices.

``` c++
#include "matiocxx.hpp"
#include <armadillo>
#include <iostream>

int main()
{
    double myDataDouble[] = {1.05,2.05,3.05};
    int myDataInt[] = {1,2,3};
    std::vector<int> intVec(myDataInt,myDataInt+3);
    arma::mat arma_mat(10,10,arma::fill::eye);

    matio::matvar<double> myVarDouble("myDataDouble",{1,3},myDataDouble);
    matio::matvar<int>    myVarInt("myDataInt",{1,3},myDataInt);
    matio::matvar<int>    var_stdvec("std_vec_int",intVec);
    matio::matvar<char>   var_string("myString","This is a test string");
    matio::matvar<double> var_arma("arma_eye",arma_mat);
    matio::matvar<double> var_arma_vec("arma_vec",arma::vec(10,arma::fill::ones));

    matio::matfile myFile("test.mat");

    myFile << myVarDouble << myVarInt << var_stdvec <<var_string << var_arma <<var_arma_vec;
    myFile.write();

    return 0;
}
```

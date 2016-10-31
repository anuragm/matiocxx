#ifndef MATIOCXX_H
#define MATIOCXX_H

//A wrapper around MATIO for C++.

extern "C"{
#include <matio.h>
}

#include <memory>
#include <string>
#include <vector>
#include <type_traits> //For template specialization.
#include <climits>
#include <limits>
#include <armadillo>

namespace matio{

    template <typename T>
    class matvar{  //General MATVAR

    private:
        typedef decltype(Mat_Close)*   mat_t_deleter ;
        typedef decltype(Mat_VarFree)* matvar_deleter;

        std::string              variable_name;
        std::vector<std::size_t> dimensions;
        const T*                 data;

        matio_classes            classtype;
        matio_types              datatype;
        int                      option = 0; //Extra options param fro C-MATIO

        template<typename T_=T,
                 typename std::enable_if_t
                 <std::is_integral<T_>::value || std::is_floating_point<T_>::value>* = nullptr
                 >
        void set_matio_types();

    public:
        matvar(const std::string&               _variable_name,
               const std::vector<std::size_t>&  _dimensions,
               const T* const                   _data,
               matio_classes                    _classtype,
               matio_types                      _datatype,
               int                              _option):
            variable_name(_variable_name), dimensions(_dimensions), data(_data),
            classtype(_classtype), datatype(_datatype), option(_option) {}; //Default constructor.

        //Constructor for Integer type. _T is only used to determine type.
        template<typename T_=T,
                 //Below compiles only if type is a integer.
                 typename std::enable_if_t<std::is_integral<T_>::value>* = nullptr>
        matvar(const std::string&              _variable_name,
               const std::vector<std::size_t>& _dimensions,
               const T* const                  _data);

        //Constructor for Floating type.
        template<typename T_=T,
                 //Below compiles only if type is a float.
                 typename std::enable_if_t<std::is_floating_point<T_>::value>* = nullptr>
        matvar(const std::string&               _variable_name,
               const std::vector<std::size_t>&  _dimensions,
               const T* const                   _data);

        //Special constructors.

        //Constructor for arma::mat
        matvar(const std::string&   _variable_name,
               const arma::Mat<T>&  _data);

        //Constructor for std::vector
        matvar(const std::string&   _variable_name,
               const std::vector<T>& _data);

        //Constructor for const char*. Complain otherwise.
        matvar(const std::string& _variable_name,
               const T*           _data);

        matvar_t* get_varp() const { //Returns the pointer to a matvar_t.
            return Mat_VarCreate
                (variable_name.c_str(),classtype,datatype,dimensions.size(),
                 const_cast<std::size_t*>(dimensions.data()),const_cast<T*>(data),option);
        }
    };  //end class matvar

    #include "matiocxx_bits/matiocxx_matvar.hpp"

    class matfile{
    private:
        typedef decltype(Mat_Close)*   mat_t_deleter ;
        typedef decltype(Mat_VarFree)* matvar_deleter;

        std::string fileName;
        std::vector<std::unique_ptr<matvar_t,matvar_deleter>> varArray;
    public:
        matfile();
        matfile(const std::string& _fileName):
            fileName(_fileName) {}; //Default constructor

        template<class T>
        matfile& operator << (matvar<T> mat_variable){     //Adds to variable array.
            matvar_t* temp_ptr = mat_variable.get_varp();
            varArray.push_back(std::unique_ptr<matvar_t,matvar_deleter>(temp_ptr,Mat_VarFree));
            return *this;
        }

        template<class T>
        void add_variable(matvar<T> mat_variable){
            *this << mat_variable;
        }

        void write(); //Write to disk.
    }; //end of matfile.

    #include "matiocxx_bits/matiocxx_matfile.hpp"
}

#endif /* MATIOCXX_H */

//Here, we implement the functions defined for class matio::matvar
#ifdef MATIOCXX_H

//Integral type constructor.
template<typename T>
template<typename T_,std::enable_if_t<std::is_integral<T_>::value>*>
matvar<T>::matvar (const std::string&               _variable_name,
                   const std::vector<std::size_t>&  _dimensions,
                   const T* const                   _data):
    variable_name(_variable_name), dimensions(_dimensions), data(_data){

    //Set class type and data type to appropriate values.
    switch( sizeof(T)*CHAR_BIT ){
    case 32 : // int on unix x86_64. int and long on windows.
        datatype = MAT_T_INT32;
        break;
    case 16 : //Short on linux and windows.
        datatype = MAT_T_INT16;
        break;
    case  8 : //int8_t
        datatype = MAT_T_INT8;
        break;
    default :
    case 64: //long and long long usually on unix.long long on windows.
        datatype = MAT_T_INT64;
    }

    //if unsigned, the data type for MAT_T_UINT* is +1 of MAT_T_INT*
    if (!std::numeric_limits<T>::is_signed)
        datatype = static_cast<matio_types>(static_cast<int>(datatype)+1) ;

    classtype = MAT_C_DOUBLE;
    option    = 0; //0 as this is not complex or something.
}

//Constructor for Floating type.
template<typename T>
template<typename T_,std::enable_if_t<std::is_floating_point<T_>::value>*>
matvar<T>::matvar (const std::string&               _variable_name,
                   const std::vector<std::size_t>&  _dimensions,
                   const T* const                   _data):
    variable_name(_variable_name), dimensions(_dimensions), data(_data){

    //Set class type and data type to appropriate values.
    switch( sizeof(T)*CHAR_BIT ){
    case 32 : // type for float.
        datatype = MAT_T_SINGLE;
        break;
    default :
    case 64: // double.
        datatype = MAT_T_DOUBLE;
    }

    classtype = MAT_C_DOUBLE;
    option    = 0;
}

#endif

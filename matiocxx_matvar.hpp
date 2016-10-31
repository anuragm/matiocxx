//Here, we implement the functions defined for class matio::matvar
#ifdef MATIOCXX_H

//Private member to determine class and data types.
template<typename T>
template<typename T_,
         typename std::enable_if_t
         <std::is_integral<T_>::value || std::is_floating_point<T_>::value>*
         >
void matvar<T>::set_matio_types(){

    if (std::is_integral<T_>::value){ //Set value for integer types.
        //Set class type and data type to appropriate values.
        switch( sizeof(T)*CHAR_BIT ){
        case 32 :
            datatype = MAT_T_INT32;
            break;
        case 16 :
            datatype = MAT_T_INT16;
            break;
        case  8 :
            datatype = MAT_T_INT8;
            break;
        default :
        case 64:
            datatype = MAT_T_INT64;
        }

        //if unsigned, the data type for MAT_T_UINT* is +1 of MAT_T_INT*
        if (!std::numeric_limits<T>::is_signed)
            datatype = static_cast<matio_types>(static_cast<int>(datatype)+1) ;
    }

    if(std::is_floating_point<T_>::value){ //Set the values for floating type.
        switch( sizeof(T)*CHAR_BIT ){
        case 32 :
            datatype = MAT_T_SINGLE;
            break;
        default :
        case 64:
            datatype = MAT_T_DOUBLE;
        }
    }

    classtype = MAT_C_DOUBLE;
    option    = 0;
}

//Integral type constructor.
template<typename T>
template<typename T_,std::enable_if_t<std::is_integral<T_>::value>*>
matvar<T>::matvar (const std::string&               _variable_name,
                   const std::vector<std::size_t>&  _dimensions,
                   const T* const                   _data):
    variable_name(_variable_name), dimensions(_dimensions), data(_data){
    set_matio_types();
}

//Constructor for Floating type.
template<typename T>
template<typename T_,std::enable_if_t<std::is_floating_point<T_>::value>*>
matvar<T>::matvar (const std::string&               _variable_name,
                   const std::vector<std::size_t>&  _dimensions,
                   const T* const                   _data):
    variable_name(_variable_name), dimensions(_dimensions), data(_data){

    set_matio_types();
}

//Constructor for arma::mat
template<typename T>
matvar<T>::matvar(const std::string&  _variable_name,
                  const arma::Mat<T>& _data):
    variable_name(_variable_name), data(_data.memptr()){

    dimensions = {_data.n_rows,_data.n_cols};
    option = 0;
    set_matio_types();
}

//Constructor for std::vector
template<typename T>
matvar<T>::matvar(const std::string&    _variable_name,
                  const std::vector<T>& _data):
    variable_name(_variable_name), data(_data.data()){

    dimensions = {_data.size(),1};
    option     = 0;
    set_matio_types();
}

//Constructor for const char*
template<typename T>
matvar<T>::matvar(const std::string& _variable_name,
                  const T*           _data):
    variable_name(_variable_name), data(_data){

    static_assert(std::is_same<char,T>::value,"This constructor can only be used for strings!");
    option      = 0;
    classtype   = MAT_C_CHAR;
    datatype    = MAT_T_UINT8;
    dimensions  = {1,std::char_traits<char>::length(data)};
}

#endif

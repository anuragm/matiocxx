#ifdef MATIOCXX_H
#include <armadillo>
#include <cstdio>
#include <matio.h>

void matfile::write(){                     //And write to disk
    mat_t* fp = Mat_CreateVer(fileName.c_str(),NULL,MAT_FT_MAT73);

    for(auto& varp : varArray){
        auto temp_ptr = varp.get();

        if( NULL != temp_ptr)
            Mat_VarWrite(fp,temp_ptr,MAT_COMPRESSION_ZLIB);
        else
            std::printf("Cannot write a null pointer!");
    }

    Mat_Close(fp);
}

template <typename T>
arma::Mat<T> matfile::read_matrix(std::string variable_name) const{ //Read from disk file
  arma::Mat<T> var_data;

  auto fp = std::unique_ptr<mat_t,mat_t_deleter>
    (Mat_Open(fileName.c_str(),MAT_ACC_RDONLY),Mat_Close);

  if(NULL == fp){
    std::printf("Cannot open file %s",fileName.c_str());
    return var_data; //Return an empty matrix.
  }

  auto matvar = std::unique_ptr<matvar_t,matvar_deleter>
    (Mat_VarRead(fp.get(),variable_name.c_str()),Mat_VarFree);

  if (NULL == matvar){
    std::printf("No such variable named %s",variable_name.c_str());
    return var_data;
  }

  if (matvar->rank != 2){
    std::printf("Variable %s is neither a vector nor a matrix.",variable_name.c_str());
    return var_data;
  }

  //Otherwise, just read the data.
  arma::uword dim0 = matvar->dims[0];
  arma::uword dim1 = matvar->dims[1];

  var_data.set_size(dim0,dim1);
  T* raw_data = reinterpret_cast<T*>(matvar->data);

  std::copy(raw_data,raw_data+dim0*dim1,var_data.begin());

  return var_data;
}

template <typename T>
T matfile::read_value(std::string variable_name) const{ //Read a single value from disk.
  T var_data = 0;

  auto fp = std::unique_ptr<mat_t,mat_t_deleter>
    (Mat_Open(fileName.c_str(),MAT_ACC_RDONLY),Mat_Close);

  if(NULL == fp){
    std::printf("Cannot open file %s",fileName.c_str());
    return var_data; //Return an empty matrix.
  }

  auto matvar = std::unique_ptr<matvar_t,matvar_deleter>
    (Mat_VarRead(fp.get(),variable_name.c_str()),Mat_VarFree);

  if (NULL == matvar){
    std::printf("No such variable named %s",variable_name.c_str());
    return var_data;
  }

  if (matvar->rank !=2 && matvar->dims[0] != 1 && matvar-> dims[1] != 1){
    std::printf("Variable %s is not a simple value!",variable_name.c_str());
    return var_data;
  }

  T* raw_data = reinterpret_cast<T*>(matvar->data);
  var_data = *raw_data;
  return var_data;
}
#endif

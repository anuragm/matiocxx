#ifdef MATIOCXX_H

void matfile::write(){                     //And write to disk
    mat_t* fp = Mat_CreateVer(fileName.c_str(),NULL,MAT_FT_MAT73);

    for(auto& varp : varArray){
        auto temp_ptr = varp.get();

        if( NULL != temp_ptr)
            Mat_VarWrite(fp,temp_ptr,MAT_COMPRESSION_NONE);
        else
            std::printf("Cannot write a null pointer!");
    }

    Mat_Close(fp);
}

#endif

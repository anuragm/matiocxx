#ifdef MATIOCXX_H

void matfile::write(){                     //And write to disk
    mat_t* fp = Mat_CreateVer(fileName.c_str(),NULL,MAT_FT_MAT73);
    std::printf("Opened file to write! \n");

    for(auto& varp : varArray){
        auto temp_ptr = varp.get();
        std::printf("Got the variable pointer! \n");

        if( NULL != temp_ptr)
            Mat_VarWrite(fp,temp_ptr,MAT_COMPRESSION_NONE);
        else
            std::printf("Cannot write a null pointer!");

        std::printf("Write a variable to disk!! \n");
    }

    Mat_Close(fp);
}

#endif

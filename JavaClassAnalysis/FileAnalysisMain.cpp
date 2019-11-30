//
// Created by 星野斉 on 2019/11/11.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "FileAnalysisMain.h"




int classFileCheck(char * filename) {

    // File length read
    long file_size = fileSizeCalc(filename);

    // Data Area make
    char * data_array = new char[file_size];

    // File read
    std::ifstream ifs(filename, std::ios::in | std::ios::binary);
    ifs.read(data_array, file_size);

    ifs.close();

    size_t readed = ifs.gcount();

    std::cout << "read_length=" << readed << std::endl;

    //Java class file signature check
    bool error_flg  = false;
    if (!(data_array[0] == -54)) {
        //std::cout << "ca" << std::endl;
        error_flg = true;
    }
    if ((!error_flg) && !(data_array[1] == -2)) {
        //std::cout << "fe" << std::endl;
        error_flg = true;
    }
    if ((!error_flg) && !(data_array[2] == -70)) {
        //std::cout << "ba" << std::endl;
        error_flg = true;
    }
    if ((!error_flg) &&  !(data_array[3] == -66)) {
        //std::cout << "be" << std::endl;
        error_flg = true;
    }

    if (error_flg) {
        //has errors
        std::cout << "File is not java class file. signature error." << std::endl;
        return 1;
    }

    delete[] data_array;



    return 0;
}

long fileSizeCalc(char * filename) {

    // for ifstream

    std::ifstream ifs(filename, std::ios::binary);
    ifs.seekg(0, std::ios::end);
    long eofpos = ifs.tellg();
    ifs.clear();
    ifs.seekg(0, std::ios::beg);
    long begpos = ifs.tellg();
    long file_size = eofpos - begpos;
    std::cout << "FileSize: " << file_size << std::endl;
    ifs.close();

    return file_size;

}
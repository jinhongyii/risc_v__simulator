//
// Created by jinho on 7/1/2019.
//

#ifndef RISC_V__SIMULATOR_PREPROCESSOR_H
#define RISC_V__SIMULATOR_PREPROCESSOR_H

#include <fstream>
#include "Executor.h"
class Preprocessor {
    std::fstream f;
public:
    Preprocessor(const std::string& file_name):f(file_name){
    
    }
    void preprocess();
    
};


#endif //RISC_V__SIMULATOR_PREPROCESSOR_H

//
// Created by jinho on 7/1/2019.
//

#ifndef RISC_V__SIMULATOR_PREPROCESSOR_H
#define RISC_V__SIMULATOR_PREPROCESSOR_H

#include <fstream>
#include "Executor.h"
class Preprocessor {
    std::istream& io;
public:
    Preprocessor(std::istream& ios):io(ios){
    
    }
    void preprocess();
    
};


#endif //RISC_V__SIMULATOR_PREPROCESSOR_H

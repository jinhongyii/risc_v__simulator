//
// Created by jinho on 7/1/2019.
//

#ifndef RISC_V__SIMULATOR_INSTRUCTIONFETCHER_H
#define RISC_V__SIMULATOR_INSTRUCTIONFETCHER_H


#include "Executor.h"

class InstructionFetcher {
public:
    int buf=0;
    int pc_;
    bool ready=false;
    
    InstructionFetcher()= default;
    void IF (bool busy , bool &jump , int branchAddress=-1);
};


#endif //RISC_V__SIMULATOR_INSTRUCTIONFETCHER_H

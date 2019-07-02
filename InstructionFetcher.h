//
// Created by jinho on 7/1/2019.
//

#ifndef RISC_V__SIMULATOR_INSTRUCTIONFETCHER_H
#define RISC_V__SIMULATOR_INSTRUCTIONFETCHER_H


#include "Executor.h"

class InstructionFetcher {
public:
    int buf;
    InstructionFetcher()= default;
    void IF();
};


#endif //RISC_V__SIMULATOR_INSTRUCTIONFETCHER_H

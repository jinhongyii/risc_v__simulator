//
// Created by jinho on 7/1/2019.
//

#ifndef RISC_V__SIMULATOR_MEMORYACCESS_H
#define RISC_V__SIMULATOR_MEMORYACCESS_H

#include "Executor.h"
#include "Types.h"

class MemoryAccess {

public:
    Instruction buf;
    void mem( Instruction inst);
};


#endif //RISC_V__SIMULATOR_MEMORYACCESS_H

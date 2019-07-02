//
// Created by jinho on 7/1/2019.
//

#ifndef RISC_V__SIMULATOR_MEMORYACCESS_H
#define RISC_V__SIMULATOR_MEMORYACCESS_H

#include "Executor.h"
#include "Types.h"

class MemoryAccess {

public:
    bool busy=false;
    bool ready=true;
    Instruction buf{};
    MemoryAccess(){
        buf.valid=false;
    }
    void mem (Instruction &inst , bool busy , bool ready);
};


#endif //RISC_V__SIMULATOR_MEMORYACCESS_H

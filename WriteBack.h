//
// Created by jinho on 7/1/2019.
//

#ifndef RISC_V__SIMULATOR_WRITEBACK_H
#define RISC_V__SIMULATOR_WRITEBACK_H


#include "Types.h"
#include <cstring>
#include "Executor.h"
class WriteBack {
public:
    bool busy=false;
    void wb (const Instruction &inst , bool ready);
};


#endif //RISC_V__SIMULATOR_WRITEBACK_H

//
// Created by jinho on 7/1/2019.
//
#pragma once
#ifndef RISC_V__SIMULATOR_EXECUTOR_H
#define RISC_V__SIMULATOR_EXECUTOR_H

#include <cstring>
#include <list>
#include "Types.h"

extern int pc;
extern int reg[32];
extern char memory[4194304];

extern int access[32];
class Executor {

public:
    Instruction buf{};
    bool busy=false;
    bool ready=true;
    Executor(){
        buf.valid=false;
    }
    void execute (Instruction &inst , bool busy , int &instruction , bool ready);
};


#endif //RISC_V__SIMULATOR_EXECUTOR_H

//
// Created by jinho on 7/1/2019.
//
#pragma once
#ifndef RISC_V__SIMULATOR_EXECUTOR_H
#define RISC_V__SIMULATOR_EXECUTOR_H

#include <cstring>
#include "Types.h"

extern int pc;
extern int reg[32];
extern char memory[4194304];
class Executor {

public:
    Instruction buf;
    void execute( Instruction inst);
};


#endif //RISC_V__SIMULATOR_EXECUTOR_H

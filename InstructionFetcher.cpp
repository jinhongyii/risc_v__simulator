//
// Created by jinho on 7/1/2019.
//

#include "InstructionFetcher.h"

void InstructionFetcher::IF (bool busy) {
    if (busy) {
        
        return;
    }
    memcpy(&buf , memory + pc , 4);
    this->pc_=pc;
    pc+=4;
    ready=true;
}

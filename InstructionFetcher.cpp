//
// Created by jinho on 7/1/2019.
//

#include "InstructionFetcher.h"

void InstructionFetcher::IF (bool busy , bool &jump , int branchAddress , int jumpAddress) {
    if (busy) {
        return;
    }
    if(jump) {
        TwoLevelAdaptive pred = branchPredictorMap[(branchAddress>>2)%16];
        if ( pred.jumpOrNot()) {
            memcpy(&buf , memory + jumpAddress , 4);
            this->pc_ = jumpAddress;
            ready = true;
            jump = false;
            return;
        } else {
            jump=false;
        }
    }
    memcpy(&buf , memory + pc , 4);
    this->pc_=pc;
    pc+=4;
    ready=true;
}

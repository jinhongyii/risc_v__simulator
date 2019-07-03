//
// Created by jinho on 7/1/2019.
//

#include "InstructionFetcher.h"

void InstructionFetcher::IF (bool busy , bool &jump , int branchAddress) {
    if (busy) {
        return;
    }
    if(jump) {
        TwoLevelAdaptive pred = branchPredictorMap.at(branchAddress);
        if ( pred.jumpOrNot()) {
            memcpy(&buf , memory + pred.getjumpAddress() , 4);
            this->pc_ = pred.getjumpAddress();
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

//
// Created by jinho on 7/2/2019.
//

#ifndef RISCV_TWOLEVELADAPTIVE_H
#define RISCV_TWOLEVELADAPTIVE_H

#include "SaturatingCounter.h"

class TwoLevelAdaptive :public predictor{
    char prev1=false,prev2=false;
    int jumpAddress;
    SaturatingCounter counter[4];
public:
    explicit TwoLevelAdaptive(int jumpAddress):jumpAddress(jumpAddress){}
    inline int getjumpAddress(){ return jumpAddress;}
    void update(bool jump)override ;
    bool jumpOrNot() override ;
};


#endif //RISCV_TWOLEVELADAPTIVE_H

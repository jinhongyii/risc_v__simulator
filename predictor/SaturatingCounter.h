//
// Created by jinho on 7/2/2019.
//

#ifndef RISCV_SATURATINGCOUNTER_H
#define RISCV_SATURATINGCOUNTER_H

#include "Predictor.h"
//0: not taken   1: taken
class SaturatingCounter: public predictor {
    int counter=0;
public:
    void update(bool jump) override;
    bool jumpOrNot() override ;
};


#endif //RISCV_SATURATINGCOUNTER_H

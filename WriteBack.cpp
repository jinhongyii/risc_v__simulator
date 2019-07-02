//
// Created by jinho on 7/1/2019.
//

#include "WriteBack.h"


void WriteBack::wb (const Instruction &inst , bool ready) {
    if (!ready) {
        return;
    }
    if (inst.valid == false) {
        return;
    }
    if (inst.type == R_type_ || inst.type == I_type_ || inst.type == U_type_ || inst.type == J_type_) {
        reg[inst.rd]=inst.result;
        regToChange.pop_front();
    }
    reg[0]=0;
    
}

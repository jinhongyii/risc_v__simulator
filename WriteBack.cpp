//
// Created by jinho on 7/1/2019.
//

#include "WriteBack.h"


void WriteBack::wb (const Instruction &inst) {
    if (inst.type == R_type_ || inst.type == I_type_ || inst.type == U_type_ || inst.type == J_type_) {
        reg[inst.rd]=inst.result;
    }
    reg[0]=0;
}

//
// Created by jinho on 7/1/2019.
//

#include "MemoryAccess.h"


void MemoryAccess::mem (const Instruction &inst) {
    if (inst.type == I_type_) {
        switch (inst.i_type) {
            case LW:
                memcpy(&reg[inst.rd] , inst.immediate + memory , 4);
                break;
            case LH: {
                short tmp;
                memcpy(&tmp , inst.immediate + memory , 2);
                reg[inst.rd] = tmp;
            }
                break;
            case LHU: {
                unsigned short tmp;
                memcpy(&tmp , inst.immediate + memory , 2);
                reg[inst.rd] = tmp;
            }
                break;
            case LB: {
                char tmp;
                memcpy(&tmp , inst.immediate + memory , 1);
                reg[inst.rd] = tmp;
            }
                break;
            case LBU: {
                unsigned char tmp;
                memcpy(&tmp , inst.immediate + memory , 1);
                reg[inst.rd] = tmp;
            }
                break;
            
        }
    }
    buf = inst;
}

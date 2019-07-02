//
// Created by jinho on 7/1/2019.
//

#include "MemoryAccess.h"


void MemoryAccess::mem ( Instruction inst) {
    if (inst.type == I_type_) {
        switch (inst.i_type) {
            case LW:
                memcpy(&inst.result , inst.immediate + memory , 4);
                break;
            case LH: {
                short tmp;
                memcpy(&tmp , inst.immediate + memory , 2);
                inst.result = tmp;
            }
                break;
            case LHU: {
                unsigned short tmp;
                memcpy(&tmp , inst.immediate + memory , 2);
                inst.result= tmp;
            }
                break;
            case LB: {
                char tmp;
                memcpy(&tmp , inst.immediate + memory , 1);
                inst.result = tmp;
            }
                break;
            case LBU: {
                unsigned char tmp;
                memcpy(&tmp , inst.immediate + memory , 1);
                inst.result = tmp;
            }
                break;
            
        }
    } else if (inst.type == S_type_) {
        switch (inst.s_type) {
            case SW:
                memcpy(inst.immediate+memory,&inst.reg2_val,4);
                break;
            case SH: {
                short tmp = inst.reg2_val;
                memcpy(inst.immediate + memory , &tmp , 2);
            }
                break;
            case SB: {
                char tmp = inst.reg2_val;
                memcpy(inst.immediate + memory , &tmp , 1);
            }
                break;
        }
    }
    buf = inst;
    reg[0]=0;
}

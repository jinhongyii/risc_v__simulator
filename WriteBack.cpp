//
// Created by jinho on 7/1/2019.
//

#include "WriteBack.h"


void WriteBack::wb (const Instruction &inst) {
    if (inst.type == S_type_) {
        switch (inst.s_type) {
            case SW:
                memcpy(inst.immediate+memory,&reg[inst.rs2],4);
                break;
            case SH: {
                short tmp = reg[inst.rs2];
                memcpy(inst.immediate + memory , &tmp , 2);
            }
                break;
            case SB: {
                char tmp = reg[inst.rs2];
                memcpy(inst.immediate + memory , &tmp , 1);
            }
                break;
        }
    }
}

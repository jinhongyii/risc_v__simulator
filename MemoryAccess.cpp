//
// Created by jinho on 7/1/2019.
//

#include "MemoryAccess.h"


void MemoryAccess::mem (Instruction &inst , bool busy , bool ready) {
    static int time=0;
    if(time!=0) goto process;
    if (!ready ) {
        this->ready=false;
        return;
    }
    if (busy) {
        this->busy=true;
        return;
    }
    if (inst.valid == false) {
        this->busy=false;
        buf=inst;
        return;
    }
    process:
    
    
    if (inst.type == I_type_) {
        switch (inst.i_type) {
            case LW:
                memcpy(&inst.result , inst.immediate + memory , 4);
                time++;
                time%=3;
                break;
            case LH: {
                short tmp;
                memcpy(&tmp , inst.immediate + memory , 2);
                inst.result = tmp;
                time++;
                time%=3;
            }
                break;
            case LHU: {
                unsigned short tmp;
                memcpy(&tmp , inst.immediate + memory , 2);
                inst.result= tmp;
                time++;
                time%=3;
            }
                break;
            case LB: {
                char tmp;
                memcpy(&tmp , inst.immediate + memory , 1);
                inst.result = tmp;
                time++;
                time%=3;
            }
                break;
            case LBU: {
                unsigned char tmp;
                memcpy(&tmp , inst.immediate + memory , 1);
                inst.result = tmp;
                time++;
                time%=3;
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
        time++;
        time%=3;
    }
    if (time != 0) {
        this->busy=true;
        this->ready=false;
    } else {
        this->busy=false;
        this->ready=true;
    }
    buf = inst;
    reg[0]=0;
    
}

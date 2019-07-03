//
// Created by jinho on 7/1/2019.
//

#include "Executor.h"

void Executor::execute (Instruction inst , bool busy , int &instruction , bool ready) {
    this->busy=false;
    if (!ready) {
        this->ready=false;
        return;
    }
    if (busy) {
        this->busy=true;
        return;
    }
    if (inst.valid == false) {
        buf=inst;
        return;
    }
    
    
    switch (inst.type) {
        case R_type_: {
            switch (inst.r_type) {
                case ADD:
                    inst.result = inst.reg1_val + inst.reg2_val;
                    break;
                case SUB:
                    inst.result = inst.reg1_val - inst.reg2_val;
                    break;
                case SLT:
                    inst.result = inst.reg1_val < inst.reg2_val;
                    break;
                case SLTU: {
                    unsigned rs1u = inst.reg1_val;
                    unsigned rs2u = inst.reg2_val;
                    inst.result = rs1u < rs2u;
                }
                    break;
                case AND:
                    inst.result = inst.reg1_val & inst.reg2_val;
                    break;
                case OR:
                    inst.result = inst.reg1_val | inst.reg2_val;
                    break;
                case XOR:
                    inst.result = inst.reg1_val ^ inst.reg2_val;
                    break;
                case SLL:
                    inst.result = inst.reg1_val << inst.reg2_val;
                    break;
                case SRL: {
                    unsigned rs1u = inst.reg1_val;
                    unsigned rs2u = inst.reg2_val;
                    inst.result = rs1u >> rs2u;
                }
                    break;
                case SRA:
                    inst.result = inst.reg1_val >> inst.reg2_val;
                    break;
            }
        }
            
            break;
        case I_type_: {
            switch (inst.i_type) {
                case ADDI:
                    inst.result = inst.reg1_val + inst.immediate;
                    break;
                case SLTI:
                    inst.result = inst.reg1_val < inst.immediate;
                    break;
                case SLTIU: {
                    unsigned immu = inst.immediate;
                    inst.result = inst.reg1_val < immu;
                }
                    break;
                case ANDI:
                    inst.result = inst.reg1_val & inst.immediate;
                    break;
                case ORI:
                    inst.result = inst.reg1_val | inst.immediate;
                    break;
                case XORI:
                    inst.result = inst.reg1_val ^ inst.immediate;
                    break;
                case SLLI: {
                    unsigned immu = inst.immediate;
                    inst.result = inst.reg1_val << ((immu << 27) >> 27);
                }
                    break;
                case SRLI: {
                    unsigned immu = inst.immediate;
                    unsigned rs1u = inst.reg1_val;
                    inst.result = rs1u >> ((immu << 27) >> 27);
                }
                    break;
                case SRAI: {
                    unsigned immu = inst.immediate;
                    inst.result = inst.reg1_val >> ((immu << 27) >> 27);
            
                }
                    break;
                case JALR:
                    inst.result = inst.pc + 4;
                    pc = (inst.immediate + inst.reg1_val) & (-2);
                    instruction=0;
                    break;
                case LW:
                case LH:
                case LB:
                case LHU:
                case LBU:
                    inst.immediate += inst.reg1_val;
                    break;
        
            }
        }
            break;
        case U_type_:
            if (inst.u_type == LUI) {
                inst.result = inst.immediate ;
            } else {
                inst.result = inst.pc + inst.immediate;
            }
            
            break;
        case J_type_:
            inst.result = inst.pc + 4;
            pc = inst.pc+inst.immediate;
            instruction=0;
            break;
        case B_type_: {
            TwoLevelAdaptive& pred=branchPredictorMap.at(inst.pc);
            bool jumpPrefetch=pred.jumpOrNot();
            switch (inst.b_type) {
                case BEQ:
                    if (inst.reg1_val == inst.reg2_val ) {
                        if(!jumpPrefetch){
                            instruction = 0;
                            pc=inst.pc+inst.immediate;
                        } else {
                            pc = inst.pc + inst.immediate + 4;
                        }
                    } else {
                        if (jumpPrefetch) {
                            instruction=0;
                        }
                    }
                    pred.update(inst.reg1_val == inst.reg2_val);
                    break;
                case BNE:
                    if (inst.reg1_val != inst.reg2_val)  {
                        if(!jumpPrefetch){
                            instruction = 0;
                            pc=inst.pc+inst.immediate;
                        } else {
                            pc = inst.pc + inst.immediate + 4;
                        }
                    } else {
                        if (jumpPrefetch) {
                            instruction=0;
                        }
                    }
                    pred.update(inst.reg1_val != inst.reg2_val);
                    break;
                case BLT:
                    if (inst.reg1_val < inst.reg2_val) {
                        if(!jumpPrefetch){
                            instruction = 0;
                            pc=inst.pc+inst.immediate;
                        } else {
                            pc = inst.pc + inst.immediate + 4;
                        }
                    } else {
                        if (jumpPrefetch) {
                            instruction=0;
                        }
                    }
                    pred.update(inst.reg1_val < inst.reg2_val);
                    break;
                case BLTU: {
                    unsigned rs1u = inst.reg1_val;
                    unsigned rs2u = inst.reg2_val;
                    if (rs1u < rs2u)  {
                        if(!jumpPrefetch){
                            instruction = 0;
                            pc=inst.pc+inst.immediate;
                        } else {
                            pc = inst.pc + inst.immediate + 4;
                        }
                    } else {
                        if (jumpPrefetch) {
                            instruction=0;
                        }
                    }
                    pred.update(rs1u < rs2u);
                }
                    break;
                case BGE:
                    if (inst.reg1_val >= inst.reg2_val) {
                        if(!jumpPrefetch){
                            instruction = 0;
                            pc=inst.pc+inst.immediate;
                        } else {
                            pc = inst.pc + inst.immediate + 4;
                        }
                    } else {
                        if (jumpPrefetch) {
                            instruction=0;
                        }
                    }
                    pred.update(inst.reg1_val >= inst.reg2_val);
                    break;
                case BGEU: {
                    unsigned rs1u = inst.reg1_val;
                    unsigned rs2u = inst.reg2_val;
                    if (rs1u >= rs2u) {
                        if(!jumpPrefetch){
                            instruction = 0;
                            pc=inst.pc+inst.immediate;
                        } else {
                            pc = inst.pc + inst.immediate + 4;
                        }
                    } else {
                        if (jumpPrefetch) {
                            instruction=0;
                        }
                    }
                    pred.update(rs1u >= rs2u);
                }
                    
                    break;
            }
        }
            break;
        case S_type_:
            inst.immediate+=inst.reg1_val;
            
            break;
    }
    reg[0]=0;
    buf=inst;
    this->ready=true;
}
int pc;
int reg[32];
char memory[4194304];
std::list<int> regToChange;
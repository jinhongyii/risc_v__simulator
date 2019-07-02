//
// Created by jinho on 7/1/2019.
//

#include "Executor.h"

void Executor::execute (Instruction inst) {
    switch (inst.type) {
        case R_type_: {
            switch (inst.r_type) {
                case ADD:
                    reg[inst.rd] = reg[inst.rs1] + reg[inst.rs2];
                    break;
                case SUB:
                    reg[inst.rd] = reg[inst.rs1] - reg[inst.rs2];
                    break;
                case SLT:
                    reg[inst.rd] = reg[inst.rs1] < reg[inst.rs2];
                    break;
                case SLTU: {
                    unsigned rs1u = reg[inst.rs1];
                    unsigned rs2u = reg[inst.rs2];
                    reg[inst.rd] = rs1u < rs2u;
                }
                    break;
                case AND:
                    reg[inst.rd] = reg[inst.rs1] & reg[inst.rs2];
                    break;
                case OR:
                    reg[inst.rd] = reg[inst.rs1] | reg[inst.rs2];
                    break;
                case XOR:
                    reg[inst.rd] = reg[inst.rs1] ^ reg[inst.rs2];
                    break;
                case SLL:
                    reg[inst.rd] = reg[inst.rs1] << reg[inst.rs2];
                    break;
                case SRL: {
                    unsigned rs1u = reg[inst.rs1];
                    unsigned rs2u = reg[inst.rs2];
                    reg[inst.rd] = rs1u >> rs2u;
                }
                    break;
                case SRA:
                    reg[inst.rd] = reg[inst.rs1] >> reg[inst.rs2];
                    break;
            }
        }
            pc += 4;
            break;
        case I_type_: {
            switch (inst.i_type) {
                case ADDI:
                    reg[inst.rd] = reg[inst.rs1] + inst.immediate;
                    break;
                case SLTI:
                    reg[inst.rd] = reg[inst.rs1] < inst.immediate;
                    break;
                case SLTIU: {
                    unsigned immu = inst.immediate;
                    reg[inst.rd] = reg[inst.rs1] < immu;
                }
                    break;
                case ANDI:
                    reg[inst.rd] = reg[inst.rs1] & inst.immediate;
                    break;
                case ORI:
                    reg[inst.rd] = reg[inst.rs1] | inst.immediate;
                    break;
                case XORI:
                    reg[inst.rd] = reg[inst.rs1] ^ inst.immediate;
                    break;
                case SLLI: {
                    unsigned immu = inst.immediate;
                    reg[inst.rd] = reg[inst.rs1] << ((immu << 27) >> 27);
                }
                    break;
                case SRLI: {
                    unsigned immu = inst.immediate;
                    unsigned rs1u = reg[inst.rs1];
                    reg[inst.rd] = rs1u >> ((immu << 27) >> 27);
                }
                    break;
                case SRAI: {
                    unsigned immu = inst.immediate;
                    reg[inst.rd] = reg[inst.rs1] >> ((immu << 27) >> 27);
            
                }
                    break;
                case JALR:
                    reg[inst.rd] = pc + 4;
                    pc = (inst.immediate + reg[inst.rs1]) & (-2);
                    break;
                case LW:
                case LH:
                case LB:
                case LHU:
                case LBU:
                    inst.immediate += reg[inst.rs1];
                    break;
        
            }
    
            if (inst.i_type != JALR) {
                pc += 4;
            }
        }
            break;
        case U_type_:
            if (inst.u_type == LUI) {
                reg[inst.rd] = inst.immediate ;
            } else {
                reg[inst.rd] = pc + inst.immediate;
            }
            pc += 4;
            break;
        case J_type_:
            reg[inst.rd] = pc + 4;
            pc += inst.immediate;
            break;
        case B_type_:
            switch (inst.b_type) {
                case BEQ:
                    if (reg[inst.rs1] == reg[inst.rs2]) {
                        pc += inst.immediate;
                    } else {
                        pc+=4;
                    }
                    break;
                case BNE:
                    if (reg[inst.rs1] != reg[inst.rs2]) {
                        pc += inst.immediate;
                    } else {
                        pc+=4;
                    }
                    break;
                case BLT:
                    if (reg[inst.rs1] < reg[inst.rs2]) {
                        pc += inst.immediate;
                    } else {
                        pc+=4;
                    }
                    break;
                case BLTU: {
                    unsigned rs1u = reg[inst.rs1];
                    unsigned rs2u = reg[inst.rs2];
                    if (rs1u < rs2u) {
                        pc += inst.immediate;
                    } else {
                        pc+=4;
                    }
                }
                    break;
                case BGE:
                    if (reg[inst.rs1] >= reg[inst.rs2]) {
                        pc += inst.immediate;
                    } else {
                        pc+=4;
                    }
                    break;
                case BGEU: {
                    unsigned rs1u = reg[inst.rs1];
                    unsigned rs2u = reg[inst.rs2];
                    if (rs1u >= rs2u) {
                        pc += inst.immediate;
                    } else {
                        pc+=4;
                    }
                }
                    break;
            }
            break;
        case S_type_:
            inst.immediate+=reg[inst.rs1];
            pc+=4;
            break;
    }
    reg[0]=0;
    buf=inst;
    
}
int pc;
int reg[32];
char memory[4194304];
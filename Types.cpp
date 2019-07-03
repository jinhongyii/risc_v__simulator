//
// Created by jinho on 7/1/2019.
//

#include "Types.h"
#include "Executor.h"

/**
 *
 * @param instruction
 * @param rs1
 * @param rs2
 * @param rd
 * @param type
 * @return shamt
 */
void R_type_decoder::decode (unsigned instruction , int &rs1 , int &rs2 , int &rd , R_type &type) {
    unsigned funct7 = instruction >> 25;
    unsigned shamt = rs2 = (instruction << 7) >> 27;
    rs1 = (instruction << 12) >> 27;
    unsigned funct3 = (instruction << 17) >> 29;
    rd = (instruction << 20) >> 27;
    unsigned opcode = (instruction << 25) >> 25;
    
    switch (funct3) {
        case 0:
            if (funct7 == 0) {
                type = ADD;
            } else {
                type = SUB;
            }
            break;
        case 1:
            type = SLL;
            break;
        case 2:
            type = SLT;
            break;
        case 3:
            type = SLTU;
            break;
        case 4:
            type = XOR;
            break;
        case 5:
            if (funct7 == 0) {
                type = SRL;
            } else {
                type = SRA;
            }
            break;
        case 6:
            type = OR;
            break;
        case 7:
            type = AND;
    }
    
}

void I_type_decoder::decode (unsigned instruction , int &rs1 , int &rd , int &immediate , I_type &type) {
    int inst = instruction;
    immediate = inst >> 20;
    rs1 = (instruction << 12) >> 27;
    unsigned funct3 = (instruction << 17) >> 29;
    rd = (instruction << 20) >> 27;
    unsigned opcode = (instruction << 25) >> 25;
    if (opcode == 0x67) {
        type = JALR;
    }else if (opcode == 0x3) {
        switch (funct3) {
            case 0:
                type = LB;
                break;
            case 1:
                type = LH;
                break;
            case 2:
                type = LW;
                break;
            case 4:
                type = LBU;
                break;
            case 5:
                type = LHU;
                break;
        }
    } else {
        switch (funct3) {
            case 0:
                type = ADDI;
                break;
            case 1:
                type=SLLI;
                break;
            case 2:
                type = SLTI;
                break;
            case 3:
                type = SLTIU;
                break;
            case 4:
                type = XORI;
                break;
            case 5:
                if ((instruction >> 25) == 0) {
                    type = SRLI;
                } else {
                    type = SRAI;
                }
                break;
            case 6:
                type = ORI;
                break;
            case 7:
                type = ANDI;
                break;
        }
    }
}

void S_type_decoder::decode (unsigned instruction , int &rs1 , int &rs2 , int &immediate , S_type &type) {
    int inst = instruction;
    immediate = (inst >> 25) << 5;
    immediate += ((instruction << 20) >> 27);
    rs2 = (instruction << 7) >> 27;
    rs1 = (instruction << 12) >> 27;
    unsigned funct3 = (instruction << 17) >> 29;
    switch (funct3) {
        case 0:
            type = SB;
            break;
        case 1:
            type = SH;
            break;
        case 2:
            type = SW;
            break;
    }
    
}

void B_type_decoder::decode (unsigned instruction , int &rs1 , int &rs2 , int &immediate , B_type &type) {
    immediate = -(instruction >> 31) << 12;
    immediate += ((instruction << 1) >> 26) << 5;
    immediate += ((instruction << 20) >> 28) << 1;
    immediate += ((instruction << 24) >> 31) << 11;
    rs2 = (instruction << 7) >> 27;
    rs1 = (instruction << 12) >> 27;
    unsigned funct3 = (instruction << 17) >> 29;
    switch (funct3) {
        case 0:
            type = BEQ;
            break;
        case 1:
            type = BNE;
            break;
        case 4:
            type = BLT;
            break;
        case 5:
            type = BGE;
            break;
        case 6:
            type = BLTU;
            break;
        case 7:
            type = BGEU;
            break;
    }
}

void U_type_decoder::decode (unsigned instruction , int &immediate , int &rd , U_type &type) {
    int inst = instruction;
    immediate = (inst >> 12) << 12;
    rd = (instruction << 20) >> 27;
    unsigned opcode = (instruction << 25) >> 25;
    if (opcode == 0x37) {
        type = LUI;
    } else {
        type = AUIPC;
    }
}

void J_type_decoder::decode (unsigned instruction , int &immediate , int &rd) {
    immediate = -(instruction >> 31) << 20;
    immediate += ((instruction << 1) >> 22) << 1;
    immediate += ((instruction << 11) >> 31) << 11;
    immediate += ((instruction << 12) >> 24) << 12;
    rd = (instruction << 20) >> 27;
}

Types getType (unsigned instruction) {
    unsigned opcode = (instruction << 25) >> 25;
    unsigned funct3 = (instruction << 17) >> 29;
    Types type;
    switch (opcode) {
        case 0x37:
        case 0x17:
            type = U_type_;
            break;
        case 0x6f:
            type = J_type_;
            break;
        case 0x67:
        case 0x3:
        case 0x13:
            type=I_type_;
            break;
        case 0x63:
            type=B_type_;
            break;
        case 0x23:
            type=S_type_;
            break;
        case 0x33:
            type=R_type_;
    }
    return type;
}

bool find(const std::list<int>& ls,int target){
    for (auto i:ls) {
        if (i == target) {
            return true;
        }
    }
    return false;
}
void Decoder::decode (unsigned instruction , bool busy , int pc , bool ready) {
    this->busy=false;
    if (!ready) {
        this->ready=false;
        return;
    }
    if (busy) {
        this->busy=true;
        return;
    }
    if (instruction == 0) {
        this->buf.valid=false;
        return;
    }
    
    Instruction inst;
    inst.type=getType(instruction);
    switch (inst.type) {
        case R_type_:
            R_type_decoder::decode(instruction,inst.rs1,inst.rs2,inst.rd,inst.r_type);
            if(!find(regToChange,inst.rs1) && !find(regToChange,inst.rs2)) {
                inst.reg1_val = reg[inst.rs1];
                inst.reg2_val = reg[inst.rs2];
                regToChange.push_back(inst.rd);
            } else {
                this->busy=true;
                this->ready=false;
                return;
            }
            break;
        case I_type_ :
            I_type_decoder::decode(instruction,inst.rs1,inst.rd,inst.immediate,inst.i_type);
            if(!find(regToChange,inst.rs1)) {
                inst.reg1_val = reg[inst.rs1];
                regToChange.push_back(inst.rd);
            } else {
                this->busy=true;
                this->ready=false;
                return;
            }
            break;
        case S_type_:
            S_type_decoder::decode(instruction,inst.rs1,inst.rs2,inst.immediate,inst.s_type);
            if(!find(regToChange,inst.rs1) && !find(regToChange,inst.rs2)) {
                inst.reg1_val = reg[inst.rs1];
                inst.reg2_val = reg[inst.rs2];
            } else {
                this->busy=true;
                this->ready=false;
                return;
            }
            break;
        case B_type_:
            B_type_decoder::decode(instruction,inst.rs1,inst.rs2,inst.immediate,inst.b_type);
            if(!find(regToChange,inst.rs1) && !find(regToChange,inst.rs2)) {
                inst.reg1_val = reg[inst.rs1];
                inst.reg2_val = reg[inst.rs2];
                if(!branchPredictorMap.count(pc)){
                    branchPredictorMap.insert(std::make_pair(pc,TwoLevelAdaptive(inst.immediate+pc)));
                }
                branchAddress=pc;
                jump=true;
            } else {
                this->busy=true;
                this->ready=false;
                return;
            }
            break;
        case U_type_:
            U_type_decoder::decode(instruction,inst.immediate,inst.rd,inst.u_type);
            regToChange.push_back(inst.rd);
            break;
        case J_type_:
            J_type_decoder::decode(instruction,inst.immediate,inst.rd);
            regToChange.push_back(inst.rd);
            break;
    }
    buf=inst;
    buf.pc=pc;
    this->busy=false;
    this->ready=true;
}
std::string type_name[6]{"R_type","I_type","S_type","B_type","U_type","J_type"};
std::string R_type_name[]={"ADD","SUB","SLL","SLT","SLTU","XOR","SRL","SRA","OR","AND"};
std::string I_type_name[]={"SLLI","SRLI","SRAI","JALR","LB","LH","LW","LBU","LHU","ADDI","SLTI","SLTIU","XORI","ORI",
                           "ANDI"};
std::string S_type_name[]={"SB","SH","SW"};
std::string B_type_name[]={"BEQ","BNE","BLT","BGE","BLTU","BGEU"};
std::string U_type_name[]={"LUI","AUIPC"};
std::string regname[]={"zero","ra","sp","gp","tp","t0","t1","t2","s0","s1","a0","a1","a2",
                       "a3","a4","a5","a6","a7","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11"
        ,"t3","t4","t5","t6"};
std::unordered_map<int,TwoLevelAdaptive> branchPredictorMap;
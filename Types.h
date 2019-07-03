//
// Created by jinho on 7/1/2019.
//
#pragma once
#ifndef RISC_V__SIMULATOR_TYPES_H
#define RISC_V__SIMULATOR_TYPES_H
#include "predictor/TwoLevelAdaptive.h"
#include <unordered_map>
#include <string>
#include <sstream>
enum Types{
    R_type_,I_type_,S_type_,B_type_,U_type_,J_type_
};
extern std::string type_name[6];
enum R_type {
    ADD,SUB,SLL,SLT,SLTU,XOR,SRL,SRA,OR,AND
};
extern std::string R_type_name[];
enum I_type{
    SLLI,SRLI,SRAI,JALR,LB,LH,LW,LBU,LHU,ADDI,SLTI,SLTIU,XORI,ORI,ANDI
};
extern std::string I_type_name[];
enum S_type{
    SB,SH,SW
};
extern std::string S_type_name[];
enum B_type{
    BEQ,BNE,BLT,BGE,BLTU,BGEU
};
extern std::string B_type_name[];

enum U_type{
    LUI,AUIPC
};
extern std::string U_type_name[];
enum J_type{
    JAL
};

extern std::string regname[];

struct Instruction{
    Types type;
    R_type r_type;
    I_type i_type;
    S_type s_type;
    B_type b_type;
    U_type u_type;
    J_type j_type;
    int rs1,rs2,rd,immediate,result,reg1_val,reg2_val,pc,valid=true;
    std::string to_string(){
        std::stringstream sstream;
        switch (type) {
            case R_type_ :
                sstream<<"type:"<<R_type_name[r_type]<<" ";
                sstream<<" rs1:"<<regname[rs1]<<" rs2:"<<regname[rs2]<<
                " rd:"<<regname[rd];
                break;
            case I_type_:
                sstream<<"type:"<<I_type_name[i_type]<<" ";
                sstream<<" rs1:"<<regname[rs1]<<
                       " rd:"<<regname[rd]<<" immediate:"<<std::hex<<immediate;
                break;
            case S_type_:
                sstream<<"type:"<<S_type_name[s_type]<<" ";
                sstream<<" rs1:"<<regname[rs1]<<
                       " rs2:"<<regname[rs2]<<" immediate:"<<std::hex<<immediate;
                break;
            case B_type_:
                sstream<<"type:"<<B_type_name[b_type]<<" ";
                sstream<<" rs1:"<<regname[rs1]<<
                       " rs2:"<<regname[rs2]<<" immediate:"<<std::hex<<immediate;
                break;
            case U_type_:
                sstream<<"type:"<<U_type_name[u_type]<<" rd:"<<regname[rd]<<" immediate:"<<std::hex<<immediate;
                break;
            case J_type_:
                sstream<<"type:JAL ";
                sstream<<" rd:"<<regname[rd]<<" immediate:"<<std::hex<<immediate;
                break;
        }
        sstream<<" pc:"<<std::hex<<this->pc;
        return sstream.str();
        
    }
};
class R_type_decoder{
public:
    static void decode (unsigned instruction , int &rs1 , int &rs2 , int &rd , R_type &type);
};
class I_type_decoder{
public:
    static void decode (unsigned instruction , int &rs1 , int &rd , int &immediate , I_type &type);
};
class S_type_decoder{
public:
    static void decode (unsigned instruction , int &rs1 , int &rs2 , int &immediate , S_type &type);
};
class B_type_decoder{
public:
    static void decode (unsigned instruction , int &rs1 , int &rs2 , int &immediate , B_type &type);
};
class U_type_decoder{
public:
    static void decode (unsigned instruction,int & immediate,int& rd,U_type& type);
};
class J_type_decoder{
public:
    static void decode (unsigned  instruction ,int& immediate,int& rd);
};
Types getType (unsigned instruction);
extern std::unordered_map<int,TwoLevelAdaptive> branchPredictorMap;
class Decoder{

public:
    Instruction buf{};
    bool busy=false;
    bool ready=true;
    bool jump;
    int branchAddress;
    Decoder(){
        buf.valid=false;
    }
    void decode (unsigned instruction , bool busy , int pc , bool ready);
};

#endif //RISC_V__SIMULATOR_TYPES_H

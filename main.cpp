#include <iostream>
#include "Executor.h"
#include "Preprocessor.h"
#include "InstructionFetcher.h"
#include "MemoryAccess.h"
#include "WriteBack.h"
#include "Types.h"

int main () {
//    std::ifstream f("../test/pi.data");
//    std::ofstream debugFile("../debug");
    Preprocessor preprocessor(std::cin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    preprocessor.preprocess();
    InstructionFetcher instructionFetcher;
    Decoder decoder;
    Executor executor;
    MemoryAccess memoryAccess;
    WriteBack writeBack;
    int cnt=0;
    while(instructionFetcher.buf!=0xc68223) {
    
        writeBack.wb(memoryAccess.buf , memoryAccess.ready);
        memoryAccess.mem(executor.buf , writeBack.busy , executor.ready);
        executor.execute(decoder.buf , memoryAccess.busy , instructionFetcher.buf , decoder.ready);
        decoder.decode(instructionFetcher.buf , executor.busy , instructionFetcher.pc_ , instructionFetcher.ready ,
                       executor.buf , memoryAccess.buf , executor.ready , memoryAccess.ready);
//        debugFile<<std::hex<<instructionFetcher.buf<<" ra:"<<reg[1]
//                 <<" a0:"<<reg[10]<<std::endl;
//        debugFile<<decoder.buf.to_string()<<std::endl;
//        debugFile<<"reglist:";
//        for (auto i:regToChange) {
//            debugFile<<i<<" ";
//        }
//        debugFile<<std::endl<<std::endl;
        instructionFetcher.IF(decoder.busy , decoder.jump , decoder.branchAddress , decoder.jumpAddress);
    
        cnt++;
    }
    std::cout<<std::dec<<(((unsigned)reg[10])&255u);
//    std::cout<<cnt;
    
}
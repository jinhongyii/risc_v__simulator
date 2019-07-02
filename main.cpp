#include <iostream>
#include "Executor.h"
#include "Preprocessor.h"
#include "InstructionFetcher.h"
#include "MemoryAccess.h"
#include "WriteBack.h"
#include "Types.h"

int main () {
//    std::ifstream f("../test/tak.data");
    
    Preprocessor preprocessor(std::cin);
    preprocessor.preprocess();
    InstructionFetcher instructionFetcher;
    Decoder decoder;
    Executor executor;
    MemoryAccess memoryAccess;
    WriteBack writeBack;
    int cnt=0;
    while(instructionFetcher.buf!=0xc68223) {
        instructionFetcher.IF();
//        debugFile<<std::hex<<instructionFetcher.buf<<" ra:"<<reg[1]
//        <<" a0:"<<reg[10]<<std::endl;
        decoder.decode(instructionFetcher.buf);
//        debugFile<<decoder.buf.to_string()<<std::endl;
        executor.execute(decoder.buf);
        memoryAccess.mem(executor.buf);
        writeBack.wb(memoryAccess.buf);
        cnt++;
    }
    std::cout<<std::dec<<(((unsigned)reg[10])&255u);
    
}
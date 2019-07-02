#include <iostream>
#include "Executor.h"
#include "Preprocessor.h"
#include "InstructionFetcher.h"
#include "MemoryAccess.h"
#include "WriteBack.h"
#include "Types.h"

int main () {
    Preprocessor preprocessor;
    preprocessor.preprocess();
    InstructionFetcher instructionFetcher;
    Decoder decoder;
    Executor executor;
    MemoryAccess memoryAccess;
    WriteBack writeBack;
    while(instructionFetcher.buf!=0xc68223) {
        instructionFetcher.IF();
        std::cout<<std::hex<<instructionFetcher.buf<<" ra:"<<reg[1]
        <<" a0:"<<reg[10]<<std::endl;
        decoder.decode(instructionFetcher.buf);
        std::cout<<decoder.buf.to_string()<<std::endl;
        executor.execute(decoder.buf);
        memoryAccess.mem(executor.buf);
        writeBack.wb(memoryAccess.buf);
    }
    std::cout<<std::dec<<(((unsigned)reg[10])&255u);
    
}
cmake_minimum_required(VERSION 3.5.2)
project(riscv)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2  ")
add_executable(code main.cpp config.h Types.cpp Types.h Executor.cpp Executor.h InstructionFetcher.cpp
        InstructionFetcher.h Preprocessor.cpp Preprocessor.h MemoryAccess.cpp MemoryAccess.h WriteBack.cpp WriteBack.h predictor/Predictor.h predictor/SaturatingCounter.cpp predictor/SaturatingCounter.h
        predictor/TwoLevelAdaptive.cpp predictor/TwoLevelAdaptive.h )
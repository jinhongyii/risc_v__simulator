cmake_minimum_required(VERSION 3.5.2)
project(riscv)

set(CMAKE_CXX_STANDARD 14)

add_executable(riscv main.cpp config.h Types.cpp Types.h Executor.cpp Executor.h InstructionFetcher.cpp InstructionFetcher.h Preprocessor.cpp Preprocessor.h MemoryAccess.cpp MemoryAccess.h WriteBack.cpp WriteBack.h)
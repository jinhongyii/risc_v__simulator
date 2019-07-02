//
// Created by jinho on 7/1/2019.
//

#include "InstructionFetcher.h"

void InstructionFetcher::IF () {
    if(buf!=-1)
        memcpy(&buf,memory+pc,4);
}

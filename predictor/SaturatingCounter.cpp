//
// Created by jinho on 7/2/2019.
//

#include "SaturatingCounter.h"

void SaturatingCounter::update (bool jump) {
    if (jump) {
        if(counter<3) {
            counter++;
        }
    } else {
        if (counter > 0) {
            counter--;
        }
    }
}

bool SaturatingCounter::jumpOrNot () {
    if (counter <= 1) {
        return false;
    } else {
        return true;
    }
}

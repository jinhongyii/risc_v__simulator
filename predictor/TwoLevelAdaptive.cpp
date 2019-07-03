//
// Created by jinho on 7/2/2019.
//

#include "TwoLevelAdaptive.h"

void TwoLevelAdaptive::update (bool jump) {
    counter[(prev1<<1)+prev2].update(jump);
    prev1=prev2;
    prev2=jump;
}

bool TwoLevelAdaptive::jumpOrNot () {
//    return counter[(prev1<<1)+prev2].jumpOrNot();
    return false;
}


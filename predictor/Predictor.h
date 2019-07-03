//
// Created by jinho on 7/2/2019.
//

#ifndef RISCV_PREDICTOR_H
#define RISCV_PREDICTOR_H


class predictor {
public:
    virtual void update(bool jump)=0;
    virtual bool jumpOrNot()=0;
};


#endif //RISCV_PREDICTOR_H

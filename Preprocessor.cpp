//
// Created by jinho on 7/1/2019.
//

#include <iostream>
#include "Preprocessor.h"

void Preprocessor::preprocess () {
    int pos;
    std::string buf;
    while(true) {
        std::cin >> buf;
        if (std::cin.eof()) {
            return;
        }
        if (buf[0] == '@') {
            sscanf(buf.c_str()+1,"%x",&pos);
        } else {
            int t2,t3,t4,sum,tmp;
            std::cin>>std::hex>>t2>>t3>>t4;
            sscanf(buf.c_str(),"%x",&tmp);
            sum=(t4<<24)+(t3<<16)+(t2<<8)+tmp;
            memcpy(memory+pos,&sum,sizeof(sum));
            pos+=4;
        }
}
}

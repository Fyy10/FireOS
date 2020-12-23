//
// Created by jefffu on 2020/12/22.
//

#ifndef FIREOS_RCB_H
#define FIREOS_RCB_H

#include "string"
#include "vector"
#include "PCB.h"

class RCB {
private:
    string rid;
    int Status;
    vector<PCB*> waiting_list;

public:
    RCB(string, int);
    ~RCB();
};

#endif //FIREOS_RCB_H

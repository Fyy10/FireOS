//
// Created by jefffu on 2020/12/22.
//

#ifndef FIREOS_RCB_H
#define FIREOS_RCB_H

#include "string"
#include "list"
#include "PCB.h"

class RCB {
public:
    // name of res
    string rid;
    // total number of res
    int num;
    // number of available res
    int available;
    list<PCB*> waiting_list;

    RCB(string rid, int n);
    ~RCB();
};

#endif //FIREOS_RCB_H

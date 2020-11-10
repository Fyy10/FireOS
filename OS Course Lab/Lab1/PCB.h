//
// Created by jefffu on 2020/11/8.
//

#ifndef FIREOS_PCB_H
#define FIREOS_PCB_H

// #include "bits/stdc++.h"
#include "vector"
using namespace std;

enum State {
    RUNNING,
    READY,
    BLOCK
};

// process control block
class PCB {
private:
    int process_id;
    State status;
    int priority;
    PCB* father;
    vector<PCB*> son;
};


#endif //FIREOS_PCB_H

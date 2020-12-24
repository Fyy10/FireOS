//
// Created by jefffu on 2020/11/8.
//

#ifndef FIREOS_PCB_H
#define FIREOS_PCB_H

// #include "bits/stdc++.h"
#include "vector"
#include "string"
using namespace std;

// process control block
class PCB {
public:
    // pid (name)
    string pid;
    // status: running, ready, blocked
    string status;
    // priority: 0, 1, 2
    int priority;
    // requested resource list
    int res[4];
    // requesting resource list (when blocked)
    int req_res[4];
    PCB* father;
    vector<PCB*> sons;

    PCB(string pid, int priority, PCB* father=NULL);
    ~PCB();
};


#endif //FIREOS_PCB_H

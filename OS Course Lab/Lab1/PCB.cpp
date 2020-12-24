//
// Created by jefffu on 2020/11/8.
//

#include "PCB.h"
#include "iostream"

using namespace std;

PCB::PCB(string pid, int priority, PCB* father) {
    this->pid = pid;
    this->status = "ready";
    this->priority = priority;
    this->father = father;
    // initialize resource list
    for (int i = 0; i < 4; i++) {
        this->res[i] = 0;
        this->req_res[i] = 0;
    }
}

PCB::~PCB() {
    for (PCB* son : this->sons) delete son;
}

//
// Created by jefffu on 2020/11/8.
//

#ifndef FIREOS_PCB_H
#define FIREOS_PCB_H

// #include "bits/stdc++.h"
#include "vector"
#include "set"
#include "string"
using namespace std;

// process control block
class PCB {
private:
    // pid (name)
    string pid;
    // status: running, ready, block
    string status;
    // priority: 0, 1, 2
    int priority;
    // requested resource set
    set<int> res;
    PCB* father;
    vector<PCB*> sons;

public:
    PCB(string pid, int priority, PCB* father=NULL);
    ~PCB();

    string get_pid();
    string get_status();
    void set_status(string status);
    int get_priority();
    void display();
    void kill();
};


#endif //FIREOS_PCB_H
